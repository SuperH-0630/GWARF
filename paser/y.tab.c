/* A Bison parser, made by GNU Bison 3.5.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "gwarf_yacc.y"

    #include<stdio.h>
    #include"lex.yy.c"

    #ifndef _INTERPRETER_H
    #include"../inter/interpreter.h"
    #endif
    
    #define yylex yylex_self
    extern int yylex (void);
    // 此处声明：定义的token：INDENTA不会在yacc中被使用，但将会在lex中被使用

#line 83 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    LOG = 275,
    SQRT = 276,
    EQUAL = 277,
    MOREEQ = 278,
    LESSEQ = 279,
    NOTEQ = 280,
    BREAK = 281,
    IF = 282,
    ELSE = 283,
    ELIF = 284,
    BROKEN = 285,
    CONTINUE = 286,
    CONTINUED = 287,
    RESTART = 288,
    RESTARTED = 289,
    REGO = 290,
    REWENT = 291,
    RI = 292,
    LI = 293,
    DEFAULT = 294,
    FOR = 295,
    COMMA = 296,
    GLOBAL = 297,
    NONLOCAL = 298,
    INDENTA = 299,
    STOPN = 300,
    STOPF = 301,
    BLOCK = 302,
    FALSE = 303,
    TRUE = 304,
    NULL_token = 305,
    DEF = 306,
    RETURN = 307,
    CLASS = 308,
    POINT = 309,
    COLON = 310,
    TRY = 311,
    EXCEPT = 312,
    AS = 313,
    RAISE = 314,
    THROW = 315,
    IMPORT = 316,
    INCLUDE = 317,
    IN = 318,
    AND = 319,
    OR = 320,
    NOT = 321,
    MOD = 322,
    INTDIV = 323,
    AADD = 324,
    ASUB = 325,
    AMUL = 326,
    ADIV = 327,
    AMOD = 328,
    AINTDIV = 329,
    FADD = 330,
    FSUB = 331,
    APOW = 332,
    BITAND = 333,
    BITOR = 334,
    BITNOT = 335,
    BITNOTOR = 336,
    BITRIGHT = 337,
    BITLEFT = 338,
    PASS = 339,
    DO = 340,
    LAMBDA = 341,
    ASSERT = 342
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
#define LOG 275
#define SQRT 276
#define EQUAL 277
#define MOREEQ 278
#define LESSEQ 279
#define NOTEQ 280
#define BREAK 281
#define IF 282
#define ELSE 283
#define ELIF 284
#define BROKEN 285
#define CONTINUE 286
#define CONTINUED 287
#define RESTART 288
#define RESTARTED 289
#define REGO 290
#define REWENT 291
#define RI 292
#define LI 293
#define DEFAULT 294
#define FOR 295
#define COMMA 296
#define GLOBAL 297
#define NONLOCAL 298
#define INDENTA 299
#define STOPN 300
#define STOPF 301
#define BLOCK 302
#define FALSE 303
#define TRUE 304
#define NULL_token 305
#define DEF 306
#define RETURN 307
#define CLASS 308
#define POINT 309
#define COLON 310
#define TRY 311
#define EXCEPT 312
#define AS 313
#define RAISE 314
#define THROW 315
#define IMPORT 316
#define INCLUDE 317
#define IN 318
#define AND 319
#define OR 320
#define NOT 321
#define MOD 322
#define INTDIV 323
#define AADD 324
#define ASUB 325
#define AMUL 326
#define ADIV 327
#define AMOD 328
#define AINTDIV 329
#define FADD 330
#define FSUB 331
#define APOW 332
#define BITAND 333
#define BITOR 334
#define BITNOT 335
#define BITNOTOR 336
#define BITRIGHT 337
#define BITLEFT 338
#define PASS 339
#define DO 340
#define LAMBDA 341
#define ASSERT 342

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "gwarf_yacc.y"

    int int_value;
    double double_value;
    char *string_value;
    struct statement *statement_value;
    struct if_list *if_list_base;
    struct parameter *parameter_list;

#line 318 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  141
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1069

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  197
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  369

#define YYUNDEFTOK  2
#define YYMAXUTOK   342


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    46,    46,    51,    58,    69,    73,    77,    81,    85,
      89,    93,    97,   101,   105,   111,   117,   121,   125,   129,
     133,   137,   141,   145,   149,   153,   157,   161,   165,   173,
     180,   181,   190,   199,   208,   217,   226,   235,   244,   253,
     262,   271,   280,   292,   297,   302,   308,   314,   320,   330,
     335,   341,   347,   354,   362,   366,   371,   379,   387,   388,
     396,   407,   408,   418,   431,   432,   446,   447,   459,   460,
     472,   473,   486,   487,   496,   505,   514,   523,   532,   544,
     545,   558,   559,   571,   572,   585,   586,   596,   608,   609,
     618,   630,   631,   640,   649,   658,   671,   672,   686,   687,
     700,   701,   710,   719,   731,   732,   745,   746,   758,   759,
     771,   772,   789,   809,   815,   824,   830,   840,   841,   842,
     849,   862,   874,   886,   898,   910,   922,   923,   931,   944,
     951,   960,   974,   988,  1003,  1004,  1009,  1018,  1029,  1030,
    1038,  1048,  1049,  1057,  1067,  1068,  1076,  1086,  1087,  1095,
    1105,  1106,  1114,  1124,  1125,  1132,  1142,  1147,  1156,  1162,
    1171,  1182,  1189,  1200,  1207,  1218,  1229,  1240,  1251,  1262,
    1273,  1284,  1295,  1308,  1318,  1331,  1339,  1346,  1357,  1365,
    1378,  1389,  1395,  1404,  1413,  1425,  1432,  1446,  1463,  1470,
    1483,  1498,  1499,  1500,  1505,  1506,  1507,  1508
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "INT", "STRING", "VAR", "ADD",
  "SUB", "DIV", "MUL", "EQ", "LESS", "MORE", "RB", "LB", "RP", "LP",
  "WHILE", "POW", "LOG", "SQRT", "EQUAL", "MOREEQ", "LESSEQ", "NOTEQ",
  "BREAK", "IF", "ELSE", "ELIF", "BROKEN", "CONTINUE", "CONTINUED",
  "RESTART", "RESTARTED", "REGO", "REWENT", "RI", "LI", "DEFAULT", "FOR",
  "COMMA", "GLOBAL", "NONLOCAL", "INDENTA", "STOPN", "STOPF", "BLOCK",
  "FALSE", "TRUE", "NULL_token", "DEF", "RETURN", "CLASS", "POINT",
  "COLON", "TRY", "EXCEPT", "AS", "RAISE", "THROW", "IMPORT", "INCLUDE",
  "IN", "AND", "OR", "NOT", "MOD", "INTDIV", "AADD", "ASUB", "AMUL",
  "ADIV", "AMOD", "AINTDIV", "FADD", "FSUB", "APOW", "BITAND", "BITOR",
  "BITNOT", "BITNOTOR", "BITRIGHT", "BITLEFT", "PASS", "DO", "LAMBDA",
  "ASSERT", "$accept", "command_block", "command_list", "command",
  "top_exp", "eq_number", "formal_parameter", "arguments",
  "slice_arguments", "slice_arguments_token", "call_number", "lambda_exp",
  "chose_exp", "bool_or", "bool_and", "bool_not", "third_number",
  "bit_or_not", "bit_or", "bit_and", "bit_move", "second_number",
  "first_number", "negative", "bit_not", "zero_number", "attribute",
  "call_down", "call_slice", "iter_value", "list_arguments",
  "dict_arguments", "element", "base_value", "base_var_", "base_var_token",
  "base_string", "nonlocal_token", "global_token", "default_token",
  "return_exp", "return_token", "restarted_exp", "restarted_token",
  "restart_exp", "restart_token", "continued_exp", "continued_token",
  "continue_exp", "continue_token", "break_exp", "break_token",
  "broken_exp", "broken_token", "if_block", "elif_exp", "if_exp",
  "block_block", "block_exp", "for_block", "for_exp", "include_exp",
  "import_exp", "raise_exp", "try_block", "try_exp", "try_token",
  "do_while_block", "while_block", "while_exp", "class_block", "class_exp",
  "def_block", "def_exp", "block", "stop_token", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342
};
# endif

#define YYPACT_NINF (-153)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     484,  -153,  -153,  -153,  -153,   249,   194,   223,    -8,  -153,
       0,  -153,  -153,  -153,  -153,  -153,    63,    63,   950,    14,
       7,    14,    14,  -153,  -153,  -153,  -153,   223,  -153,   223,
    -153,   950,   950,   950,   950,   989,   278,   278,   274,    -7,
     950,    33,   484,  -153,    63,  -153,     8,  -153,    12,   -30,
     -19,  -153,    41,   -44,   -29,   -26,     4,   115,    38,  -153,
    -153,   112,     1,  -153,    23,  -153,  -153,  -153,  -153,  -153,
      67,    63,    63,    63,    63,   950,    63,   223,    63,   223,
      63,   223,    63,   223,    63,   223,    63,   223,    84,    -7,
      63,    -7,    63,    -7,    63,    63,    63,    63,    -7,    -7,
      63,    63,    -7,    63,    -7,    63,    -7,   950,  -153,   950,
     -12,    35,    10,   950,    -5,    65,   950,   950,  -153,  -153,
      92,    92,    52,   -20,   223,   649,  -153,  -153,    76,    78,
     950,  -153,    37,  -153,    41,    85,    85,   112,   335,    -4,
     950,  -153,  -153,    92,   950,   548,   950,   950,   950,   950,
     950,   950,  -153,  -153,   950,   974,   974,   974,   989,   989,
     989,   989,   989,   989,   989,   989,   989,   989,   989,   989,
     989,   989,   989,   989,   989,   274,   274,   274,   274,   950,
    -153,    92,    92,    92,    92,   223,    92,  -153,    92,  -153,
      92,  -153,    92,  -153,    92,  -153,    92,  -153,  -153,    87,
      -7,    92,  -153,    92,  -153,    92,  -153,    92,    92,    92,
      92,  -153,    40,    92,    92,  -153,    92,  -153,    92,  -153,
     104,  -153,   974,   950,  -153,    34,   706,    52,  -153,   223,
     223,   111,   132,  -153,  -153,    14,  -153,   950,  -153,   728,
     116,    96,   570,   627,  -153,   223,   335,   145,   420,   147,
    -153,    -2,  -153,  -153,   950,  -153,  -153,    15,   154,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,   100,   -19,  -153,   -44,
     -44,   -44,   -44,   -44,   -44,   -29,   -26,     4,   115,   115,
      38,    38,  -153,  -153,  -153,  -153,     1,     1,     1,  -153,
     -24,   784,  -153,  -153,   950,  -153,   109,    12,  -153,   974,
     950,   160,   173,  -153,  -153,  -153,  -153,  -153,   792,   149,
     840,   950,  -153,   180,    16,  -153,    18,  -153,    65,  -153,
    -153,  -153,  -153,  -153,  -153,   950,   950,   974,  -153,  -153,
    -153,   137,  -153,   179,   223,    12,  -153,   950,   223,  -153,
     181,   848,   896,   153,   187,  -153,  -153,  -153,   192,  -153,
      12,  -153,  -153,  -153,  -153,  -153,  -153,   191,  -153,   196,
     935,  -153,   950,  -153,  -153,  -153,   198,  -153,  -153
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   120,   121,   129,   128,     0,     0,     0,     0,   152,
       0,   155,   149,   146,   143,   140,     0,     0,     0,     0,
       0,     0,     0,   162,   124,   123,   125,     0,   137,     0,
     180,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     3,     0,    29,    30,    58,    61,    64,
      66,    68,    70,    72,    79,    81,    83,    85,    88,    91,
      96,    98,   100,   104,   106,   108,   110,   117,   118,   126,
     122,     0,     0,     0,     0,   134,     0,   138,     0,   141,
       0,   144,     0,   147,     0,   150,     0,   153,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    97,     0,
       0,    43,     0,     0,     0,     0,     0,     0,   194,   195,
      14,    15,   113,     0,     0,     0,   132,   131,     0,     0,
       0,   176,     0,   173,    71,    40,    42,    99,     0,     0,
       0,     1,     4,     5,     0,     0,     0,     0,     0,     0,
       0,     0,    39,    41,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     130,    19,    17,    16,    22,   135,    13,   139,    12,   142,
      11,   145,    10,   148,     8,   151,     9,   154,   159,     0,
       0,     7,   156,    20,   161,    18,   163,    27,    26,    25,
      24,   178,     0,    28,     6,   183,    23,   185,    21,   188,
       0,    44,     0,     0,   119,     0,     0,     0,   112,     0,
       0,     0,     0,   197,   196,     0,   111,     0,   133,     0,
       0,   110,     0,     0,   175,     0,     0,     0,     0,     0,
     181,     0,   177,    31,     0,    59,    49,     0,   118,    32,
      33,    34,    35,    36,    37,    38,     0,    67,    69,    75,
      74,    73,    76,    77,    78,    80,    82,    84,    86,    87,
      89,    90,    93,    92,    94,    95,   101,   102,   103,   105,
       0,     0,    54,   136,     0,   157,     0,    62,    45,     0,
       0,    46,     0,   115,   184,   160,   127,   114,     0,     0,
       0,     0,   189,    43,     0,   186,     0,   174,   110,   193,
     191,   192,   182,    53,    60,     0,     0,     0,   107,    57,
     109,    56,    55,     0,     0,    63,    47,     0,     0,   164,
       0,     0,     0,     0,     0,   190,   187,    50,   118,    51,
      65,   158,   179,    48,   116,   167,   166,     0,   165,     0,
       0,   172,     0,   170,   168,   169,     0,    52,   171
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -153,  -153,   206,   -41,    -6,   258,   -28,   -21,  -153,   -78,
     144,  -153,  -152,  -153,    59,    62,   188,   -18,    60,    51,
      64,   -16,    19,   -57,   220,   197,   -27,    56,  -153,  -153,
    -153,  -153,    11,  -153,  -139,   -17,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -130,
    -153,  -153,  -153,  -153,   -31,    82
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    41,   248,    43,    44,    45,   112,   257,   291,   292,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
     123,   114,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,   200,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   249,   120
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     111,   142,   124,   266,   126,   127,   258,   116,   139,   250,
     138,   228,   122,   328,     8,   117,     8,   236,   115,   144,
       4,   237,   125,   145,   225,   130,   131,   132,   133,   324,
     345,   329,   346,   141,   140,   156,   229,   164,   128,   155,
     129,   118,   119,   233,   234,   157,   223,   171,   172,   224,
     165,   226,   166,   158,   159,   178,   325,   226,   202,   325,
     204,   179,   206,   160,   161,   162,   163,   211,   212,   185,
     297,   215,   180,   217,   222,   219,   230,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   167,   168,   187,   235,
     189,   242,   191,   243,   193,   245,   195,   296,   197,   121,
     145,   220,   294,   221,   258,   173,   174,   227,   118,   119,
     231,   232,   198,   199,   282,   283,   284,   285,   224,   240,
     299,   322,   169,   170,   244,   304,   143,   155,   327,   118,
     119,   175,   176,   177,   252,   238,   241,   233,   234,   256,
     269,   270,   271,   272,   273,   274,   305,   335,   286,   287,
     288,   278,   279,   181,   182,   183,   184,   310,   186,   311,
     188,   319,   190,   321,   192,   326,   194,   334,   196,   295,
     201,   337,   203,   290,   205,   350,   207,   208,   209,   210,
     135,   136,   213,   214,   338,   216,   348,   218,   280,   281,
     341,   223,   329,   351,   360,   355,   293,     1,     2,     3,
       4,   361,     5,   362,   109,   363,    42,   142,   110,     6,
     364,     7,   368,   332,   314,   267,   276,   298,   306,   268,
     301,   251,   316,   134,   275,   108,     1,     2,     3,     4,
     277,   307,    18,   309,   289,   137,   313,   256,   107,     0,
     302,   303,    24,    25,    26,     0,     0,     0,   323,     0,
       0,     0,     1,     2,     3,     4,   317,   318,     0,     0,
      35,   113,     0,     0,   107,     0,     7,     0,     0,    36,
      37,    24,    25,    26,    38,     0,     0,     1,     2,     3,
       4,     1,     2,     3,     4,   331,     5,    18,   333,   107,
       0,     7,     0,     6,   336,     7,     0,    24,    25,    26,
       0,     0,   340,     0,   343,   344,     0,     0,     0,     0,
       0,     0,    18,     0,     0,     0,    18,     0,     0,   347,
     349,     0,    24,    25,    26,     0,    24,    25,    26,    38,
       0,   353,     0,     0,     0,   357,   359,     0,     1,     2,
       3,     4,     0,     5,    35,   352,     0,     0,     0,   354,
       6,     0,   246,     8,   366,     0,   367,     0,    38,     0,
       0,     9,    10,     0,     0,    11,    12,    13,    14,    15,
      16,    17,     0,    18,    19,    20,     0,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,    29,     0,
       0,    30,     0,     0,    31,    32,    33,    34,     0,     0,
       0,    35,   253,     0,   259,   260,   261,   262,   263,   264,
      36,    37,   265,     0,     0,    38,     0,     0,     0,   247,
      39,     0,    40,     1,     2,     3,     4,     0,     5,     0,
       0,     0,     0,     0,     0,     6,   320,     7,     8,     0,
       0,     0,     0,     0,     0,     0,     9,    10,     0,     0,
      11,    12,    13,    14,    15,    16,    17,     0,    18,    19,
      20,     0,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,    29,     0,     0,    30,     0,     0,    31,
      32,    33,    34,     0,     0,     0,    35,     1,     2,     3,
       4,     0,     5,     0,     0,    36,    37,     0,     0,     6,
      38,     7,     8,     0,     0,    39,     0,    40,     0,     0,
       9,    10,     0,     0,    11,    12,    13,    14,    15,    16,
      17,     0,    18,    19,    20,     0,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,    29,     0,     0,
      30,     0,     0,    31,    32,    33,    34,     0,     0,     0,
      35,     1,     2,     3,     4,     0,     5,     0,   254,    36,
      37,     0,   255,     6,    38,     7,     0,     0,     0,    39,
       0,    40,     0,     1,     2,     3,     4,     0,     5,     0,
     109,     0,     0,     0,   312,     6,    18,     7,     0,     0,
       0,     0,     0,     0,     0,     0,    24,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    18,     0,
       0,     0,     0,     0,    35,     0,     0,     0,    24,    25,
      26,     0,     0,    36,    37,     0,     0,     0,    38,     0,
       1,     2,     3,     4,     0,     5,    35,   254,     0,     0,
       0,   315,     6,     0,     7,    36,    37,     0,     0,     0,
      38,     0,     1,     2,     3,     4,     0,     5,     0,     0,
       0,     0,     0,     0,     6,    18,     7,     0,     0,     0,
       0,     0,     0,     0,     0,    24,    25,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    18,     0,     0,
     239,     0,     0,    35,     0,     0,     0,    24,    25,    26,
       0,     0,    36,    37,     0,     0,     0,    38,     0,     1,
       2,     3,     4,     0,     5,    35,   300,     0,     0,     0,
       0,     6,     0,     7,    36,    37,     0,     0,     0,    38,
       0,     1,     2,     3,     4,     0,     5,     0,     0,     0,
       0,     0,     0,     6,    18,     7,     0,     0,     0,     0,
       0,     0,     0,     0,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,     0,     0,   308,
       0,     0,    35,     0,     0,     0,    24,    25,    26,     0,
       0,    36,    37,     0,     0,     0,    38,     1,     2,     3,
       4,     0,     5,     0,    35,     1,     2,     3,     4,     6,
       5,     7,     0,    36,    37,     0,   339,     6,    38,     7,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   330,    18,     0,     0,     0,     0,     0,     0,     0,
      18,     0,    24,    25,    26,     0,     0,     0,     0,     0,
      24,    25,    26,     1,     2,     3,     4,     0,     5,     0,
      35,     1,     2,     3,     4,     6,     5,     7,    35,    36,
      37,     0,   356,     6,    38,     7,     0,    36,    37,     0,
       0,     0,    38,     0,     0,     0,     0,     0,    18,     0,
       0,   342,     0,     0,     0,     0,    18,     0,    24,    25,
      26,     0,     0,     0,     0,     0,    24,    25,    26,     1,
       2,     3,     4,     0,     5,     0,    35,     0,     0,     0,
     358,     6,     0,     7,    35,    36,    37,     0,     0,     0,
      38,     0,     0,    36,    37,     0,     0,     0,    38,     0,
       0,     0,     0,     0,    18,     0,     0,     0,     1,     2,
       3,     4,     0,     5,    24,    25,    26,     0,     0,   365,
       6,     0,     7,     1,     2,     3,     4,     0,     5,     0,
       0,     0,    35,     0,     0,     6,     0,     7,     0,     0,
       0,    36,    37,    18,     0,     0,    38,     1,     2,     3,
       4,     0,     5,    24,    25,    26,     0,     0,    18,   107,
       0,     7,     1,     2,     3,     4,     0,     5,    24,    25,
      26,    35,     0,     0,   107,     0,     7,     0,     0,     0,
      36,    37,    18,     0,     0,    38,    35,     0,     0,     0,
       0,     0,    24,    25,    26,    36,    37,    18,     0,     0,
      38,     0,     0,     0,     0,     0,     0,    24,    25,    26,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38
};

static const yytype_int16 yycheck[] =
{
       6,    42,    19,   155,    21,    22,   145,    15,    39,   139,
      17,    16,    18,    37,    18,    15,    18,    37,     7,    11,
       6,    41,    15,    15,    14,    31,    32,    33,    34,    14,
      14,    55,    14,     0,    40,    65,    41,    81,    27,    27,
      29,    45,    46,    45,    46,    64,    11,     9,    10,    14,
      79,    41,    78,    12,    13,    54,    41,    41,    89,    41,
      91,    38,    93,    22,    23,    24,    25,    98,    99,    75,
     222,   102,     5,   104,    86,   106,    11,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    82,    83,    77,    37,
      79,    15,    81,    15,    83,    58,    85,    57,    87,    17,
      15,   107,    15,   109,   243,    67,    68,   113,    45,    46,
     116,   117,    28,    29,   171,   172,   173,   174,    14,   125,
      86,   251,     7,     8,   130,    14,    44,    27,    28,    45,
      46,    19,    20,    21,   140,   124,   125,    45,    46,   145,
     158,   159,   160,   161,   162,   163,    14,   299,   175,   176,
     177,   167,   168,    71,    72,    73,    74,    41,    76,    63,
      78,    16,    80,    16,    82,    11,    84,    58,    86,   200,
      88,    11,    90,   179,    92,   327,    94,    95,    96,    97,
      36,    37,   100,   101,    11,   103,   325,   105,   169,   170,
      41,    11,    55,    14,    41,    14,   185,     3,     4,     5,
       6,    14,     8,    11,    10,    14,     0,   248,    14,    15,
      14,    17,    14,   291,   242,   156,   165,   223,   235,   157,
     226,   139,   243,    35,   164,     5,     3,     4,     5,     6,
     166,   237,    38,   239,   178,    38,   242,   243,    15,    -1,
     229,   230,    48,    49,    50,    -1,    -1,    -1,   254,    -1,
      -1,    -1,     3,     4,     5,     6,   245,   246,    -1,    -1,
      66,    38,    -1,    -1,    15,    -1,    17,    -1,    -1,    75,
      76,    48,    49,    50,    80,    -1,    -1,     3,     4,     5,
       6,     3,     4,     5,     6,   291,     8,    38,   294,    15,
      -1,    17,    -1,    15,   300,    17,    -1,    48,    49,    50,
      -1,    -1,   308,    -1,   310,   311,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    -1,    38,    -1,    -1,   325,
     326,    -1,    48,    49,    50,    -1,    48,    49,    50,    80,
      -1,   337,    -1,    -1,    -1,   341,   342,    -1,     3,     4,
       5,     6,    -1,     8,    66,   334,    -1,    -1,    -1,   338,
      15,    -1,    17,    18,   360,    -1,   362,    -1,    80,    -1,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    38,    39,    40,    -1,    42,    43,    -1,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    -1,
      -1,    56,    -1,    -1,    59,    60,    61,    62,    -1,    -1,
      -1,    66,   144,    -1,   146,   147,   148,   149,   150,   151,
      75,    76,   154,    -1,    -1,    80,    -1,    -1,    -1,    84,
      85,    -1,    87,     3,     4,     5,     6,    -1,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    16,    17,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    38,    39,
      40,    -1,    42,    43,    -1,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,    59,
      60,    61,    62,    -1,    -1,    -1,    66,     3,     4,     5,
       6,    -1,     8,    -1,    -1,    75,    76,    -1,    -1,    15,
      80,    17,    18,    -1,    -1,    85,    -1,    87,    -1,    -1,
      26,    27,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    38,    39,    40,    -1,    42,    43,    -1,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    -1,    -1,
      56,    -1,    -1,    59,    60,    61,    62,    -1,    -1,    -1,
      66,     3,     4,     5,     6,    -1,     8,    -1,    10,    75,
      76,    -1,    14,    15,    80,    17,    -1,    -1,    -1,    85,
      -1,    87,    -1,     3,     4,     5,     6,    -1,     8,    -1,
      10,    -1,    -1,    -1,    14,    15,    38,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    48,    49,
      50,    -1,    -1,    75,    76,    -1,    -1,    -1,    80,    -1,
       3,     4,     5,     6,    -1,     8,    66,    10,    -1,    -1,
      -1,    14,    15,    -1,    17,    75,    76,    -1,    -1,    -1,
      80,    -1,     3,     4,     5,     6,    -1,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    38,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      41,    -1,    -1,    66,    -1,    -1,    -1,    48,    49,    50,
      -1,    -1,    75,    76,    -1,    -1,    -1,    80,    -1,     3,
       4,     5,     6,    -1,     8,    66,    10,    -1,    -1,    -1,
      -1,    15,    -1,    17,    75,    76,    -1,    -1,    -1,    80,
      -1,     3,     4,     5,     6,    -1,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    38,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,
      -1,    -1,    66,    -1,    -1,    -1,    48,    49,    50,    -1,
      -1,    75,    76,    -1,    -1,    -1,    80,     3,     4,     5,
       6,    -1,     8,    -1,    66,     3,     4,     5,     6,    15,
       8,    17,    -1,    75,    76,    -1,    14,    15,    80,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,     3,     4,     5,     6,    -1,     8,    -1,
      66,     3,     4,     5,     6,    15,     8,    17,    66,    75,
      76,    -1,    14,    15,    80,    17,    -1,    75,    76,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    -1,    -1,    -1,    -1,    38,    -1,    48,    49,
      50,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,     3,
       4,     5,     6,    -1,     8,    -1,    66,    -1,    -1,    -1,
      14,    15,    -1,    17,    66,    75,    76,    -1,    -1,    -1,
      80,    -1,    -1,    75,    76,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,     3,     4,
       5,     6,    -1,     8,    48,    49,    50,    -1,    -1,    14,
      15,    -1,    17,     3,     4,     5,     6,    -1,     8,    -1,
      -1,    -1,    66,    -1,    -1,    15,    -1,    17,    -1,    -1,
      -1,    75,    76,    38,    -1,    -1,    80,     3,     4,     5,
       6,    -1,     8,    48,    49,    50,    -1,    -1,    38,    15,
      -1,    17,     3,     4,     5,     6,    -1,     8,    48,    49,
      50,    66,    -1,    -1,    15,    -1,    17,    -1,    -1,    -1,
      75,    76,    38,    -1,    -1,    80,    66,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    75,    76,    38,    -1,    -1,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     8,    15,    17,    18,    26,
      27,    30,    31,    32,    33,    34,    35,    36,    38,    39,
      40,    42,    43,    47,    48,    49,    50,    51,    52,    53,
      56,    59,    60,    61,    62,    66,    75,    76,    80,    85,
      87,    89,    90,    91,    92,    93,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,    15,   112,    10,
      14,    92,    94,    38,   119,   120,    15,    15,    45,    46,
     163,   163,    92,   118,   123,    15,   123,   123,   120,   120,
      92,    92,    92,    92,   104,    98,    98,   113,    17,   162,
      92,     0,    91,   163,    11,    15,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    27,    65,    64,    12,    13,
      22,    23,    24,    25,    81,    79,    78,    82,    83,     7,
       8,     9,    10,    67,    68,    19,    20,    21,    54,    38,
       5,   163,   163,   163,   163,    92,   163,   120,   163,   120,
     163,   120,   163,   120,   163,   120,   163,   120,    28,    29,
     143,   163,   162,   163,   162,   163,   162,   163,   163,   163,
     163,   162,   162,   163,   163,   162,   163,   162,   163,   162,
      92,    92,    86,    11,    14,    14,    41,    92,    16,    41,
      11,    92,    92,    45,    46,    37,    37,    41,   120,    41,
      92,   120,    15,    15,    92,    58,    17,    84,    90,   162,
     157,   163,    92,    93,    10,    14,    92,    95,   122,    93,
      93,    93,    93,    93,    93,    93,   100,   102,   103,   105,
     105,   105,   105,   105,   105,   106,   107,   108,   109,   109,
     110,   110,   111,   111,   111,   111,   114,   114,   114,   115,
      92,    96,    97,   120,    15,   162,    57,   100,    92,    86,
      10,    92,   120,   120,    14,    14,   123,    92,    41,    92,
      41,    63,    14,    92,    94,    14,    95,   120,   120,    16,
      16,    16,   157,    92,    14,    41,    11,    28,    37,    55,
      37,    92,    97,    92,    58,   100,    92,    11,    11,    14,
      92,    41,    41,    92,    92,    14,    14,    92,   122,    92,
     100,    14,   120,    92,   120,    14,    14,    92,    14,    92,
      41,    14,    11,    14,    14,    14,    92,    92,    14
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    90,    90,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    92,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    94,    94,    94,    94,    94,    94,    95,
      95,    95,    95,    95,    96,    96,    96,    97,    98,    98,
      98,    99,    99,    99,   100,   100,   101,   101,   102,   102,
     103,   103,   104,   104,   104,   104,   104,   104,   104,   105,
     105,   106,   106,   107,   107,   108,   108,   108,   109,   109,
     109,   110,   110,   110,   110,   110,   111,   111,   112,   112,
     113,   113,   113,   113,   114,   114,   115,   115,   116,   116,
     117,   117,   117,   118,   118,   119,   119,   120,   120,   120,
     121,   121,   121,   121,   121,   121,   122,   122,   123,   124,
     124,   125,   126,   127,   128,   128,   128,   129,   130,   130,
     131,   132,   132,   133,   134,   134,   135,   136,   136,   137,
     138,   138,   139,   140,   140,   141,   142,   142,   143,   143,
     144,   145,   146,   147,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   149,   150,   151,   151,   151,   152,   153,
     154,   155,   155,   156,   157,   158,   159,   159,   160,   161,
     161,   162,   162,   162,   163,   163,   163,   163
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     1,     2,     3,     3,     4,     5,     1,
       3,     3,     5,     2,     1,     2,     2,     2,     1,     3,
       4,     1,     4,     5,     1,     5,     1,     3,     1,     3,
       1,     2,     1,     3,     3,     3,     3,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     2,     1,     2,
       1,     3,     3,     3,     1,     3,     1,     4,     1,     4,
       1,     3,     3,     1,     3,     3,     5,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     4,     1,     1,
       2,     2,     2,     3,     1,     2,     3,     1,     1,     2,
       1,     1,     2,     1,     1,     2,     1,     1,     2,     1,
       1,     2,     1,     1,     2,     1,     2,     3,     4,     1,
       4,     2,     1,     2,     5,     6,     6,     6,     7,     7,
       7,     8,     6,     2,     4,     3,     2,     3,     2,     5,
       1,     3,     4,     2,     4,     2,     4,     5,     2,     4,
       5,     3,     3,     3,     1,     1,     2,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 3:
#line 52 "gwarf_yacc.y"
    {
        if((yyvsp[0].statement_value) != NULL){
            statement *tmp = find_statement_list(0, statement_base);
            append_statement(tmp, (yyvsp[0].statement_value));
        }
    }
#line 1919 "y.tab.c"
    break;

  case 4:
#line 59 "gwarf_yacc.y"
    {   
        if((yyvsp[0].statement_value) != NULL){
            statement *tmp = find_statement_list(0, statement_base);
            append_statement(tmp, (yyvsp[0].statement_value));
        }
    }
#line 1930 "y.tab.c"
    break;

  case 5:
#line 70 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1938 "y.tab.c"
    break;

  case 6:
#line 74 "gwarf_yacc.y"
    {   
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1946 "y.tab.c"
    break;

  case 7:
#line 78 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1954 "y.tab.c"
    break;

  case 8:
#line 82 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1962 "y.tab.c"
    break;

  case 9:
#line 86 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1970 "y.tab.c"
    break;

  case 10:
#line 90 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1978 "y.tab.c"
    break;

  case 11:
#line 94 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1986 "y.tab.c"
    break;

  case 12:
#line 98 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1994 "y.tab.c"
    break;

  case 13:
#line 102 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2002 "y.tab.c"
    break;

  case 14:
#line 106 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = rego;
        (yyval.statement_value) = code_tmp;
    }
#line 2012 "y.tab.c"
    break;

  case 15:
#line 112 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = rewent;
        (yyval.statement_value) = code_tmp;
    }
#line 2022 "y.tab.c"
    break;

  case 16:
#line 118 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2030 "y.tab.c"
    break;

  case 17:
#line 122 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2038 "y.tab.c"
    break;

  case 18:
#line 126 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2046 "y.tab.c"
    break;

  case 19:
#line 130 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2054 "y.tab.c"
    break;

  case 20:
#line 134 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2062 "y.tab.c"
    break;

  case 21:
#line 138 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2070 "y.tab.c"
    break;

  case 22:
#line 142 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2078 "y.tab.c"
    break;

  case 23:
#line 146 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2086 "y.tab.c"
    break;

  case 24:
#line 150 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2094 "y.tab.c"
    break;

  case 25:
#line 154 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2102 "y.tab.c"
    break;

  case 26:
#line 158 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2110 "y.tab.c"
    break;

  case 27:
#line 162 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2118 "y.tab.c"
    break;

  case 28:
#line 166 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2126 "y.tab.c"
    break;

  case 29:
#line 174 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[0].statement_value);
    }
#line 2134 "y.tab.c"
    break;

  case 31:
#line 182 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ASSIGnMENT_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2147 "y.tab.c"
    break;

  case 32:
#line 191 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AADD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2160 "y.tab.c"
    break;

  case 33:
#line 200 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ASUB_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2173 "y.tab.c"
    break;

  case 34:
#line 209 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AMUL_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2186 "y.tab.c"
    break;

  case 35:
#line 218 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ADIV_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2199 "y.tab.c"
    break;

  case 36:
#line 227 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AMOD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2212 "y.tab.c"
    break;

  case 37:
#line 236 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AINTDIV_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2225 "y.tab.c"
    break;

  case 38:
#line 245 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = APOW_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2238 "y.tab.c"
    break;

  case 39:
#line 254 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LADD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-1].statement_value);
        code_tmp->code.operation.right_exp = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2251 "y.tab.c"
    break;

  case 40:
#line 263 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = FADD_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2264 "y.tab.c"
    break;

  case 41:
#line 272 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LSUB_func;
        code_tmp->code.operation.left_exp = (yyvsp[-1].statement_value);
        code_tmp->code.operation.right_exp = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2277 "y.tab.c"
    break;

  case 42:
#line 281 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = FSUB_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2290 "y.tab.c"
    break;

  case 43:
#line 293 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_name((yyvsp[0].statement_value));
        (yyval.parameter_list)->type = only_name;
    }
#line 2299 "y.tab.c"
    break;

  case 44:
#line 298 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_name((yyvsp[0].statement_value));
        (yyval.parameter_list)->type = put_args;
    }
#line 2308 "y.tab.c"
    break;

  case 45:
#line 303 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_name((yyvsp[-2].statement_value));
        (yyval.parameter_list)->u.value = (yyvsp[0].statement_value);
        (yyval.parameter_list)->type = name_value;
    }
#line 2318 "y.tab.c"
    break;

  case 46:
#line 309 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_name((yyvsp[0].statement_value), (yyvsp[-2].parameter_list));
        tmp->type = only_name;
        (yyval.parameter_list) = (yyvsp[-2].parameter_list);
    }
#line 2328 "y.tab.c"
    break;

  case 47:
#line 315 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_name((yyvsp[0].statement_value), (yyvsp[-3].parameter_list));
        tmp->type = put_args;
        (yyval.parameter_list) = (yyvsp[-3].parameter_list);
    }
#line 2338 "y.tab.c"
    break;

  case 48:
#line 321 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_name((yyvsp[-2].statement_value), (yyvsp[-4].parameter_list));
        tmp->u.value = (yyvsp[0].statement_value);
        tmp->type = name_value;
        (yyval.parameter_list) = (yyvsp[-4].parameter_list);
    }
#line 2349 "y.tab.c"
    break;

  case 49:
#line 331 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_value((yyvsp[0].statement_value));
        (yyval.parameter_list)->type = only_value;
    }
#line 2358 "y.tab.c"
    break;

  case 50:
#line 336 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_value((yyvsp[0].statement_value), (yyvsp[-2].parameter_list));
        tmp->type = only_value;
        (yyval.parameter_list) = (yyvsp[-2].parameter_list);
    }
#line 2368 "y.tab.c"
    break;

  case 51:
#line 342 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_name((yyvsp[-2].statement_value));
        (yyval.parameter_list)->u.value = (yyvsp[0].statement_value);
        (yyval.parameter_list)->type = name_value;
    }
#line 2378 "y.tab.c"
    break;

  case 52:
#line 348 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_name((yyvsp[-2].statement_value), (yyvsp[-4].parameter_list));
        tmp->u.value = (yyvsp[0].statement_value);
        tmp->type = name_value;
        (yyval.parameter_list) = (yyvsp[-4].parameter_list);
    }
#line 2389 "y.tab.c"
    break;

  case 53:
#line 355 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_value((yyvsp[0].statement_value));
        (yyval.parameter_list)->type = put_args;
    }
#line 2398 "y.tab.c"
    break;

  case 54:
#line 363 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_value((yyvsp[0].statement_value));
    }
#line 2406 "y.tab.c"
    break;

  case 55:
#line 367 "gwarf_yacc.y"
    {
        append_parameter_value((yyvsp[0].statement_value), (yyvsp[-1].parameter_list));
        (yyval.parameter_list) = (yyvsp[-1].parameter_list);
    }
#line 2415 "y.tab.c"
    break;

  case 56:
#line 372 "gwarf_yacc.y"
    {
        append_parameter_value((yyvsp[0].statement_value), (yyvsp[-1].parameter_list));
        (yyval.parameter_list) = (yyvsp[-1].parameter_list);
    }
#line 2424 "y.tab.c"
    break;

  case 57:
#line 380 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2432 "y.tab.c"
    break;

  case 59:
#line 389 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = (yyvsp[-2].statement_value);
        code_tmp->code.call.parameter_list = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2444 "y.tab.c"
    break;

  case 60:
#line 397 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = (yyvsp[-3].statement_value);
        code_tmp->code.call.parameter_list = (yyvsp[-1].parameter_list);
        (yyval.statement_value) = code_tmp;
    }
#line 2456 "y.tab.c"
    break;

  case 62:
#line 409 "gwarf_yacc.y"
    {
        statement *lambda_tmp =  make_statement();
        lambda_tmp->type = lambda_func;

        lambda_tmp->code.lambda_func.parameter_list = NULL;
        lambda_tmp->code.lambda_func.done = (yyvsp[0].statement_value);

        (yyval.statement_value) = lambda_tmp;
    }
#line 2470 "y.tab.c"
    break;

  case 63:
#line 419 "gwarf_yacc.y"
    {
        statement *lambda_tmp =  make_statement();
        lambda_tmp->type = lambda_func;

        lambda_tmp->code.lambda_func.parameter_list = (yyvsp[-3].parameter_list);
        lambda_tmp->code.lambda_func.done = (yyvsp[0].statement_value);

        (yyval.statement_value) = lambda_tmp;
    }
#line 2484 "y.tab.c"
    break;

  case 65:
#line 433 "gwarf_yacc.y"
    {
        statement *chose_tmp =  make_statement();
        chose_tmp->type = chose_exp;

        chose_tmp->code.chose_exp.condition = (yyvsp[-2].statement_value);
        chose_tmp->code.chose_exp.true_do = (yyvsp[-4].statement_value);
        chose_tmp->code.chose_exp.false_do = (yyvsp[0].statement_value);

        (yyval.statement_value) = chose_tmp;
    }
#line 2499 "y.tab.c"
    break;

  case 67:
#line 448 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = OR_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2512 "y.tab.c"
    break;

  case 69:
#line 461 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AND_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2525 "y.tab.c"
    break;

  case 71:
#line 474 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NOT_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        puts("NOT FUNC");
        (yyval.statement_value) = code_tmp;
    }
#line 2539 "y.tab.c"
    break;

  case 73:
#line 488 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = EQUAL_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2552 "y.tab.c"
    break;

  case 74:
#line 497 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MORE_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2565 "y.tab.c"
    break;

  case 75:
#line 506 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LESS_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2578 "y.tab.c"
    break;

  case 76:
#line 515 "gwarf_yacc.y"
        {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MOREEQ_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2591 "y.tab.c"
    break;

  case 77:
#line 524 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LESSEQ_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2604 "y.tab.c"
    break;

  case 78:
#line 533 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NOTEQ_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2617 "y.tab.c"
    break;

  case 80:
#line 546 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITNOTOR_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        puts("NOT FUNC");
        (yyval.statement_value) = code_tmp;
    }
#line 2631 "y.tab.c"
    break;

  case 82:
#line 560 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITOR_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2644 "y.tab.c"
    break;

  case 84:
#line 573 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITAND_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        puts("NOT FUNC");
        (yyval.statement_value) = code_tmp;
    }
#line 2658 "y.tab.c"
    break;

  case 86:
#line 587 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITRIGHT_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        puts("NOT FUNC");
        (yyval.statement_value) = code_tmp;
    }
#line 2672 "y.tab.c"
    break;

  case 87:
#line 597 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITLEFT_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2685 "y.tab.c"
    break;

  case 89:
#line 610 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ADD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2698 "y.tab.c"
    break;

  case 90:
#line 619 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = SUB_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2711 "y.tab.c"
    break;

  case 92:
#line 632 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MUL_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2724 "y.tab.c"
    break;

  case 93:
#line 641 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = DIV_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2737 "y.tab.c"
    break;

  case 94:
#line 650 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MOD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2750 "y.tab.c"
    break;

  case 95:
#line 659 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = INTDIV_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2763 "y.tab.c"
    break;

  case 97:
#line 673 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NEGATIVE_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2776 "y.tab.c"
    break;

  case 99:
#line 688 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITNOT_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2789 "y.tab.c"
    break;

  case 101:
#line 702 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = POW_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2802 "y.tab.c"
    break;

  case 102:
#line 711 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LOG_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2815 "y.tab.c"
    break;

  case 103:
#line 720 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = SQRT_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2828 "y.tab.c"
    break;

  case 105:
#line 733 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = point;
        code_tmp->code.point.base_var = (yyvsp[-2].statement_value);
        code_tmp->code.point.child_var = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp; 
    }
#line 2840 "y.tab.c"
    break;

  case 107:
#line 747 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = down;
        code_tmp->code.down.base_var = (yyvsp[-3].statement_value);
        code_tmp->code.down.child_var = (yyvsp[-1].statement_value);
        (yyval.statement_value) = code_tmp; 
    }
#line 2852 "y.tab.c"
    break;

  case 109:
#line 760 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = slice;
        code_tmp->code.slice.base_var = (yyvsp[-3].statement_value);
        code_tmp->code.slice.value = (yyvsp[-1].parameter_list);
        (yyval.statement_value) = code_tmp; 
    }
#line 2864 "y.tab.c"
    break;

  case 111:
#line 773 "gwarf_yacc.y"
    {
        parameter *tmp;
        tmp = malloc(sizeof(parameter));  // get an address for base var
        tmp->next = NULL;
        statement *statement_tmp = malloc(sizeof(statement));
        statement_tmp->type = base_list;
        statement_tmp->code.base_list.value = (yyvsp[-1].parameter_list);
        tmp->u.value = statement_tmp;

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("list", NULL);
        code_tmp->code.call.parameter_list = tmp;

        (yyval.statement_value) = code_tmp;
    }
#line 2885 "y.tab.c"
    break;

  case 112:
#line 790 "gwarf_yacc.y"
    {
        parameter *tmp;
        tmp = malloc(sizeof(parameter));  // get an address for base var
        tmp->next = NULL;
        statement *statement_tmp = malloc(sizeof(statement));
        statement_tmp->type = base_dict;
        statement_tmp->code.base_dict.value = (yyvsp[-1].parameter_list);
        tmp->u.value = statement_tmp;

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("dict", NULL);
        code_tmp->code.call.parameter_list = tmp;

        (yyval.statement_value) = code_tmp;
    }
#line 2906 "y.tab.c"
    break;

  case 113:
#line 810 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_value((yyvsp[0].statement_value));
        (yyval.parameter_list)->type = only_value;
        puts("Fss");
    }
#line 2916 "y.tab.c"
    break;

  case 114:
#line 816 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_value((yyvsp[0].statement_value), (yyvsp[-2].parameter_list));
        tmp->type = only_value;
        (yyval.parameter_list) = (yyvsp[-2].parameter_list);
    }
#line 2926 "y.tab.c"
    break;

  case 115:
#line 825 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_name((yyvsp[-2].statement_value));
        (yyval.parameter_list)->u.value = (yyvsp[0].statement_value);
        (yyval.parameter_list)->type = name_value;
    }
#line 2936 "y.tab.c"
    break;

  case 116:
#line 831 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_name((yyvsp[-2].statement_value), (yyvsp[-4].parameter_list));
        tmp->u.value = (yyvsp[0].statement_value);
        tmp->type = name_value;
        (yyval.parameter_list) = (yyvsp[-4].parameter_list);
    }
#line 2947 "y.tab.c"
    break;

  case 119:
#line 843 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2955 "y.tab.c"
    break;

  case 120:
#line 850 "gwarf_yacc.y"
    {
        // 调用double内置类的构造函数
        GWARF_value tmp_value;
        tmp_value.type = NUMBER_value;
        tmp_value.value.double_value = (double)(yyvsp[0].double_value);

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("double", NULL);
        code_tmp->code.call.parameter_list = pack_value_parameter(tmp_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2972 "y.tab.c"
    break;

  case 121:
#line 863 "gwarf_yacc.y"
    {
        GWARF_value tmp_value;
        tmp_value.type = INT_value;
        tmp_value.value.int_value = (int)(yyvsp[0].double_value);

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("int", NULL);
        code_tmp->code.call.parameter_list = pack_value_parameter(tmp_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2988 "y.tab.c"
    break;

  case 122:
#line 875 "gwarf_yacc.y"
    {
        GWARF_value tmp_value;
        tmp_value.type = STRING_value;
        tmp_value.value.string = (yyvsp[0].string_value);  // base_string已经动态生成内存了

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("str", NULL);
        code_tmp->code.call.parameter_list = pack_value_parameter(tmp_value);
        (yyval.statement_value) = code_tmp;
    }
#line 3004 "y.tab.c"
    break;

  case 123:
#line 887 "gwarf_yacc.y"
    {
        GWARF_value tmp_value;
        tmp_value.type = BOOL_value;
        tmp_value.value.bool_value = true;

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("bool", NULL);
        code_tmp->code.call.parameter_list = pack_value_parameter(tmp_value);
        (yyval.statement_value) = code_tmp;
    }
#line 3020 "y.tab.c"
    break;

  case 124:
#line 899 "gwarf_yacc.y"
    {
        GWARF_value tmp_value;
        tmp_value.type = BOOL_value;
        tmp_value.value.bool_value = false;

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("bool", NULL);
        code_tmp->code.call.parameter_list = pack_value_parameter(tmp_value);
        (yyval.statement_value) = code_tmp;
    }
#line 3036 "y.tab.c"
    break;

  case 125:
#line 911 "gwarf_yacc.y"
    {
        // NULL代表空值，是GWARF_value
        statement *code_tmp =  make_statement();
        code_tmp->type = base_value;
        code_tmp->code.base_value.value.type = NULL_value;
        code_tmp->code.base_value.value.value.int_value = 0;
        (yyval.statement_value) = code_tmp;
    }
#line 3049 "y.tab.c"
    break;

  case 127:
#line 924 "gwarf_yacc.y"
    {
        (yyvsp[0].statement_value)->code.base_var.from = (yyvsp[-2].statement_value);
        (yyval.statement_value) = (yyvsp[0].statement_value);
    }
#line 3058 "y.tab.c"
    break;

  case 128:
#line 932 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->code.base_var.var_name = malloc(sizeof((yyvsp[0].string_value)));
        char *name_tmp = code_tmp->code.base_var.var_name;
        code_tmp->type = base_var;
        code_tmp->code.base_var.from = NULL;
        strcpy(name_tmp, (yyvsp[0].string_value));
        (yyval.statement_value) = code_tmp;
    }
#line 3072 "y.tab.c"
    break;

  case 129:
#line 945 "gwarf_yacc.y"
    {
        // STRING is char * which the len is 1
        char *tmp = malloc(sizeof((yyvsp[0].string_value)));
        strcpy(tmp, (yyvsp[0].string_value));
        (yyval.string_value) = tmp;
    }
#line 3083 "y.tab.c"
    break;

  case 130:
#line 952 "gwarf_yacc.y"
    {
        char *tmp = realloc((yyvsp[-1].string_value), strlen((yyvsp[-1].string_value)) + strlen((yyvsp[0].string_value)));  // get address
        strcat(tmp, (yyvsp[0].string_value));
        (yyval.string_value) = tmp;
    }
#line 3093 "y.tab.c"
    break;

  case 131:
#line 961 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = set_nonlocal;
        code_tmp->code.set_nonlocal.name = malloc(sizeof((yyvsp[0].statement_value)->code.base_var.var_name));
        char *name_tmp = code_tmp->code.set_nonlocal.name;
        strcpy(name_tmp, (yyvsp[0].statement_value)->code.base_var.var_name);
        free((yyvsp[0].statement_value)->code.base_var.var_name);
        free((yyvsp[0].statement_value));
        (yyval.statement_value) = code_tmp;
    }
#line 3108 "y.tab.c"
    break;

  case 132:
#line 975 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = set_global;
        code_tmp->code.set_global.name = malloc(sizeof((yyvsp[0].statement_value)->code.base_var.var_name));
        char *name_tmp = code_tmp->code.set_global.name;
        strcpy(name_tmp, (yyvsp[0].statement_value)->code.base_var.var_name);
        free((yyvsp[0].statement_value)->code.base_var.var_name);
        free((yyvsp[0].statement_value));
        (yyval.statement_value) = code_tmp;
    }
#line 3123 "y.tab.c"
    break;

  case 133:
#line 989 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = set_default;
        code_tmp->code.set_default.times = (yyvsp[0].statement_value);
        code_tmp->code.set_default.name = malloc(sizeof((yyvsp[-1].statement_value)->code.base_var.var_name));
        char *name_tmp = code_tmp->code.set_default.name;
        strcpy(name_tmp, (yyvsp[-1].statement_value)->code.base_var.var_name);
        free((yyvsp[-1].statement_value)->code.base_var.var_name);
        free((yyvsp[-1].statement_value));
        (yyval.statement_value) = code_tmp;
    }
#line 3139 "y.tab.c"
    break;

  case 135:
#line 1005 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.return_code.value = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3148 "y.tab.c"
    break;

  case 136:
#line 1010 "gwarf_yacc.y"
    {
        (yyvsp[-2].statement_value)->code.return_code.value = (yyvsp[-1].statement_value);
        (yyvsp[-2].statement_value)->code.return_code.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-2].statement_value);
    }
#line 3158 "y.tab.c"
    break;

  case 137:
#line 1019 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = return_code;
        code_tmp->code.return_code.times = NULL;
        code_tmp->code.return_code.value = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3170 "y.tab.c"
    break;

  case 139:
#line 1031 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.restarted.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3179 "y.tab.c"
    break;

  case 140:
#line 1039 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = restarted;
        code_tmp->code.restarted.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3190 "y.tab.c"
    break;

  case 142:
#line 1050 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.restart.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3199 "y.tab.c"
    break;

  case 143:
#line 1058 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = restart;
        code_tmp->code.restart.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3210 "y.tab.c"
    break;

  case 145:
#line 1069 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.continued.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3219 "y.tab.c"
    break;

  case 146:
#line 1077 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = continued;
        code_tmp->code.continued.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3230 "y.tab.c"
    break;

  case 148:
#line 1088 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.continue_cycle.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3239 "y.tab.c"
    break;

  case 149:
#line 1096 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = continue_cycle;
        code_tmp->code.continue_cycle.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3250 "y.tab.c"
    break;

  case 151:
#line 1107 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.break_cycle.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3259 "y.tab.c"
    break;

  case 152:
#line 1115 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = break_cycle;
        code_tmp->code.break_cycle.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3270 "y.tab.c"
    break;

  case 154:
#line 1126 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.broken.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3279 "y.tab.c"
    break;

  case 155:
#line 1133 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = broken;
        code_tmp->code.broken.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3290 "y.tab.c"
    break;

  case 156:
#line 1143 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3299 "y.tab.c"
    break;

  case 157:
#line 1148 "gwarf_yacc.y"
    {
        append_elif((yyvsp[-1].if_list_base), (yyvsp[-2].statement_value)->code.if_branch.done);
        (yyval.statement_value) = (yyvsp[-2].statement_value);
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 3309 "y.tab.c"
    break;

  case 158:
#line 1157 "gwarf_yacc.y"
    {
        statement *done_tmp =  make_statement();
        (yyval.if_list_base) = make_if((yyvsp[-1].statement_value), done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
    }
#line 3319 "y.tab.c"
    break;

  case 159:
#line 1163 "gwarf_yacc.y"
    {
        statement *done_tmp =  make_statement();
        (yyval.if_list_base) = make_if(NULL, done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
    }
#line 3329 "y.tab.c"
    break;

  case 160:
#line 1172 "gwarf_yacc.y"
    {
        statement *if_tmp =  make_statement(), *done_tmp =  make_statement();
        if_tmp->type = if_branch;
        if_tmp->code.if_branch.done = make_if((yyvsp[-1].statement_value), done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = if_tmp;
    }
#line 3341 "y.tab.c"
    break;

  case 161:
#line 1183 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 3349 "y.tab.c"
    break;

  case 162:
#line 1190 "gwarf_yacc.y"
    {
        statement *block_tmp =  make_statement();
        block_tmp->type = code_block;
        block_tmp->code.code_block.done = make_statement();
        statement_base = append_statement_list(block_tmp->code.code_block.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = block_tmp;
    }
#line 3361 "y.tab.c"
    break;

  case 163:
#line 1201 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 3369 "y.tab.c"
    break;

  case 164:
#line 1208 "gwarf_yacc.y"
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = NULL;
        for_tmp->code.for_cycle.condition = NULL;
        for_tmp->code.for_cycle.after = NULL;
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = for_tmp;
    }
#line 3384 "y.tab.c"
    break;

  case 165:
#line 1219 "gwarf_yacc.y"
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = (yyvsp[-3].statement_value);  // 只有初始化
        for_tmp->code.for_cycle.condition = NULL;
        for_tmp->code.for_cycle.after = NULL;
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = for_tmp;
    }
#line 3399 "y.tab.c"
    break;

  case 166:
#line 1230 "gwarf_yacc.y"
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = NULL;
        for_tmp->code.for_cycle.condition = (yyvsp[-2].statement_value);  // 只有条件
        for_tmp->code.for_cycle.after = NULL;
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = for_tmp;
    }
#line 3414 "y.tab.c"
    break;

  case 167:
#line 1241 "gwarf_yacc.y"
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = NULL;
        for_tmp->code.for_cycle.condition = NULL;
        for_tmp->code.for_cycle.after = (yyvsp[-1].statement_value);  // 只有后置操作
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = for_tmp;
    }
#line 3429 "y.tab.c"
    break;

  case 168:
#line 1252 "gwarf_yacc.y"
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = (yyvsp[-4].statement_value);
        for_tmp->code.for_cycle.condition = NULL;  // 无条件
        for_tmp->code.for_cycle.after = (yyvsp[-1].statement_value);
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = for_tmp;
    }
#line 3444 "y.tab.c"
    break;

  case 169:
#line 1263 "gwarf_yacc.y"
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = (yyvsp[-4].statement_value);
        for_tmp->code.for_cycle.condition = (yyvsp[-2].statement_value);
        for_tmp->code.for_cycle.after = NULL;  //无后置操作
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = for_tmp;
    }
#line 3459 "y.tab.c"
    break;

  case 170:
#line 1274 "gwarf_yacc.y"
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = NULL;  //无初始化
        for_tmp->code.for_cycle.condition = (yyvsp[-3].statement_value);
        for_tmp->code.for_cycle.after = (yyvsp[-1].statement_value);
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = for_tmp;
    }
#line 3474 "y.tab.c"
    break;

  case 171:
#line 1285 "gwarf_yacc.y"
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = (yyvsp[-5].statement_value);
        for_tmp->code.for_cycle.condition = (yyvsp[-3].statement_value);
        for_tmp->code.for_cycle.after = (yyvsp[-1].statement_value);
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = for_tmp;
    }
#line 3489 "y.tab.c"
    break;

  case 172:
#line 1296 "gwarf_yacc.y"
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_in_cycle;
        for_tmp->code.for_in_cycle.iter = (yyvsp[-1].statement_value);
        for_tmp->code.for_in_cycle.var = (yyvsp[-3].statement_value);
        for_tmp->code.for_in_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_in_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = for_tmp;
    }
#line 3503 "y.tab.c"
    break;

  case 173:
#line 1309 "gwarf_yacc.y"
    {
        statement *import_tmp =  make_statement();
        import_tmp->type = include_import;
        import_tmp->code.include_import.file = (yyvsp[0].statement_value);
        (yyval.statement_value) = import_tmp;
    }
#line 3514 "y.tab.c"
    break;

  case 174:
#line 1319 "gwarf_yacc.y"
    {
        statement *import_tmp =  make_statement();
        import_tmp->type = import_class;
        import_tmp->code.import_class.file = (yyvsp[-2].statement_value);

        import_tmp->code.import_class.var = (yyvsp[0].statement_value);

        (yyval.statement_value) = import_tmp;
    }
#line 3528 "y.tab.c"
    break;

  case 175:
#line 1332 "gwarf_yacc.y"
    {
        statement *raise_tmp =  make_statement();
        raise_tmp->type = raise_e;
        raise_tmp->code.raise_e.done = (yyvsp[-1].statement_value);
        raise_tmp->code.raise_e.info = (yyvsp[0].statement_value);
        (yyval.statement_value) = raise_tmp;
    }
#line 3540 "y.tab.c"
    break;

  case 176:
#line 1340 "gwarf_yacc.y"
    {
        statement *raise_tmp =  make_statement();
        raise_tmp->type = throw_e;
        raise_tmp->code.throw_e.done = (yyvsp[0].statement_value);
        (yyval.statement_value) = raise_tmp;
    }
#line 3551 "y.tab.c"
    break;

  case 177:
#line 1347 "gwarf_yacc.y"
    {
        statement *raise_tmp =  make_statement();
        raise_tmp->type = assert_e;
        raise_tmp->code.assert_e.condition = (yyvsp[-1].statement_value);
        raise_tmp->code.assert_e.info = (yyvsp[0].statement_value);
        (yyval.statement_value) = raise_tmp;
    }
#line 3563 "y.tab.c"
    break;

  case 178:
#line 1358 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3572 "y.tab.c"
    break;

  case 179:
#line 1366 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // out statement_base (FILO)

        (yyvsp[-4].statement_value)->code.try_code.var = (yyvsp[0].statement_value);  

        (yyvsp[-4].statement_value)->code.try_code.except = make_statement();
        statement_base = append_statement_list((yyvsp[-4].statement_value)->code.try_code.except, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = (yyvsp[-4].statement_value);
    }
#line 3586 "y.tab.c"
    break;

  case 180:
#line 1379 "gwarf_yacc.y"
    {
        statement *try_tmp =  make_statement();
        try_tmp->type = try_code;
        try_tmp->code.try_code.try = make_statement();
        statement_base = append_statement_list(try_tmp->code.try_code.try, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = try_tmp;
    }
#line 3598 "y.tab.c"
    break;

  case 181:
#line 1390 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyvsp[0].statement_value)->code.while_cycle.first_do = true;
        (yyval.statement_value) = (yyvsp[0].statement_value);
    }
#line 3608 "y.tab.c"
    break;

  case 182:
#line 1396 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyvsp[0].statement_value)->code.while_cycle.first_do = true;
        (yyval.statement_value) = (yyvsp[0].statement_value);
    }
#line 3618 "y.tab.c"
    break;

  case 183:
#line 1405 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyvsp[-1].statement_value)->code.while_cycle.first_do = false;
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3628 "y.tab.c"
    break;

  case 184:
#line 1414 "gwarf_yacc.y"
    {
        statement *while_tmp =  make_statement();
        while_tmp->type = while_cycle;
        while_tmp->code.while_cycle.condition = (yyvsp[-1].statement_value);
        while_tmp->code.while_cycle.done = make_statement();
        statement_base = append_statement_list(while_tmp->code.while_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = while_tmp;
    }
#line 3641 "y.tab.c"
    break;

  case 185:
#line 1426 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 3649 "y.tab.c"
    break;

  case 186:
#line 1433 "gwarf_yacc.y"
    {   
        //无参数方法
        statement *class_tmp =  make_statement();
        class_tmp->type = set_class;

        class_tmp->code.set_class.var = (yyvsp[-2].statement_value);

        class_tmp->code.set_class.father_list = NULL;
        class_tmp->code.set_class.done = make_statement();
        statement_base = append_statement_list(class_tmp->code.set_class.done, statement_base);  // new statement_base (FILO)

        (yyval.statement_value) = class_tmp;
    }
#line 3667 "y.tab.c"
    break;

  case 187:
#line 1447 "gwarf_yacc.y"
    {   
        //无参数方法
        statement *class_tmp =  make_statement();
        class_tmp->type = set_class;

        class_tmp->code.set_class.var = (yyvsp[-3].statement_value);

        class_tmp->code.set_class.done = make_statement();
        class_tmp->code.set_class.father_list = (yyvsp[-1].parameter_list);  // set father
        statement_base = append_statement_list(class_tmp->code.set_class.done, statement_base);  // new statement_base (FILO)

        (yyval.statement_value) = class_tmp;
    }
#line 3685 "y.tab.c"
    break;

  case 188:
#line 1464 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 3693 "y.tab.c"
    break;

  case 189:
#line 1471 "gwarf_yacc.y"
    {   
        //无参数方法
        statement *def_tmp =  make_statement();
        def_tmp->type = def;

        def_tmp->code.def.var = (yyvsp[-2].statement_value);
        def_tmp->code.def.parameter_list = NULL;
        def_tmp->code.def.done = make_statement();
        statement_base = append_statement_list(def_tmp->code.def.done, statement_base);  // new statement_base (FILO)

        (yyval.statement_value) = def_tmp;
    }
#line 3710 "y.tab.c"
    break;

  case 190:
#line 1484 "gwarf_yacc.y"
    {   
        statement *def_tmp =  make_statement();
        def_tmp->type = def;

        def_tmp->code.def.var = (yyvsp[-3].statement_value);
        def_tmp->code.def.parameter_list = (yyvsp[-1].parameter_list);
        def_tmp->code.def.done = make_statement();
        statement_base = append_statement_list(def_tmp->code.def.done, statement_base);  // new statement_base (FILO)

        (yyval.statement_value) = def_tmp;
    }
#line 3726 "y.tab.c"
    break;


#line 3730 "y.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 1511 "gwarf_yacc.y"

int yyerror(char const *str)
{
    printf("[ERROR] %s in [%s];\ncontinue to run? [Y/n(default)]\n", str, yytext);
    if(getc(stdin) == 'Y'){
        return 0;
    }
    else{
        exit(1);
    }
}

int parser(char *file)
{
    yyin = fopen(file,"r");
    yyparse();
    return 0;
}
