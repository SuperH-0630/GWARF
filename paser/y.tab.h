/* A Bison parser, made by GNU Bison 3.5.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
    NUMBER = 258,
    INT = 259,
    STRING = 260,
    VAR = 261,
    ADD = 262,
    SUB = 263,
    DIV = 264,
    MUL = 265,
    EQ = 266,
    LESS = 267,
    MORE = 268,
    RB = 269,
    LB = 270,
    RP = 271,
    LP = 272,
    WHILE = 273,
    POW = 274,
    EQUAL = 275,
    MOREEQ = 276,
    LESSEQ = 277,
    NOTEQ = 278,
    BREAK = 279,
    IF = 280,
    ELSE = 281,
    ELIF = 282,
    BROKEN = 283,
    CONTINUE = 284,
    CONTINUED = 285,
    RESTART = 286,
    RESTARTED = 287,
    REGO = 288,
    REWENT = 289,
    RI = 290,
    LI = 291,
    DEFAULT = 292,
    FOR = 293,
    COMMA = 294,
    GLOBAL = 295,
    NONLOCAL = 296,
    INDENTA = 297,
    STOPN = 298,
    STOPF = 299,
    BLOCK = 300
  };
#endif
/* Tokens.  */
#define NUMBER 258
#define INT 259
#define STRING 260
#define VAR 261
#define ADD 262
#define SUB 263
#define DIV 264
#define MUL 265
#define EQ 266
#define LESS 267
#define MORE 268
#define RB 269
#define LB 270
#define RP 271
#define LP 272
#define WHILE 273
#define POW 274
#define EQUAL 275
#define MOREEQ 276
#define LESSEQ 277
#define NOTEQ 278
#define BREAK 279
#define IF 280
#define ELSE 281
#define ELIF 282
#define BROKEN 283
#define CONTINUE 284
#define CONTINUED 285
#define RESTART 286
#define RESTARTED 287
#define REGO 288
#define REWENT 289
#define RI 290
#define LI 291
#define DEFAULT 292
#define FOR 293
#define COMMA 294
#define GLOBAL 295
#define NONLOCAL 296
#define INDENTA 297
#define STOPN 298
#define STOPF 299
#define BLOCK 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 10 "gwarf_yacc.y"

    int int_value;
    double double_value;
    char *string_value;
    struct statement *statement_value;
    struct if_list *if_list_base;

#line 155 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
