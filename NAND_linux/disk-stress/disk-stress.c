#include	<stdio.h>
#include	<stdlib.h>
#include	<pthread.h>
#include	<errno.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<linux/unistd.h>
#include	<linux/fs.h>
#include	"disk-stress.h"
#include	"histo.h"

/*
 *	Externals
 */

extern DISK_INFO	*Disk_list;

extern	int		yydebug;

/*
 *	Globals
 */

char			*Prog_name;
char			*File_name;

unsigned long		Verbose = 0;

G_SLEEPY_BARRIER	Sleepy_barrier;

#if defined(_POSIX_THREAD_ATTR_STACKSIZE)
static unsigned long	Stack_size;
static unsigned long	Stack_size_present = FALSE;
#endif

#if defined(_POSIX_THREAD_PRIORITY_SCHEDULING)
static unsigned long	Schedule_policy;
static unsigned long	Schedule_policy_present = FALSE;
#endif

static long		Random_seed = 0;

/*
 *	parse_control
 */

static int
parse_control( void )
{
	int	erc;
	FILE	*stream;

	/*
	 *	Attempt to open the control file and parse it.
	 */

	if ( Verbose )
	{
		(void) printf("Beginning control file parsing\n");
	}

	stream = freopen(File_name, "r", stdin);

	if ( stream == (FILE *) NULL )
	{
		char	buffer[256];

		(void) sprintf(buffer, "%s: %s - open failure", Prog_name,
			       					File_name);

		perror(buffer);

		erc = errno;
	}
	else
	{
		/*
		 *	Attempt to parse the input.
		 */

		erc = yyparse();

		/*
		 *	Close the input.
		 */

		(void) fclose(stream);
	}

	/*
	 *	Deal with the aftermath.
	 */

	if ( Verbose )
	{
		(void) printf("Control file parsing: %s\n",
			      		(erc == 0) ? "PASSED" : "FAILED");
	}

	/*
	 *	Done!
	 */

	return (erc);
}

/*
 * validate_a_disk
 */

static int
validate_a_disk( DISK_INFO *di )
{
	int		fd;
	int		erc;
	struct stat	statbuf;
	unsigned long	io_blocks;
	unsigned long	disk_slots;
	unsigned long	starting_slot;
	unsigned long	size_in_blocks;
	unsigned long	test_area_slots;

	/*
	 *	Attempt to open the block device.
	 */

	fd = open(di -> di_block_device_name, O_RDONLY);

	if ( fd == -1 )
	{
		char	buffer[256];

		(void) sprintf(buffer, "%s: %s - open failure",
					Prog_name, di -> di_block_device_name);
			
		perror(buffer);

		return (errno);
	}
	
	/*
	 * 	Attempt to stat the file.
	 */

	if ( fstat(fd, &statbuf) == -1 )
	{
		char	buffer[256];

		(void) close(fd);

		(void) sprintf(buffer, "%s: %s - fstat failure",
					Prog_name, di -> di_block_device_name);

		perror(buffer);

		return (errno);
	}

	/*
	 *	Is this is not a block device, fail.
	 */

	if ( !S_ISBLK(statbuf.st_mode) )
	{
		(void) close(fd);

		(void) fprintf(stderr, "%s: %s - not a block device\n",
					Prog_name, di -> di_block_device_name);

		return (EINVAL);
	}

	/*
	 *	Attempt to get the partition size (in blocks).
	 */

	erc = ioctl(fd, BLKGETSIZE, &size_in_blocks);
		
	(void) close(fd);

	if ( erc == -1 )
	{
		char	buffer[256];

		(void) sprintf(buffer, "%s: %s - ioctl BLKGETSIZE failure",
					Prog_name, di -> di_block_device_name);

		perror(buffer);

		return (errno);
	}

	/*
	 *	Compute the size of the "disk" in slots and validate it.
	 */

	io_blocks = di -> di_block_size / DISK_BLOCK_SIZE;

	disk_slots = size_in_blocks / io_blocks;

	if ( disk_slots == 0 )
	{
		(void) fprintf(stderr, "%s: %s - zero effective size\n",
					Prog_name, di -> di_block_device_name);

		return (EINVAL);
	}

	/*
	 *	Compute the starting slot.
	 */

	starting_slot = di -> di_starting_block / io_blocks;

	/*
	 *	Validate the starting slot.
	 */

	if ( starting_slot >= disk_slots )
	{
		(void) fprintf(stderr,
			       "%s: %s - starting block passed end of disk\n",
				Prog_name, di -> di_block_device_name);

		return (EINVAL);
	}

	/*
	 *	If a dynamic test area size was specified, compute the
	 *	actual size for this disk.
	 */

	if ( di -> di_test_area_size == 0 )
	{
		di -> di_test_area_size =
				(disk_slots - starting_slot) * io_blocks;
	}

	/*
	 *	Validate the the test area fall completely within the disk.
	 */


	test_area_slots = di -> di_test_area_size / io_blocks;

	if ( (starting_slot + test_area_slots) > disk_slots )
	{
		(void) fprintf(stderr, "%s: %s - test area not within disk\n",
					Prog_name, di -> di_block_device_name);

		return (EINVAL);
	}

	/*
	 *	Attempt to open the raw device.
	 */

	fd = open(di -> di_raw_device_name, O_RDONLY);

	if ( fd == -1 )
	{
		char	buffer[256];

		(void) sprintf(buffer, "%s: %s - open failure",
					Prog_name, di -> di_raw_device_name);
			
		perror(buffer);

		return (errno);
	}
	
	/*
	 * 	Attempt to stat the file.
	 */

	erc = fstat(fd, &statbuf);

	(void) close(fd);

	if ( erc == -1 )
	{
		char	buffer[256];

		(void) sprintf(buffer, "%s: %s - fstat failure",
					Prog_name, di -> di_raw_device_name);

		perror(buffer);

		return (errno);
	}

	/*
	 *	If this is not a character (raw) device, fail.
	 */

	if ( !S_ISCHR(statbuf.st_mode) )
	{
		(void) fprintf(stderr, "%s: %s - not a character device\n",
					Prog_name, di -> di_raw_device_name);

		return (EINVAL);
	}

	/*
	 * 	Done!
	 */

	return (0);
}

/*
 *	validate_disks
 */

static int
validate_disks( void )
{
	DISK_INFO	*di;
	int		erc;

	/*
	 *	Validate each disk.
	 */

	if ( Verbose )
	{
		(void) printf("Beginning parameter validation phase\n");
	}

	erc = 0;

	for ( di = Disk_list; di != (DISK_INFO *) NULL; di = di -> di_next )
	{
		if ( validate_a_disk(di) != 0 )
		{
			erc = EINVAL;
		}
	}

	/*
	 *	Deal with the aftermath.
	 */

	if ( Verbose )
	{
		(void) printf("Parameter validation phase: %s\n",
			      		(erc == 0) ? "PASSED" : "FAILED");
	}

	/*
	 *	Return status
	 */

	return (erc);
}

/*
 *	initialize_barrier
 */

static int
initialize_barrier( void )
{
	DISK_INFO	*di;
	unsigned long	threads;

	/*
	 *	Initialize the sleepy barrier
	 */

	if ( Verbose )
	{
		(void) printf("Beginning barrier initialization phase\n");
	}

	threads = 0;

	for ( di = Disk_list; di != (DISK_INFO *) NULL; di = di -> di_next )
	{
		threads += di -> di_threads_per_disk;
	}

	g_init_sleepy_barrier(&Sleepy_barrier, threads);

	/*
	 *	Deal with the aftermath.
	 */

	if ( Verbose )
	{
		(void) printf("Barrier initialization phase: PASSED\n");
	}

	/*
	 *	Return success!
	 */

	return (0);
}

/*
 *	verbosity
 */

static int
verbosity( void )
{
	DISK_INFO	*di;

	/*
	 *	Be verbose as necessary.
	 */

	if ( Verbose > 1 )
	{
		for ( di = Disk_list; di != (DISK_INFO *) NULL;
							di = di -> di_next )
		{
			(void) printf("block device name\t%s\n",
						di -> di_block_device_name);

			(void) printf("raw device name\t\t%s\n",
						di -> di_raw_device_name);

			(void) printf("access pattern\t\t%s\n",
			(di -> di_access_pattern == DISK_PATTERN_RANDOM) ?
						"random" : "sequential");

			(void) printf("write verification\t%s\n",
					(di -> di_write_verification == TRUE) ?
					"enabled" : "disabled");

			(void) printf("read fraction\t\t%lE\n",
				      			di -> di_read_fraction);

			(void) printf("requests per thread\t%ld\n",
				      		di -> di_requests_per_thread);

			(void) printf("block size\t\t%ld\n",
				      			di -> di_block_size);

			(void) printf("starting block\t\t%ld\n",
				      		di -> di_starting_block);

			(void) printf("test area size\t\t%ld\n",
				      		di -> di_test_area_size);

			(void) printf("threads per disk\t%ld\n",
				      		di -> di_threads_per_disk);

			if ( di -> di_histogram_bins != 0 )
			{
				(void) printf("histogram bins\t\t%ld\n",
				      		di -> di_histogram_bins);

				(void) printf("histogram upper bound\t%E\n",
				      	di -> di_histogram_upper_bound);

				(void) printf("histogram of reads:\t%s\n",
				(di -> di_read_metrics == (void *) NULL) ?
					"disabled" : "enabled");

				(void) printf("histogram of writes:\t%s\n",
				(di -> di_write_metrics == (void *) NULL) ?
					"disabled" : "enabled");
			}

			(void) printf("\n");
		}
	}

	/*
	 *	Return success!
	 */

	return (0);
}

/*
 *	allocate_memory
 */

void *
allocate_memory( unsigned long amount )
{
	unsigned long	offset;
	void		*buffer;

	buffer = malloc(amount + PREFERED_ALIGNMENT);

	if ( buffer != (void *) NULL )
	{
		offset = ((unsigned long) buffer) & (PREFERED_ALIGNMENT - 1);

		buffer = (void *) (((unsigned long) buffer) +
						(PREFERED_ALIGNMENT - offset));
	}

	return (buffer);
}

/*
 *	memory_allocation
 */

static int
memory_allocation( void )
{
	unsigned long		i;
	DISK_INFO		*di;
	BLOCK_LOCK		*bl;
	DISK_THREAD_PARAMETER	*dtp;
	unsigned long		error;

	/*
	 *	Attempt to allocate all of the memory structures.
	 */

	if ( Verbose )
	{
		(void) printf("Beginning memory allocation phase\n");
	}

	errno = 0;

	for ( di = Disk_list; di != (DISK_INFO *) NULL; di = di -> di_next )
	{
		di -> di_parameters = (DISK_THREAD_PARAMETER *) calloc(
					di -> di_threads_per_disk,
					sizeof(DISK_THREAD_PARAMETER));

		if ( di -> di_parameters == (DISK_THREAD_PARAMETER *) NULL )
		{
			errno = ENOMEM;

			goto done;
		}

		di -> di_bl_free_list = (BLOCK_LOCK *) NULL;

		for ( i = 0; i < di -> di_threads_per_disk; i++ )
		{
			dtp = &di -> di_parameters[i];

			dtp -> dtp_disk_info = di;

			DTP_NUMBER(dtp) = i;

			DTP_WRITE_BUFFER(dtp) =
					allocate_memory(di -> di_block_size);

			DTP_READ_BUFFER(dtp) =
					allocate_memory(di -> di_block_size);

			if ( (DTP_WRITE_BUFFER(dtp) == (void *) NULL) ||
			     (DTP_READ_BUFFER(dtp) == (void *) NULL) )
			{
				errno = ENOMEM;

				goto done;
			}

			bl = (BLOCK_LOCK *) malloc(sizeof(BLOCK_LOCK));

			if ( bl == (BLOCK_LOCK *) NULL )
			{
				errno = ENOMEM;

				goto done;
			}

			bl -> bl_next = di -> di_bl_free_list;
			di -> di_bl_free_list = bl;
		}

		/*
		 *	Initiialize the locking mechanism.
		 */

		pthread_mutex_init(&di -> di_lock, NULL);

		for ( i = 0; i < HASH_TABLE_SIZE; i++ )
		{
			di -> di_hash[i].blhh_list = (BLOCK_LOCK *) NULL;
			pthread_cond_init(&di -> di_hash[i].blhh_conditional,
									NULL);
		}
	}

done:
	/*
	 *	Deal with the aftermath.
	 */

	if ( Verbose )
	{
		(void) printf("Memory allocation phase: %s\n",
			      		(errno == 0) ? "PASSED" : "FAILED");
	}
	else
	{
		if ( errno != 0 )
		{
			perror("memory allocation failure");
		}
	}

	/*
	 *	Return status
	 */

	return (errno);
}

/*
 *	start_random
 */

static int
start_random( void )
{
	int	erc;
	long	seed;

	/*
	 *	Initialize the random number generator
	 */

	if ( Verbose )
	{
		(void) printf(
			"Beginning random number initialization phase\n");
	}

	/*
	 *	Determine the initial seed.
	 */

	seed = (Random_seed == 0) ? -1 : Random_seed;

	/*
	 *	Initialize the random number generator.
	 */

	erc = init_uniform_random(seed);

	/*
	 *	Deal with the aftermath.
	 */

	if ( Verbose )
	{
		(void) printf("Random number initialization phase: %s\n",
					(erc == 0) ? "PASSED" : "FAILED");
	}
	else
	{
		if ( erc != 0 )
		{
			perror("random number initialization failure");
		}
	}

	/*
	 *	Return status
	 */

	return (erc);
}

/*
 *	start_threads
 */

static int
start_threads( void )
{
	size_t			i;
	DISK_INFO		*di;
	int			erc;
	DISK_THREAD_PARAMETER	*dtp;

	static pthread_attr_t	attributes;

	/*
	 *	Create the appropriate thread attribute set.
	 */

	pthread_attr_init(&attributes);

#if defined(_POSIX_THREAD_ATTR_STACKSIZE)
	if ( Stack_size_present )
	{
		pthread_attr_setstacksize(&attributes,
						(size_t) (1024 * Stack_size));
	}

#endif

#if defined(_POSIX_THREAD_PRIORITY_SCHEDULING)
	if ( Schedule_policy_present )
	{
		pthread_attr_setschedpolicy(&attributes,
						    (int) Schedule_policy);
	}
#endif

	/*
	 *	Create all of the threads.
	 */

	if ( Verbose )
	{
		(void) printf("Beginning thread creation phase\n");
	}

	for ( di = Disk_list; di != (DISK_INFO *) NULL; di = di -> di_next )
	{
		for ( i = 0; i < di -> di_threads_per_disk; i++ )
		{
			dtp = &di -> di_parameters[i];

			if ( di -> di_access_pattern == DISK_PATTERN_RANDOM )
			{
				erc = pthread_create(&DTP_ID(dtp),
						&attributes,
						(void *) random_io_thread,
						(void *) dtp);
			}
			else
			{
				erc = pthread_create(&DTP_ID(dtp),
						&attributes,
						(void *) sequential_io_thread,
						(void *) dtp);
			}

			if ( erc != 0 )
			{
				break;
			}
		}
	}

	/*
	 *	Deal with the aftermath.
	 */

	if ( Verbose )
	{

		(void) printf("Thread creation phase: %s\n",
			      		(erc == 0) ? "PASSED" : "FAILED");
	}
	else
	{
		if ( erc != 0 )
		{
			perror("pthread_create failure");
		}
	}

	/*
	 *	Done!
	 */

	return (erc);
}

/*
 *	reap_threads
 */

static int
reap_threads( void )
{
	unsigned long		i;
	DISK_INFO		*di;
	int			erc;
	DISK_THREAD_PARAMETER	*dtp;

	/*
	 *	Now reap all of the threads.
	 */

	if ( Verbose )
	{
		(void) printf("Beginning thread reaping phase\n");
	}

	for ( di = Disk_list; di != (DISK_INFO *) NULL; di = di -> di_next )
	{
		for ( i = 0; i < di -> di_threads_per_disk; i++ )
		{
			dtp = &di -> di_parameters[i];

			erc = pthread_join(DTP_ID(dtp), NULL);

			if ( erc != 0 )
			{
				break;
			}
		}
	}

	if ( Verbose )
	{
		(void) printf("Thread reaping phase: %s\n",
			      		(erc == 0) ? "PASSED" : "FAILED");
	}
	else
	{
		if ( erc != 0 )
		{
			perror("pthread_join failure");
		}
	}

	/*
	 *	Done!
	 */

	return (erc);
}

/*
 *	status_inspection
 */

static int
status_inspection( void )
{
	unsigned long		i;
	DISK_INFO		*di;
	int			erc;
	DISK_THREAD_PARAMETER	*dtp;

	int			failures = 0;

	/*
	 *	Inspect the results if there was no reaping problems.
	 */

	if ( Verbose )
	{
		(void) printf("Beginning status inspection phase\n");
	}

	for ( di = Disk_list; di != (DISK_INFO *) NULL; di = di -> di_next )
	{
		for ( i = 0; i < di -> di_threads_per_disk; i++ )
		{
			dtp = &di -> di_parameters[i];

			erc = DTP_STATUS(dtp);

			if ( erc != 0 )
			{
				failures++;
			}
		}
	}

	if ( Verbose )
	{
		(void) printf("Status inspection phase: %s\n",
			      		(failures) ? "FAILED" : "PASSED");
	}
	else
	{
		if ( failures )
		{
			(void) fprintf(stderr, "%s: FAILED\n", Prog_name);
		}
	}

	/*
	 *	Done!
	 */

	return (failures);
}

static void
read_before( void *token )
{
	DISK_INFO	*di;

	di = (DISK_INFO *) token;

	(void) printf("BEGIN read metrics for %s (%s)\n",
		di -> di_block_device_name, di -> di_raw_device_name);

	return;
}

static void
write_before( void *token )
{
	DISK_INFO	*di;

	di = (DISK_INFO *) token;

	(void) printf("BEGIN write metrics for %s (%s)\n",
		di -> di_block_device_name, di -> di_raw_device_name);

	return;
}

static void
after( void *token )
{
	DISK_INFO	*di;

	di = (DISK_INFO *) token;

	(void) printf("END metrics for %s (%s)\n",
		di -> di_block_device_name, di -> di_raw_device_name);

	return;
}

static void
bin_statistics(	void		*token,
		float		bin_lower,
		float		bin_upper,
		unsigned long	bin_count )
{
	if ( bin_count != 0 )
	{
		(void) printf("%E >= x < %E: %ld\n",
			(double) bin_lower, (double) bin_upper, bin_count);
	}

	return;
}

static void
out_low(void *token, unsigned long count )
{
	(void) printf("out of bounds, below minimum: %ld\n", count);

	return;
}

static void
out_high(void *token, unsigned long count )
{
	(void) printf("out of bounds, above maximum: %ld\n", count);

	return;
}

/*
 *	metrics_report
 */

static int
metrics_report( void )
{
	DISK_INFO	*di;

	/*
	 *	Report metrics as appropriate.
	 */

	if ( Verbose )
	{
		(void) printf("Beginning metrics output phase\n");
	}

	for ( di = Disk_list; di != (DISK_INFO *) NULL; di = di -> di_next )
	{
		if ( di -> di_read_metrics != (void *) NULL )
		{
			histo_print(di -> di_read_metrics, (void *) di,
					read_before, after, bin_statistics,
					out_low, out_high);
		}

		if ( di -> di_write_metrics != (void *) NULL )
		{
			histo_print(di -> di_write_metrics, (void *) di,
					write_before, after, bin_statistics,
					out_low, out_high);
		}
	}

	if ( Verbose )
	{
		(void) printf("metric output phase: PASSED\n");
	}

	/*
	 *	Done!
	 */

	return (0);
}

#if defined(_POSIX_THREAD_PRIORITY_SCHEDULING)

struct table
{
	char		*string;
	unsigned long	value;
};

typedef struct table	TABLE;

static TABLE		Table[] = {
	{ "SCHED_FIFO",		SCHED_FIFO },
	{ "SCHED_RR",		SCHED_RR },
	{ "SCHED_OTHER",	SCHED_OTHER }
};

#define	TABLE_SIZE	(sizeof(Table) / sizeof(TABLE))

/*
 *	lookup
 */

static int
lookup( char *string, unsigned long *value )
{
	unsigned long	i;

	for ( i = 0; i < TABLE_SIZE; i++ )
	{
		if ( strcmp(string, Table[i].string) == 0 )
		{
			*value = Table[i].value;

			return (0);
		}
	}

	return (-1);
}
#endif

/*
 *	usage
 */

static void
usage ( void )
{
	(void) fprintf(stderr, "Usage: %s [options] control-file-name\n\n",
		       						Prog_name);

	(void) fprintf(stderr, "Options:\n\n");

	(void) fprintf(stderr, "-n integer\tMessage volume (noise level)\n");

#if defined(_POSIX_THREAD_PRIORITY_SCHEDULING)
	(void) fprintf(stderr,
		"-p policy-name\tPOSIX threads scheduling policy name\n");
#endif

	(void) fprintf(stderr, "-r integer\tRandom number generator seed\n");

#if defined(_POSIX_THREAD_ATTR_STACKSIZE)
	(void) fprintf(stderr,
		"-s integer\tStack size in K (for each test thread)\n");
#endif

	(void) fprintf(stderr, "-v\t\tVersion number information\n");
	(void) fprintf(stderr, "-y\t\tgrammar debugging (yacc yydebug)\n");

	(void) fprintf(stderr, "\n");

	exit(1);
}

/*
 *	versioning
 */

static void
versioning( void )
{
	(void) fprintf(stderr, "%s: version 1.2\n", Prog_name);

	exit(0);
}

/*
 *	Program phase table
 */

static int (*Phase_table[])() = {
	parse_control,
	validate_disks,
	verbosity,
	memory_allocation,
	initialize_barrier,
	start_random,
	start_threads,
	reap_threads,
	status_inspection,
	metrics_report
};

#define	PHASE_TABLE_SIZE (sizeof(Phase_table) / sizeof(int (*)()))

/*
 *	main
 */

main( int argc, char *argv[] )
{
	unsigned long	i;
	int		c;
	char		*p;
	int		erc;

	/*
	 *	Set up the program name.
	 */

	p = (char *) strrchr(argv[0], '/');

	if ( p == (char *) NULL )
	{
		Prog_name = argv[0];
	}
	else
	{
		Prog_name = p + 1;
	}

	/*
	 *	Process the options.
	 */

	while ( (c = getopt(argc, argv, "?hn:p:r:s:vy")) != -1 )
	{
		switch ( c )
		{
		case 'n':
			if ( sscanf(optarg, "%ld", &Verbose) != 1 )
			{
				(void) fprintf(stderr,
				"%s: verbose option conversion error\n");

				exit(1);
			}

			break;

#if defined(_POSIX_THREAD_PRIORITY_SCHEDULING)
		case 'p':
			if ( lookup(optarg, &Schedule_policy) == -1 )
			{
				(void) fprintf(stderr,
					"%s: invalid policy name\n",
					Prog_name);

				exit(1);
			}
			else
			{
				Schedule_policy_present = TRUE;
			}

			break;
#endif

#if defined(_POSIX_THREAD_ATTR_STACKSIZE)
		case 's':
			if ( sscanf(optarg, "%ld", &Stack_size) == 0 )
			{
				(void) fprintf(stderr,
					"%s: argument conversion error\n",
					Prog_name);

				exit(1);
			}
			else
			{
        			pthread_attr_t   attributes;

				(void) pthread_attr_init(&attributes);
				(void) pthread_attr_getstacksize(&attributes,
							(size_t *) &i);

				if ( (1024 * Stack_size) < i )
				{
					(void) fprintf(stderr,
		"%s: Stack size is less than the recommended size (%ld)\n",
						Prog_name, i);

					exit(1);
				}

				Stack_size_present = TRUE;
			}

			break;
#endif

		case 'r':
			if ( sscanf(optarg, "%ld", &Random_seed) != 1 )
			{
				(void) fprintf(stderr,
			"%s: random number generator seed conversion error\n");

				exit(1);
			}

			if ( Random_seed == 0 )
			{
				(void) fprintf(stderr,
				"%s: invalid random number generator seed\n");

				exit(1);
			}

			break;

		case 'v':
			versioning();
			break;

		case 'y':
			yydebug = 1;
			break;

		case '?':
		case 'h':
		default:
			usage();
			break;
		}
	}

	argv += optind;
	argc -= optind;

	/*
	 *	Only one file argument.
	 */

	if ( argc != 1 )
	{
		usage();
	}

	/*
	 *	Execute the phases.
	 */

	File_name = argv[0];

	for ( i = 0; i < PHASE_TABLE_SIZE; i++ )
	{
		erc = (*Phase_table[i])();

		if ( erc != 0 )
		{
			break;
		}
  	}

	/*
	 *	Attempt to run the test.
	 */

	exit(erc);
}
