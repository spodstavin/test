/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "grammar.y" /* yacc.c:339  */

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

#line 131 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    DEFAULT_BLOCK_SIZE = 258,
    DEFAULT_READ_FRACTION = 259,
    DEFAULT_STARTING_BLOCK = 260,
    DEFAULT_TEST_AREA_SIZE = 261,
    DEFAULT_REQUESTS_PER_THREAD = 262,
    DEFAULT_THREADS_PER_DISK = 263,
    DEFAULT_ACCESS_PATTERN = 264,
    DEFAULT_WRITE_VERIFICATION = 265,
    DEFAULT_HISTOGRAM_UPPER_BOUND = 266,
    DEFAULT_HISTOGRAM_BINS = 267,
    BLOCK_SIZE = 268,
    READ_FRACTION = 269,
    STARTING_BLOCK = 270,
    TEST_AREA_SIZE = 271,
    REQUESTS_PER_THREAD = 272,
    THREADS_PER_DISK = 273,
    ACCESS_PATTERN = 274,
    MEMORY_ERROR = 275,
    INTERNAL_ERROR = 276,
    WRITE_VERIFICATION = 277,
    HISTOGRAM_UPPER_BOUND = 278,
    HISTOGRAM_BINS = 279,
    DISK = 280,
    RANDOM = 281,
    SEQUENTIAL = 282,
    ENABLED = 283,
    DISABLED = 284,
    FLOAT = 285,
    INTEGER = 286,
    STRING = 287,
    UNKNOWN = 288,
    KEYWORD = 289,
    SEPARATOR = 290,
    NEWLINE = 291,
    OPEN_BRACE = 292,
    CLOSE_BRACE = 293,
    UNQUOTED_STRING = 294
  };
#endif
/* Tokens.  */
#define DEFAULT_BLOCK_SIZE 258
#define DEFAULT_READ_FRACTION 259
#define DEFAULT_STARTING_BLOCK 260
#define DEFAULT_TEST_AREA_SIZE 261
#define DEFAULT_REQUESTS_PER_THREAD 262
#define DEFAULT_THREADS_PER_DISK 263
#define DEFAULT_ACCESS_PATTERN 264
#define DEFAULT_WRITE_VERIFICATION 265
#define DEFAULT_HISTOGRAM_UPPER_BOUND 266
#define DEFAULT_HISTOGRAM_BINS 267
#define BLOCK_SIZE 268
#define READ_FRACTION 269
#define STARTING_BLOCK 270
#define TEST_AREA_SIZE 271
#define REQUESTS_PER_THREAD 272
#define THREADS_PER_DISK 273
#define ACCESS_PATTERN 274
#define MEMORY_ERROR 275
#define INTERNAL_ERROR 276
#define WRITE_VERIFICATION 277
#define HISTOGRAM_UPPER_BOUND 278
#define HISTOGRAM_BINS 279
#define DISK 280
#define RANDOM 281
#define SEQUENTIAL 282
#define ENABLED 283
#define DISABLED 284
#define FLOAT 285
#define INTEGER 286
#define STRING 287
#define UNKNOWN 288
#define KEYWORD 289
#define SEPARATOR 290
#define NEWLINE 291
#define OPEN_BRACE 292
#define CLOSE_BRACE 293
#define UNQUOTED_STRING 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 67 "grammar.y" /* yacc.c:355  */

	char	*ptr;
	long	integer;
	double	floating;

#line 255 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 272 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  57
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   98

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  121

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   134,   134,   236,   237,   240,   241,   244,   250,   261,
     267,   275,   276,   277,   278,   285,   286,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   301,   312,   322,
     332,   342,   352,   362,   367,   372,   373,   376,   381,   386,
     391,   392,   395,   400,   412,   424,   441,   458,   475,   492,
     509,   526,   538,   550,   575,   600,   677,   678,   681,   684,
     687,   690,   691,   692,   695,   696,   697,   698,   699,   700,
     701,   702,   703,   704
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEFAULT_BLOCK_SIZE",
  "DEFAULT_READ_FRACTION", "DEFAULT_STARTING_BLOCK",
  "DEFAULT_TEST_AREA_SIZE", "DEFAULT_REQUESTS_PER_THREAD",
  "DEFAULT_THREADS_PER_DISK", "DEFAULT_ACCESS_PATTERN",
  "DEFAULT_WRITE_VERIFICATION", "DEFAULT_HISTOGRAM_UPPER_BOUND",
  "DEFAULT_HISTOGRAM_BINS", "BLOCK_SIZE", "READ_FRACTION",
  "STARTING_BLOCK", "TEST_AREA_SIZE", "REQUESTS_PER_THREAD",
  "THREADS_PER_DISK", "ACCESS_PATTERN", "MEMORY_ERROR", "INTERNAL_ERROR",
  "WRITE_VERIFICATION", "HISTOGRAM_UPPER_BOUND", "HISTOGRAM_BINS", "DISK",
  "RANDOM", "SEQUENTIAL", "ENABLED", "DISABLED", "FLOAT", "INTEGER",
  "STRING", "UNKNOWN", "KEYWORD", "SEPARATOR", "NEWLINE", "OPEN_BRACE",
  "CLOSE_BRACE", "UNQUOTED_STRING", "$accept", "file", "expect_an_integer",
  "expect_a_float", "integer_ok", "integer_to_float", "float_ok",
  "float_bad", "statements", "statement", "default_statements",
  "default_block_size", "default_read_fraction", "default_starting_block",
  "default_test_area_size", "default_requests_per_thread",
  "default_threads_per_disk", "random", "sequential", "access_type",
  "default_access_pattern", "enabled", "disabled", "switch",
  "default_write_verification", "default_histogram_bins",
  "default_histogram_upper_bound", "block_size", "read_fraction",
  "starting_block", "test_area_size", "requests_per_thread",
  "threads_per_disk", "access_pattern", "write_verification",
  "histogram_bins", "histogram_upper_bound", "disk_definition_line",
  "disk_statement", "disk_options", "open_brace_line", "close_brace_line",
  "disk_option_statements", "disk_option_statement", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

#define YYPACT_NINF -24

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-24)))

#define YYTABLE_NINF -12

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       5,    -7,   -12,   -10,   -12,   -12,   -12,   -12,    18,    32,
     -10,   -12,    14,    55,    31,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,   -24,   -24,   -24,   -24,   -24,    25,   -24,   -24,
     -24,   -24,    27,   -24,   -24,   -24,   -24,    28,   -24,   -24,
      29,    30,    41,    42,   -24,   -24,   -24,   -24,    44,   -24,
     -24,   -24,   -24,    45,    46,    47,    36,   -24,   -24,    48,
     -24,    35,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,    49,   -24,   -12,   -10,   -12,   -12,   -12,   -12,
      18,    32,   -10,   -12,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,   -24,   -24,     9,   -24,   -24,    50,    51,    52,
      53,    54,    56,    57,    58,    59,    60,    61,   -24,   -24,
     -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -24
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,    12,    15,    17,    18,    19,
      20,    21,    22,    23,    24,    26,    25,    56,    16,    14,
      10,     7,     0,     3,     4,     9,     8,     0,     6,     5,
       0,     0,     0,     0,    33,    34,    35,    36,     0,    38,
      39,    40,    41,     0,     0,     0,     0,     1,    13,     0,
      57,    61,    27,    28,    29,    30,    31,    32,    37,    42,
      44,    43,     0,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,     0,    62,    55,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    58,    63,
      45,    46,    47,    48,    49,    50,    51,    52,    54,    53,
      60
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -24,   -24,    -4,    -6,   -24,   -24,   -24,   -24,   -24,    77,
     -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -13,
     -24,   -24,   -24,    17,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,   -24,   -23
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    13,    32,    37,    33,    38,    39,    34,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    46,    47,    48,
      23,    51,    52,    53,    24,    25,    26,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    27,    28,    60,
      61,   108,    94,    95
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      40,    41,    42,    43,    54,   -11,     1,    55,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    30,    31,
      35,    36,    74,    75,    76,    77,    78,    79,    80,    29,
      12,    81,    82,    83,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    44,    45,    56,   107,    74,    75,
      76,    77,    78,    79,    80,    57,    12,    81,    82,    83,
      49,    50,    59,    62,    63,    64,    65,   103,    72,    98,
      97,   109,    99,   100,   101,   102,   105,    66,    67,   106,
      68,    69,    70,    71,    73,    96,   110,   111,   112,   113,
     114,    58,   115,   116,   117,   118,   119,   120,   104
};

static const yytype_uint8 yycheck[] =
{
       4,     5,     6,     7,    10,     0,     1,    11,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    30,    31,
      30,    31,    13,    14,    15,    16,    17,    18,    19,    36,
      25,    22,    23,    24,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    26,    27,    32,    38,    13,    14,
      15,    16,    17,    18,    19,     0,    25,    22,    23,    24,
      28,    29,    37,    36,    36,    36,    36,    80,    32,    75,
      74,    94,    76,    77,    78,    79,    82,    36,    36,    83,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    14,    36,    36,    36,    36,    36,    36,    81
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    25,    41,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    60,    64,    65,    66,    77,    78,    36,
      30,    31,    42,    44,    47,    30,    31,    43,    45,    46,
      42,    42,    42,    42,    26,    27,    57,    58,    59,    28,
      29,    61,    62,    63,    43,    42,    32,     0,    49,    37,
      79,    80,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    36,    32,    36,    13,    14,    15,    16,    17,    18,
      19,    22,    23,    24,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    82,    83,    36,    42,    43,    42,
      42,    42,    42,    59,    63,    43,    42,    38,    81,    83,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      36
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    44,    45,    46,
      47,    48,    48,    48,    48,    49,    49,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    59,    60,    61,    62,
      63,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    78,    79,    80,
      81,    82,    82,    82,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     1,     2,     3,     2,
       2,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 135 "grammar.y" /* yacc.c:1646  */
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
#line 1548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 245 "grammar.y" /* yacc.c:1646  */
    {
	(yyval.integer) = (yyvsp[0].integer);
}
#line 1556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 251 "grammar.y" /* yacc.c:1646  */
    {
	if ( (yyvsp[0].integer) != 0 )
	{
		warning("INTEGER converted to FLOATING");
	}

	(yyval.floating) = (double) (yyvsp[0].integer);
}
#line 1569 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 262 "grammar.y" /* yacc.c:1646  */
    {
	(yyval.floating) = (yyvsp[0].floating);
}
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 268 "grammar.y" /* yacc.c:1646  */
    {
	yyerror("expecting INTEGER; got FLOATING");

	(yyval.integer) = (unsigned long) (yyvsp[0].floating);
}
#line 1587 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 279 "grammar.y" /* yacc.c:1646  */
    {
	yyerrok;
	yyclearin;
}
#line 1596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 302 "grammar.y" /* yacc.c:1646  */
    {
	if ( ((yyvsp[-1].integer) <= 0) || ((yyvsp[-1].integer) % DISK_BLOCK_SIZE) )
	{
		invalid(DEFAULT_BLOCK_SIZE_KEYWORD);
	}

	Default_block_size = (yyvsp[-1].integer);
}
#line 1609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 313 "grammar.y" /* yacc.c:1646  */
    {
	if ( ((yyvsp[-1].floating) < 0.0) || ((yyvsp[-1].floating) > 1.0) )
	{
		invalid(DEFAULT_READ_FRACTION_KEYWORD);
	}

	Default_read_fraction = (yyvsp[-1].floating);
}
#line 1622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 323 "grammar.y" /* yacc.c:1646  */
    {
	if ( (yyvsp[-1].integer) <= 0 )
	{
		invalid(DEFAULT_STARTING_BLOCK_KEYWORD);
	}

	Default_starting_block = (yyvsp[-1].integer);
}
#line 1635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 333 "grammar.y" /* yacc.c:1646  */
    {
	if ( (yyvsp[-1].integer) <= 0 )
	{
		invalid(DEFAULT_TEST_AREA_SIZE_KEYWORD);
	}

	Default_test_area_size = (yyvsp[-1].integer);
}
#line 1648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 343 "grammar.y" /* yacc.c:1646  */
    {
	if ( (yyvsp[-1].integer) <= 0 )
	{
		invalid(DEFAULT_REQUESTS_PER_THREAD_KEYWORD);
	}

	Default_requests_per_thread = (yyvsp[-1].integer);
}
#line 1661 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 353 "grammar.y" /* yacc.c:1646  */
    {
	if ( (yyvsp[-1].integer) <= 0 )
	{
		invalid(DEFAULT_THREADS_PER_DISK_KEYWORD);
	}

	Default_threads_per_disk = (yyvsp[-1].integer);
}
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 363 "grammar.y" /* yacc.c:1646  */
    {
	(yyval.integer) = DISK_PATTERN_RANDOM;
}
#line 1682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 368 "grammar.y" /* yacc.c:1646  */
    {
	(yyval.integer) = DISK_PATTERN_SEQUENTIAL;
}
#line 1690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 377 "grammar.y" /* yacc.c:1646  */
    {
	Default_access_pattern = (yyvsp[-1].integer);
}
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 382 "grammar.y" /* yacc.c:1646  */
    {
	(yyval.integer) = TRUE;
}
#line 1706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 387 "grammar.y" /* yacc.c:1646  */
    {
	(yyval.integer) = FALSE;
}
#line 1714 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 396 "grammar.y" /* yacc.c:1646  */
    {
	Default_write_verification = (yyvsp[-1].integer);
}
#line 1722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 401 "grammar.y" /* yacc.c:1646  */
    {
	if ( (yyvsp[-1].integer) <= 2 )
	{
		invalid(DEFAULT_HISTOGRAM_BINS_KEYWORD);
	}

	Default_histogram_bins = (yyvsp[-1].integer);

	Default_metrics = TRUE;
}
#line 1737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 413 "grammar.y" /* yacc.c:1646  */
    {
	if ( (yyvsp[-1].floating) <= 0.0 )
	{
		invalid(DEFAULT_HISTOGRAM_UPPER_BOUND_KEYWORD);
	}

	Default_histogram_upper_bound = (yyvsp[-1].floating);

	Default_metrics = TRUE;
}
#line 1752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 425 "grammar.y" /* yacc.c:1646  */
    {
	if ( ((yyvsp[-1].integer) <= 0) || ((yyvsp[-1].integer) % DISK_BLOCK_SIZE) )
	{
		invalid(BLOCK_SIZE_KEYWORD);
	}

	Current_disk -> di_block_size = (yyvsp[-1].integer);

	if ( Block_size_present )
	{
		multiple_occurance(BLOCK_SIZE_KEYWORD);
	}

	Block_size_present = TRUE;
}
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 442 "grammar.y" /* yacc.c:1646  */
    {
	if ( ((yyvsp[-1].floating) < 0.0) || ((yyvsp[-1].floating) > 1.0) )
	{
		invalid(READ_FRACTION_KEYWORD);
	}

	Current_disk -> di_read_fraction = (yyvsp[-1].floating);

	if ( Read_fraction_present )
	{
		multiple_occurance(READ_FRACTION_KEYWORD);
	}

	Read_fraction_present = TRUE;
}
#line 1792 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 459 "grammar.y" /* yacc.c:1646  */
    {
	if ( (yyvsp[-1].integer) <= 0 )
	{
		invalid(STARTING_BLOCK_KEYWORD);
	}

	Current_disk -> di_starting_block = (yyvsp[-1].integer);

	if ( Starting_block_present )
	{
		multiple_occurance(STARTING_BLOCK_KEYWORD);
	}

	Starting_block_present = TRUE;
}
#line 1812 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 476 "grammar.y" /* yacc.c:1646  */
    {
	if ( (yyvsp[-1].integer) <= 0 )
	{
		invalid(TEST_AREA_SIZE_KEYWORD);
	}

	Current_disk -> di_test_area_size = (yyvsp[-1].integer);

	if ( Test_area_size_present )
	{
		multiple_occurance(TEST_AREA_SIZE_KEYWORD);
	}

	Test_area_size_present = TRUE;
}
#line 1832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 493 "grammar.y" /* yacc.c:1646  */
    {
	if ( (yyvsp[-1].integer) <= 0 )
	{
		invalid(REQUESTS_PER_THREAD_KEYWORD);
	}

	Current_disk -> di_requests_per_thread = (yyvsp[-1].integer);

	if ( Requests_per_thread_present )
	{
		multiple_occurance(REQUESTS_PER_THREAD_KEYWORD);
	}

	Requests_per_thread_present = TRUE;
}
#line 1852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 510 "grammar.y" /* yacc.c:1646  */
    {
	if ( (yyvsp[-1].integer) <= 0 )
	{
		invalid(THREADS_PER_DISK_KEYWORD);
	}

	Current_disk -> di_threads_per_disk = (yyvsp[-1].integer);

	if ( Threads_per_disk_present )
	{
		multiple_occurance(THREADS_PER_DISK_KEYWORD);
	}

	Threads_per_disk_present = TRUE;
}
#line 1872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 527 "grammar.y" /* yacc.c:1646  */
    {
	Current_disk -> di_access_pattern = (yyvsp[-1].integer);

	if ( Access_pattern_present )
	{
		multiple_occurance(ACCESS_PATTERN_KEYWORD);
	}

	Access_pattern_present = TRUE;
}
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 539 "grammar.y" /* yacc.c:1646  */
    {
	Current_disk -> di_write_verification = (yyvsp[-1].integer);

	if ( Write_verification_present )
	{
		multiple_occurance(WRITE_VERIFICATION_KEYWORD);
	}

	Write_verification_present = TRUE;
}
#line 1902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 551 "grammar.y" /* yacc.c:1646  */
    {
	if ( (yyvsp[-1].integer) <= 2 )
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

	Current_disk -> di_histogram_bins = (yyvsp[-1].integer);

	Histogram_bins_present = TRUE;
}
#line 1930 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 576 "grammar.y" /* yacc.c:1646  */
    {
	if ( (yyvsp[-1].floating) <= 0.0 )
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

	Current_disk -> di_histogram_upper_bound = (yyvsp[-1].floating);

	Histogram_upper_bound_present = TRUE;
}
#line 1958 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 601 "grammar.y" /* yacc.c:1646  */
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

	Current_disk -> di_block_device_name = (yyvsp[-2].ptr);
	Current_disk -> di_raw_device_name = (yyvsp[-1].ptr);
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
}
#line 2038 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2042 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 707 "grammar.y" /* yacc.c:1906  */


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
