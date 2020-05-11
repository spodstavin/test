%{
/*
 *	include files
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<errno.h>
#include	<math.h>
#include        "keyword.h"
#include	"histo.h"
#include	"disk-stress.h"

/*
 *	externals
 */

extern unsigned long		Verbose;	/* verbosity */
extern char			*Prog_name;	/* program name */
extern unsigned long		Line_number;	/* input line number */

/*
 *	global variables
 */

DISK_INFO		*Disk_list = (DISK_INFO *) NULL;/* list of disks */

/*
 *	The default values
 */

static unsigned long	Default_block_size		= 4096;
static unsigned long	Default_starting_block		= 0; /* from start */
static unsigned long	Default_test_area_size		= 0; /* whole thing */
static unsigned long	Default_requests_per_thread	= 10000;
static unsigned long	Default_threads_per_disk	= 1;
static unsigned long	Default_access_pattern		= DISK_PATTERN_RANDOM;
static unsigned long	Default_write_verification	= FALSE;
static double		Default_read_fraction		= 1.0;
static double		Default_histogram_upper_bound	= 1.0;
static unsigned long	Default_histogram_bins		= 1000;
static int		Default_metrics			= FALSE;

/*
 *	locals
 */

static unsigned long	Errors = (long) 0;	/* number of errors */
static unsigned long	Warnings = (long) 0;	/* number of warnings */

static DISK_INFO	*Last_disk;		/* last disk pointer */
static DISK_INFO	*Current_disk;		/* current disk pointer */

static unsigned long	Block_size_present;
static unsigned long	Starting_block_present;
static unsigned long	Test_area_size_present;
static unsigned long	Requests_per_thread_present;
static unsigned long	Threads_per_disk_present;
static unsigned long	Access_pattern_present;
static unsigned long	Read_fraction_present;
static unsigned long	Write_verification_present;
static unsigned long	Histogram_upper_bound_present;
static unsigned long	Histogram_bins_present;
%}

%union
{
	char	*ptr;
	long	integer;
	double	floating;
}

%token	DEFAULT_BLOCK_SIZE
%token	DEFAULT_READ_FRACTION
%token	DEFAULT_STARTING_BLOCK
%token	DEFAULT_TEST_AREA_SIZE
%token	DEFAULT_REQUESTS_PER_THREAD
%token	DEFAULT_THREADS_PER_DISK
%token	DEFAULT_ACCESS_PATTERN
%token	DEFAULT_WRITE_VERIFICATION
%token	DEFAULT_HISTOGRAM_UPPER_BOUND
%token	DEFAULT_HISTOGRAM_BINS
%token	BLOCK_SIZE
%token	READ_FRACTION
%token	STARTING_BLOCK
%token	TEST_AREA_SIZE
%token	REQUESTS_PER_THREAD
%token	THREADS_PER_DISK
%token	ACCESS_PATTERN
%token	MEMORY_ERROR
%token	INTERNAL_ERROR
%token	WRITE_VERIFICATION
%token	HISTOGRAM_UPPER_BOUND
%token	HISTOGRAM_BINS
%token	DISK
%token	RANDOM
%token	SEQUENTIAL
%token	ENABLED
%token	DISABLED
%token	FLOAT
%token	INTEGER
%token	STRING
%token	UNKNOWN
%token	KEYWORD
%token	SEPARATOR
%token	NEWLINE
%token	OPEN_BRACE
%token	CLOSE_BRACE
%token	UNQUOTED_STRING

%token	<ptr>		STRING
%token	<integer>	INTEGER
%token	<floating>	FLOAT

%type	<integer>	expect_an_integer
%type	<integer>	integer_ok
%type	<integer>	float_bad
%type	<floating>	expect_a_float
%type	<floating>	float_ok
%type	<floating>	integer_to_float

%type	<integer>	access_type
%type	<integer>	random
%type	<integer>	sequential

%type	<integer>	switch
%type	<integer>	enabled
%type	<integer>	disabled

%start file

%%

file: statements
{
	DISK_INFO	*di;
	unsigned long	error;
	unsigned long	blocks;

	/*
	 *	Validate the basics.
	 */

	if ( Errors == 0 )
	{
		if ( Disk_list == (DISK_INFO *) NULL )
		{
			(void) fprintf(stderr, "%s: empty control file\n",
								Prog_name);

			Errors++;
		}

		for ( di = Disk_list; di != (DISK_INFO *) NULL;
							di = di -> di_next )
		{
			if ( di -> di_starting_block %
				(di -> di_block_size / DISK_BLOCK_SIZE) )
			{
				(void) fprintf(stderr,
		"%s: %s - starting block not on a block-size boundary\n",
					Prog_name, di -> di_block_device_name);

				Errors++;
			}

			if ( di -> di_histogram_bins != 0 )
			{
				if ( di -> di_read_fraction == 0.0 )
				{
					di -> di_read_metrics = (void *) NULL;
				}
				else
				{
					di -> di_read_metrics = histo_init(
						di -> di_histogram_bins,
						0.0,
						di -> di_histogram_upper_bound,
						&error);

					if ( error != HISTO_OK )
					{
						(void) fprintf(stderr,
						"%s: metric init error %d\n",
						Prog_name, error);

						Errors++;
					}
				}

				if ( di -> di_read_fraction == 1.0 )
				{
					di -> di_write_metrics = (void *) NULL;
				}
				else
				{
					di -> di_write_metrics = histo_init(
						di -> di_histogram_bins,
						0.0,
						di -> di_histogram_upper_bound,
						&error);

					if ( error != HISTO_OK )
					{
						(void) fprintf(stderr,
						"%s: metric init error %d\n",
						Prog_name, error);

						Errors++;
					}
				}
			}
		}
	}

	/*
	 *	Let them know if anything happened
	 */

	if ( Warnings )
	{
		(void) fprintf(stderr, "%s: %ld %s occured.\n", Prog_name,
			Warnings, (Warnings == 1) ? "warning" : "warnings");
	}

	if ( Errors )
	{
		(void) fprintf(stderr, "%s: %ld %s occured.\n", Prog_name,
				Errors, (Errors == 1) ? "error" : "errors");
	}

	return ((Errors) ? EINVAL : 0);
}
;

expect_an_integer: integer_ok
	| float_bad
;

expect_a_float:	float_ok
	| integer_to_float
;

integer_ok:	INTEGER
{
	$$ = $1;
}
;

integer_to_float:	INTEGER
{
	if ( $1 != 0 )
	{
		warning("INTEGER converted to FLOATING");
	}

	$$ = (double) $1;
}
;

float_ok:	FLOAT
{
	$$ = $1;
}
;

float_bad:	FLOAT
{
	yyerror("expecting INTEGER; got FLOATING");

	$$ = (unsigned long) $1;
}
;

statements:
	| statement
	| statements statement
	| error NEWLINE
{
	yyerrok;
	yyclearin;
}
;

statement: default_statements
	| disk_statement
;

default_statements: default_block_size
	| default_read_fraction
	| default_starting_block
	| default_test_area_size
	| default_requests_per_thread
	| default_threads_per_disk
	| default_access_pattern
	| default_write_verification
	| default_histogram_upper_bound
	| default_histogram_bins
;

default_block_size: DEFAULT_BLOCK_SIZE expect_an_integer NEWLINE
{
	if ( ($2 <= 0) || ($2 % DISK_BLOCK_SIZE) )
	{
		invalid(DEFAULT_BLOCK_SIZE_KEYWORD);
	}

	Default_block_size = $2;
}
;

default_read_fraction: DEFAULT_READ_FRACTION expect_a_float NEWLINE
{
	if ( ($2 < 0.0) || ($2 > 1.0) )
	{
		invalid(DEFAULT_READ_FRACTION_KEYWORD);
	}

	Default_read_fraction = $2;
};

default_starting_block: DEFAULT_STARTING_BLOCK expect_an_integer NEWLINE
{
	if ( $2 <= 0 )
	{
		invalid(DEFAULT_STARTING_BLOCK_KEYWORD);
	}

	Default_starting_block = $2;
};

default_test_area_size:	DEFAULT_TEST_AREA_SIZE expect_an_integer NEWLINE
{
	if ( $2 <= 0 )
	{
		invalid(DEFAULT_TEST_AREA_SIZE_KEYWORD);
	}

	Default_test_area_size = $2;
};

default_requests_per_thread: DEFAULT_REQUESTS_PER_THREAD expect_an_integer NEWLINE
{
	if ( $2 <= 0 )
	{
		invalid(DEFAULT_REQUESTS_PER_THREAD_KEYWORD);
	}

	Default_requests_per_thread = $2;
};

default_threads_per_disk: DEFAULT_THREADS_PER_DISK expect_an_integer NEWLINE
{
	if ( $2 <= 0 )
	{
		invalid(DEFAULT_THREADS_PER_DISK_KEYWORD);
	}

	Default_threads_per_disk = $2;
};

random:	RANDOM
{
	$$ = DISK_PATTERN_RANDOM;
};

sequential: SEQUENTIAL
{
	$$ = DISK_PATTERN_SEQUENTIAL;
};

access_type:	random
	| sequential
;

default_access_pattern: DEFAULT_ACCESS_PATTERN access_type NEWLINE
{
	Default_access_pattern = $2;
};

enabled:	ENABLED
{
	$$ = TRUE;
};

disabled: DISABLED
{
	$$ = FALSE;
};

switch:	enabled
	| disabled
;

default_write_verification: DEFAULT_WRITE_VERIFICATION switch NEWLINE
{
	Default_write_verification = $2;
};

default_histogram_bins: DEFAULT_HISTOGRAM_BINS expect_an_integer NEWLINE
{
	if ( $2 <= 2 )
	{
		invalid(DEFAULT_HISTOGRAM_BINS_KEYWORD);
	}

	Default_histogram_bins = $2;

	Default_metrics = TRUE;
};

default_histogram_upper_bound: DEFAULT_HISTOGRAM_UPPER_BOUND expect_a_float NEWLINE
{
	if ( $2 <= 0.0 )
	{
		invalid(DEFAULT_HISTOGRAM_UPPER_BOUND_KEYWORD);
	}

	Default_histogram_upper_bound = $2;

	Default_metrics = TRUE;
};

block_size: BLOCK_SIZE expect_an_integer NEWLINE
{
	if ( ($2 <= 0) || ($2 % DISK_BLOCK_SIZE) )
	{
		invalid(BLOCK_SIZE_KEYWORD);
	}

	Current_disk -> di_block_size = $2;

	if ( Block_size_present )
	{
		multiple_occurance(BLOCK_SIZE_KEYWORD);
	}

	Block_size_present = TRUE;
};

read_fraction: READ_FRACTION expect_a_float NEWLINE
{
	if ( ($2 < 0.0) || ($2 > 1.0) )
	{
		invalid(READ_FRACTION_KEYWORD);
	}

	Current_disk -> di_read_fraction = $2;

	if ( Read_fraction_present )
	{
		multiple_occurance(READ_FRACTION_KEYWORD);
	}

	Read_fraction_present = TRUE;
};

starting_block: STARTING_BLOCK expect_an_integer NEWLINE
{
	if ( $2 <= 0 )
	{
		invalid(STARTING_BLOCK_KEYWORD);
	}

	Current_disk -> di_starting_block = $2;

	if ( Starting_block_present )
	{
		multiple_occurance(STARTING_BLOCK_KEYWORD);
	}

	Starting_block_present = TRUE;
};

test_area_size:	TEST_AREA_SIZE expect_an_integer NEWLINE
{
	if ( $2 <= 0 )
	{
		invalid(TEST_AREA_SIZE_KEYWORD);
	}

	Current_disk -> di_test_area_size = $2;

	if ( Test_area_size_present )
	{
		multiple_occurance(TEST_AREA_SIZE_KEYWORD);
	}

	Test_area_size_present = TRUE;
};

requests_per_thread: REQUESTS_PER_THREAD expect_an_integer NEWLINE
{
	if ( $2 <= 0 )
	{
		invalid(REQUESTS_PER_THREAD_KEYWORD);
	}

	Current_disk -> di_requests_per_thread = $2;

	if ( Requests_per_thread_present )
	{
		multiple_occurance(REQUESTS_PER_THREAD_KEYWORD);
	}

	Requests_per_thread_present = TRUE;
};

threads_per_disk: THREADS_PER_DISK expect_an_integer NEWLINE
{
	if ( $2 <= 0 )
	{
		invalid(THREADS_PER_DISK_KEYWORD);
	}

	Current_disk -> di_threads_per_disk = $2;

	if ( Threads_per_disk_present )
	{
		multiple_occurance(THREADS_PER_DISK_KEYWORD);
	}

	Threads_per_disk_present = TRUE;
};

access_pattern: ACCESS_PATTERN access_type NEWLINE
{
	Current_disk -> di_access_pattern = $2;

	if ( Access_pattern_present )
	{
		multiple_occurance(ACCESS_PATTERN_KEYWORD);
	}

	Access_pattern_present = TRUE;
};

write_verification: WRITE_VERIFICATION switch NEWLINE
{
	Current_disk -> di_write_verification = $2;

	if ( Write_verification_present )
	{
		multiple_occurance(WRITE_VERIFICATION_KEYWORD);
	}

	Write_verification_present = TRUE;
};

histogram_bins: HISTOGRAM_BINS expect_an_integer NEWLINE
{
	if ( $2 <= 2 )
	{
		invalid(HISTOGRAM_BINS_KEYWORD);
	}

	if ( Histogram_bins_present )
	{
		multiple_occurance(HISTOGRAM_BINS_KEYWORD);
	}
	else
	{
		if ( Current_disk -> di_histogram_bins == 0 )
		{
			Current_disk -> di_histogram_upper_bound =
					Default_histogram_upper_bound;
		}
	}

	Current_disk -> di_histogram_bins = $2;

	Histogram_bins_present = TRUE;
};

histogram_upper_bound: HISTOGRAM_UPPER_BOUND expect_a_float NEWLINE
{
	if ( $2 <= 0.0 )
	{
		invalid(HISTOGRAM_UPPER_BOUND_KEYWORD);
	}

	if ( Histogram_upper_bound_present )
	{
		multiple_occurance(HISTOGRAM_BINS_KEYWORD);
	}
	else
	{
		if ( Current_disk -> di_histogram_bins == 0 )
		{
			Current_disk -> di_histogram_bins =
						Default_histogram_bins;
		}
	}

	Current_disk -> di_histogram_upper_bound = $2;

	Histogram_upper_bound_present = TRUE;
};

disk_definition_line:	DISK STRING STRING NEWLINE
{
	DISK_INFO		*di;
	unsigned long		erc;

	static DISK_INFO	dummy;

	di = (DISK_INFO *) malloc(sizeof(DISK_INFO));

	if ( di == (DISK_INFO *) NULL )
	{

		(void) fprintf(stderr,
				"%s: disk info memory allocation failure\n",
				Prog_name);

		Errors++;

		Current_disk = &dummy;
	}
	else
	{
		Current_disk = di;
	}

	Current_disk -> di_block_device_name = $2;
	Current_disk -> di_raw_device_name = $3;
	Current_disk -> di_access_pattern = Default_access_pattern;
	Current_disk -> di_read_fraction = Default_read_fraction;
	Current_disk -> di_requests_per_thread = Default_requests_per_thread;
	Current_disk -> di_threads_per_disk = Default_threads_per_disk;
	Current_disk -> di_block_size = Default_block_size;
	Current_disk -> di_starting_block = Default_starting_block;
	Current_disk -> di_test_area_size = Default_test_area_size;
	Current_disk -> di_write_verification = Default_write_verification;

	if ( Default_metrics )
	{
		Current_disk -> di_histogram_upper_bound =
					Default_histogram_upper_bound;

		Current_disk -> di_histogram_bins = Default_histogram_bins;
	}
	else
	{
		Current_disk -> di_histogram_upper_bound = 0.0;
		Current_disk -> di_histogram_bins = 0;
	}

	Current_disk -> di_next = (DISK_INFO *) NULL;

	if ( di != (DISK_INFO *) NULL )
	{
		if ( Disk_list == (DISK_INFO *) NULL )
		{
			Disk_list = Current_disk;
		}
		else
		{
			Last_disk -> di_next = Current_disk;
		}

		Last_disk = Current_disk;
	}

	Block_size_present = FALSE;
	Starting_block_present = FALSE;
	Test_area_size_present = FALSE;
	Requests_per_thread_present = FALSE;
	Threads_per_disk_present = FALSE;
	Access_pattern_present = FALSE;
	Read_fraction_present = FALSE;
	Write_verification_present = FALSE;
	Histogram_bins_present = FALSE;
	Histogram_upper_bound_present = FALSE;
};

disk_statement: disk_definition_line
	| disk_definition_line disk_options
;

disk_options: open_brace_line disk_option_statements close_brace_line
;

open_brace_line:	OPEN_BRACE NEWLINE
;

close_brace_line:	CLOSE_BRACE NEWLINE
;

disk_option_statements:
	| disk_option_statement
	| disk_option_statements disk_option_statement
;

disk_option_statement:	block_size
	| read_fraction
	| starting_block
	| test_area_size
	| requests_per_thread
	| threads_per_disk
	| access_pattern
	| write_verification
	| histogram_bins
	| histogram_upper_bound
;

%%

/*
 *	yyerror
 *
 *	syntax error routine
 */

yyerror( char *s )
{
	(void) fprintf(stderr, "%s ERROR: %s at or near line %ld\n",
						Prog_name, s, Line_number); 

	Errors++;

	return;
}

/*
 *	invalid
 */

invalid( char *keyword )
{
	char line[256];

	(void) sprintf(line, "invalid %s", keyword);
	yyerror(line);

	return;
}

/*
 *	multiple_occurance
 */

multiple_occurance( char *keyword )
{
	char line[256];

	(void) sprintf(line, "multiple occurance of %s", keyword);
	yyerror(line);

	return;
}

/*
 *	warning
 */

warning( char *s )
{
	(void) fprintf(stderr, "%s WARNING: %s at or near line %ld\n",
						Prog_name, s, Line_number);

	Warnings++;

	return;
}
