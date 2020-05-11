/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 67 "grammar.y" /* yacc.c:1909  */

	char	*ptr;
	long	integer;
	double	floating;

#line 138 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
