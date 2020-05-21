#include	<stdio.h>
#include	<stdlib.h>
#include	<ctype.h>
#include	"y.tab.h"
#include	"keyword.h"
#include	"disk-stress.h"

/*
 *	globals
 */

unsigned long		Line_number = 1;       /* input line number */

extern unsigned long	Verbose;
extern char		*Prog_name;

/*
 *	state variables
 */

static int		Token_on_line = FALSE;

/*
 *	the keyword table
 */

struct key_word
{
	char	*token;
	int	value;
};

static struct key_word Keyword_table[] = {
	{ DEFAULT_BLOCK_SIZE_KEYWORD,		DEFAULT_BLOCK_SIZE },
	{ DEFAULT_READ_FRACTION_KEYWORD,	DEFAULT_READ_FRACTION },
	{ DEFAULT_STARTING_BLOCK_KEYWORD,	DEFAULT_STARTING_BLOCK },
	{ DEFAULT_TEST_AREA_SIZE_KEYWORD,	DEFAULT_TEST_AREA_SIZE },
	{ DEFAULT_REQUESTS_PER_THREAD_KEYWORD,	DEFAULT_REQUESTS_PER_THREAD },
	{ DEFAULT_THREADS_PER_DISK_KEYWORD,	DEFAULT_THREADS_PER_DISK },
	{ DEFAULT_ACCESS_PATTERN_KEYWORD,	DEFAULT_ACCESS_PATTERN },
	{ DEFAULT_WRITE_VERIFICATION_KEYWORD,	DEFAULT_WRITE_VERIFICATION },
	{ DEFAULT_HISTOGRAM_UPPER_BOUND_KEYWORD,
					DEFAULT_HISTOGRAM_UPPER_BOUND },
	{ DEFAULT_HISTOGRAM_BINS_KEYWORD,	DEFAULT_HISTOGRAM_BINS },
	{ BLOCK_SIZE_KEYWORD,			BLOCK_SIZE },
	{ READ_FRACTION_KEYWORD,		READ_FRACTION },
	{ STARTING_BLOCK_KEYWORD,		STARTING_BLOCK },
	{ TEST_AREA_SIZE_KEYWORD,		TEST_AREA_SIZE },
	{ REQUESTS_PER_THREAD_KEYWORD,		REQUESTS_PER_THREAD },
	{ THREADS_PER_DISK_KEYWORD,		THREADS_PER_DISK },
	{ ACCESS_PATTERN_KEYWORD,		ACCESS_PATTERN },
	{ WRITE_VERIFICATION_KEYWORD,		WRITE_VERIFICATION },
	{ HISTOGRAM_UPPER_BOUND_KEYWORD,	HISTOGRAM_UPPER_BOUND },
	{ HISTOGRAM_BINS_KEYWORD,		HISTOGRAM_BINS },
	{ DISK_KEYWORD,				DISK },
	{ ENABLED_KEYWORD,			ENABLED },
	{ DISABLED_KEYWORD,			DISABLED },
	{ RANDOM_KEYWORD,			RANDOM },
	{ SEQUENTIAL_KEYWORD,			SEQUENTIAL }
};

#define NUM_KEYWORDS (sizeof (Keyword_table) / sizeof (struct key_word))

/*
 *	number
 *
 *	The input should be a number string.
 *	Validate it, and convert it to internal form.
 *	If successfully converted store in known place and record type.
 *	Any errors return token UNKNOWN.
 */

int
number( char *t )
{
	char	*p;
	int	erc;
	int	sign;

	/*
	 *	Pick off a sign if it is present.
	 */

	if ( *t == '-' )
	{
		sign = -1;
		t++;
	}
	else
	{
		sign = 1;
		
		if ( *t == '+' )
		{
			t++;
		}
	}

	/*
	 *	Walk to the end of the digit string.
	 */

	for ( p = t; isdigit(*p); p++ );

	/*
	 *	What we do is based on how we ended.
	 */

	switch ( *p )
	{
	case '\0':
	case 'k':
	case 'K':
	case 'b':
	case 'B':
		if ( sscanf(t, "%ld", &yylval.integer) == 1 )
		{
			switch ( *p )
			{
			case 'k':
			case 'K':
				yylval.integer *= 1024;
				break;

			case 'b':
			case 'B':
				yylval.integer *= 512;
				break;

			case '\0':
				break;
			}

			erc = INTEGER;
		}
		else
		{
			erc = UNKNOWN;
		}
		break;

	case '.' :
	case 'e' :
	case 'E' :
		yylval.floating = sign * atof(t);
		erc = FLOAT;
		break;

	default:
		erc = UNKNOWN;
		break;
	}

	/*
	 *	Return status.
	 */

	return (erc);
}

/*
 *	get_token
 *
 *	Get a token from the input string.
 *	Tokens longer than MAX_UNQUOTED_STRING or MAX_STRING are truncated.
 *	Quoted string are handled.
 *
 *	This is fast and nasty, using goto's to loop.
 */

int
get_token( char *p )
{
	int	c;
	int	erc;

	int	i = 0;
	char	*t = p;

	/*
	 *	character state -- get a character and figure out what to
	 *	do wit it.
	 */

char_state:
	if ( (c = getchar()) == EOF )
	{
		if ( i == 0 )
		{
			erc = EOF;
		}
		else
		{
			erc = UNQUOTED_STRING;
		}

		goto done_state;
	}

	switch ( c )
	{
		case '\n' :			/* new line */
			Line_number++;

			if ( i == 0 )
			{
				if ( Token_on_line )
				{
					Token_on_line = FALSE;

					erc = NEWLINE;
					goto done_state;
				}
				else
				{
					goto char_state;
				}
			}
			else
			{
				ungetc(c, stdin);

				Token_on_line = TRUE;

				erc = UNQUOTED_STRING;
				goto done_state;
			}

			break;

		case '\t' :			/* whitespace */
		case ' ' :
			if ( i == 0 )
			{
				goto char_state;
			}
			else
			{
				erc = UNQUOTED_STRING;
				goto done_state;
			}

			break;

		case '{' :
			if ( i == 0 )
			{
				*t++ = c;

				erc = OPEN_BRACE;
			}
			else
			{
				erc = UNQUOTED_STRING;
			}

			Token_on_line = TRUE;

			goto done_state;

			break;

		case '}' :
			if ( i == 0 )
			{
				*t++ = c;

				erc = CLOSE_BRACE;
			}
			else
			{
				erc = UNQUOTED_STRING;
			}

			Token_on_line = TRUE;

			goto done_state;

			break;

		case '(' :			/* normal separators */
		case ')' :
		case '[' :
		case ']' :
		case '<' :
		case '>' :
		case '@' :
		case ';' :
		case ':' :
			if ( i == 0 )
			{
				*t++ = c;
				erc = SEPARATOR;
			}
			else
			{
				erc = UNQUOTED_STRING;
			}

			goto done_state;

			break;

		case '#' :			/* comment */
			if ( i > 0 )
			{
				erc = UNQUOTED_STRING;
				goto done_state;
			}
			else
			{
				goto comment_state;
			}

			break;

		case '"' :			/* quoted string */
			if ( i > 0 )
			{
				erc = UNQUOTED_STRING;
				goto done_state;
			}
			else
			{
				goto quoted_state;
			}

			break;

		default:			/* token */
			if ( i < MAX_STRING ) /* truncate if too long */
			{
				*t++ = c;
				i++;
			}

			Token_on_line = TRUE;

			goto char_state;

			break;
	}

	/*
	 *	comment state -- digest all characters up to new line
	 */

comment_state:
	if ( (c = getchar()) == EOF )
	{
		erc = EOF;
		goto done_state;
	}

	if ( c == '\n' )
	{
		ungetc(c, stdin);
		goto char_state;
	}

	goto comment_state;

	/*
	 *	quoted state -- handle strings like "characters"
	 */

quoted_state:
	if ( (c = getchar()) == EOF ) /* eof in string is an error */
	{
		erc = UNKNOWN;
		goto done_state;
	}

	if ( c == '"' )			/* end of string */
	{
		erc = STRING;
		goto done_state;
	}

	if ( c == '\n' )		/* newline in string an error */
	{
		Line_number++;
		erc = UNKNOWN;

		goto done_state;
	}

	if ( i < MAX_STRING )		/* truncate if too long */
	{
		*t++ = c;
		i++;
	}

	goto quoted_state;

	/*
	 *	done state	-- terminate the token.
	 *			-- If the token if type UNQUOTED_STRING,
	 *			-- see if it is really a number,
	 *			-- and if so, try to convert it.
	 */

done_state:
	*t = '\0';

	if ( erc == UNQUOTED_STRING )
	{
		if ( (*p == '.') || (*p == '+') || (*p == '-') || isdigit(*p) )
		{
			erc = number(p);
		}
	}

	return (erc);
}

/*
 *	yylex
 *
 *	The lexical analyzer.
 */

int
yylex( void )
{
	int	erc;
	char	*p;
	char	token[MAX_STRING + 1];

	/*
	 *	Get a token.
	 */

	erc = get_token(token);

	/*
	 *	Perform the proper token specific action.
	 */

	switch ( erc )
	{
		case UNQUOTED_STRING:
			for ( erc = 0; erc < NUM_KEYWORDS; erc++ )
			{
				if ( strcmp(token, Keyword_table[erc].token)
									== 0 )
				{
					return (Keyword_table[erc].value);
				}
			}

			erc = STRING;

			/* fall through */

		case STRING:
			p = malloc(strlen(token) + 1);

			if ( p == (char *) NULL )
			{
				erc = MEMORY_ERROR;
			}
			else
			{
				(void) strcpy(p, token);

				yylval.ptr = p;
			}

			break;

		case INTEGER:
		case FLOAT:
		case EOF:
		case NEWLINE:
		case OPEN_BRACE:
		case CLOSE_BRACE:
			break;

		case SEPARATOR:
			erc = token[0];
			break;

		default:
			erc = INTERNAL_ERROR;
			break;
	}

	/*
	 *	Return status.
	 */

	return (erc);
}
