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
#define YYFINAL  146
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1258

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  194
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  362

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
     133,   137,   141,   145,   149,   153,   157,   161,   165,   169,
     176,   189,   197,   198,   207,   216,   225,   234,   243,   252,
     261,   270,   279,   288,   297,   309,   315,   321,   327,   333,
     340,   347,   354,   365,   369,   374,   382,   390,   391,   399,
     410,   411,   421,   434,   435,   449,   450,   462,   463,   475,
     476,   489,   490,   499,   508,   517,   526,   535,   547,   548,
     561,   562,   574,   575,   588,   589,   599,   611,   612,   621,
     633,   634,   643,   652,   661,   674,   675,   689,   690,   703,
     704,   713,   722,   734,   735,   748,   749,   761,   762,   774,
     775,   783,   791,   799,   810,   811,   812,   819,   832,   844,
     856,   868,   880,   892,   893,   901,   914,   921,   930,   944,
     958,   973,   974,   979,   988,   999,  1000,  1008,  1018,  1019,
    1027,  1037,  1038,  1046,  1056,  1057,  1065,  1075,  1076,  1084,
    1094,  1095,  1102,  1112,  1117,  1126,  1132,  1141,  1152,  1159,
    1170,  1177,  1188,  1199,  1210,  1221,  1232,  1243,  1254,  1265,
    1278,  1288,  1301,  1309,  1316,  1327,  1335,  1348,  1359,  1365,
    1374,  1383,  1395,  1402,  1416,  1433,  1440,  1453,  1468,  1469,
    1470,  1475,  1476,  1477,  1478
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
  "pack_eq_exp", "top_exp", "eq_number", "formal_parameter",
  "slice_arguments", "slice_arguments_token", "call_number", "lambda_exp",
  "chose_exp", "bool_or", "bool_and", "bool_not", "third_number",
  "bit_or_not", "bit_or", "bit_and", "bit_move", "second_number",
  "first_number", "negative", "bit_not", "zero_number", "attribute",
  "call_down", "call_slice", "iter_value", "element", "base_value",
  "base_var_", "base_var_token", "base_string", "nonlocal_token",
  "global_token", "default_token", "return_exp", "return_token",
  "restarted_exp", "restarted_token", "restart_exp", "restart_token",
  "continued_exp", "continued_token", "continue_exp", "continue_token",
  "break_exp", "break_token", "broken_exp", "broken_token", "if_block",
  "elif_exp", "if_exp", "block_block", "block_exp", "for_block", "for_exp",
  "include_exp", "import_exp", "raise_exp", "try_block", "try_exp",
  "try_token", "do_while_block", "while_block", "while_exp", "class_block",
  "class_exp", "def_block", "def_exp", "block", "stop_token", YY_NULLPTR
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

#define YYPACT_NINF (-151)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     554,  -151,  -151,  -151,  -151,   784,   212,   632,    20,  -151,
      23,  -151,  -151,  -151,  -151,  -151,   -21,   -21,   652,     8,
      26,     8,     8,  -151,  -151,  -151,  -151,   710,  -151,   710,
    -151,  1085,  1085,  1085,  1085,    77,   316,   316,   280,    50,
    1085,    43,   554,  -151,   -21,   -21,  -151,   197,  -151,    -5,
      10,    13,  -151,   139,     3,    14,    11,   -53,   140,     6,
    -151,  -151,    97,    37,  -151,    61,  -151,  -151,  -151,  -151,
    -151,    96,   -21,   -21,   -21,   -21,  1085,   -21,   710,   -21,
     710,   -21,   710,   -21,   710,   -21,   710,   -21,   710,   109,
      50,   -21,    50,   -21,    50,   -21,   -21,   -21,   -21,    50,
      50,   -21,   -21,    50,   -21,    50,   -21,    50,  1085,  -151,
    1085,    28,   212,  1085,    -6,     7,  -151,    68,     4,  1085,
    1085,  -151,  -151,   114,   114,  -151,    24,    49,   710,    92,
    -151,  -151,  1085,   113,   116,  1085,  -151,    76,  -151,   139,
     121,   121,    97,   405,     1,  1085,  -151,  -151,   114,   114,
    1085,   716,  1085,  1085,  1085,  1085,  1085,  1085,  -151,  -151,
    1085,  1178,  1178,  1178,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,   280,   280,   280,   280,  1085,  -151,   114,   114,   114,
     114,   710,   114,  -151,   114,  -151,   114,  -151,   114,  -151,
     114,  -151,   114,  -151,  -151,   124,    50,   114,  -151,   114,
    -151,   114,  -151,   114,   114,   114,   114,  -151,    87,   114,
     114,  -151,   114,  -151,   114,  -151,   132,  -151,  1178,    12,
    -151,  -151,  1085,     2,   820,  -151,   152,   162,  -151,  -151,
       8,  -151,  -151,   903,   115,   118,   146,   736,   800,  -151,
     710,   341,   171,   490,   173,  -151,     5,  -151,  -151,  -151,
      22,  -151,  -151,  -151,  -151,  -151,  -151,  -151,   142,    13,
    -151,     3,     3,     3,     3,     3,     3,    14,    11,   -53,
     140,   140,     6,     6,  -151,  -151,  -151,  -151,    37,    37,
      37,  -151,    32,   967,  -151,  -151,  1085,  -151,   133,    -5,
     107,  -151,   884,  1178,  1085,  1085,   144,  -151,  -151,  -151,
     982,   154,  1046,  1085,  -151,    25,  -151,    30,  -151,   -18,
    -151,  -151,  -151,  -151,  -151,  1178,  -151,  -151,  -151,   155,
    -151,   183,   710,   178,    -5,  -151,  -151,  1085,  -151,   200,
    1061,  1100,   180,   209,  -151,  -151,    -5,  -151,  -151,  -151,
    -151,  -151,   211,  -151,   216,  1139,  -151,  -151,  -151,  -151,
     219,  -151
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   117,   118,   126,   125,     0,     0,     0,     0,   149,
       0,   152,   146,   143,   140,   137,     0,     0,     0,     0,
       0,     0,     0,   159,   121,   120,   122,     0,   134,     0,
     177,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     3,     0,     0,    31,    32,    57,    60,
      63,    65,    67,    69,    71,    78,    80,    82,    84,    87,
      90,    95,    97,    99,   103,   105,   107,   109,   114,   115,
     123,   119,     0,     0,     0,     0,   131,     0,   135,     0,
     138,     0,   141,     0,   144,     0,   147,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    96,
       0,     0,     0,     0,    45,     0,   112,    45,     0,     0,
       0,   191,   192,    14,    15,   110,    45,     0,     0,     0,
     129,   128,     0,     0,     0,     0,   173,     0,   170,    70,
      42,    44,    98,     0,     0,     0,     1,     4,    29,     5,
       0,     0,     0,     0,     0,     0,     0,     0,    41,    43,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,    19,    17,    16,
      22,   132,    13,   136,    12,   139,    11,   142,    10,   145,
       8,   148,     9,   151,   156,     0,     0,     7,   153,    20,
     158,    18,   160,    27,    26,    25,    24,   175,     0,    28,
       6,   180,    23,   182,    21,   185,     0,    46,     0,     0,
      47,   116,     0,     0,     0,   113,     0,     0,   194,   193,
       0,   111,   130,     0,     0,   109,     0,     0,     0,   172,
       0,     0,     0,     0,     0,   178,     0,   174,    33,    58,
       0,    34,    35,    36,    37,    38,    39,    40,     0,    66,
      68,    74,    73,    72,    75,    76,    77,    79,    81,    83,
      85,    86,    88,    89,    92,    91,    93,    94,   100,   101,
     102,   104,     0,     0,    53,   133,     0,   154,     0,    61,
       0,    48,     0,     0,     0,     0,    49,   181,   157,   124,
       0,     0,     0,     0,   186,     0,   183,     0,   171,    45,
     190,   188,   189,   179,    59,     0,   106,    56,   108,    55,
      54,     0,     0,    30,    62,    50,    51,     0,   161,     0,
       0,     0,     0,     0,   187,   184,    64,   155,   176,    52,
     164,   163,     0,   162,     0,     0,   169,   167,   165,   166,
       0,   168
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -151,  -151,   236,   -40,  -151,     0,    85,    -1,  -151,   -49,
     137,  -151,  -150,  -151,    86,    89,   230,    90,   106,   104,
     117,    31,    88,   102,   272,   252,   -77,   110,  -151,  -151,
     -26,  -151,  -151,   -12,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -132,  -151,  -151,
    -151,  -151,   -35,   105
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    41,   253,    43,    44,   117,    46,   118,   293,   294,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   206,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   254,   149
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,   133,   147,   134,   144,   115,   114,   128,   231,   130,
     131,   268,   255,   302,     4,   177,   178,   127,   126,     8,
     235,   233,   161,     8,   121,   122,   300,   121,   122,   173,
     174,   135,   136,   137,   138,   119,   324,   232,   120,   344,
     145,   129,    45,   146,   345,   234,   121,   122,   234,   232,
     238,   239,   193,   234,   195,   208,   197,   210,   199,   212,
     201,   240,   203,   234,   217,   218,   234,   143,   221,   326,
     223,   234,   225,   179,   180,   162,   191,   163,   299,   232,
       1,     2,     3,     4,   170,     5,   241,   327,   303,   172,
     234,   184,   108,   171,     7,     1,     2,     3,     4,   185,
       5,   186,   242,   245,   288,   289,   290,   112,   226,     7,
     227,   229,   114,   230,   228,    18,   181,   182,   183,   236,
     237,   123,   124,   232,   323,    24,    25,    26,   247,   244,
      18,   248,   246,   243,   250,   249,   151,   204,   205,   296,
      24,    25,    26,    45,   298,   257,   231,   175,   176,   148,
     260,   164,   165,   334,   121,   122,   312,    38,    35,   238,
     239,   166,   167,   168,   169,   295,   307,    36,    37,   161,
     325,   297,    38,   140,   141,   346,   308,   187,   188,   189,
     190,   313,   192,   240,   194,   292,   196,   320,   198,   322,
     200,   332,   202,   303,   207,   340,   209,   347,   211,   337,
     213,   214,   215,   216,   280,   281,   219,   220,   150,   222,
     327,   224,   151,   147,   350,     1,     2,     3,     4,   234,
       5,   355,   110,   356,   318,   357,   111,   112,   309,     7,
     358,   113,   301,   361,   306,   258,    42,   261,   262,   263,
     264,   265,   266,   311,   330,   267,   315,   317,   269,   256,
      18,   319,   270,    45,   271,   272,   273,   274,   275,   276,
      24,    25,    26,   282,   283,   139,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   278,   277,   109,    35,   284,
     285,   286,   287,     1,     2,     3,     4,    36,    37,   279,
     142,     0,    38,   329,   291,   108,   331,     7,     0,     0,
       0,   333,     0,     0,   335,   336,   348,     0,     0,     0,
     339,     0,   342,   343,     0,     0,     0,     0,    18,     1,
       2,     3,     4,     0,     5,     0,     0,     0,    24,    25,
      26,   112,     0,     7,     0,     0,     0,   349,     0,     0,
     352,   354,     0,     0,     1,     2,     3,     4,     0,     5,
       0,   110,     0,     0,    18,   360,     6,   116,   251,     8,
     113,     0,     0,     0,    24,    25,    26,     9,    10,     0,
       0,    11,    12,    13,    14,    15,    16,    17,     0,    18,
      19,    20,    35,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,    29,     0,    38,    30,     0,     0,
      31,    32,    33,    34,     0,     0,     0,    35,     1,     2,
       3,     4,     0,     5,     0,     0,    36,    37,     0,     0,
       6,    38,   251,     8,     0,   252,    39,     0,    40,     0,
       0,     9,    10,     0,     0,    11,    12,    13,    14,    15,
      16,    17,     0,    18,    19,    20,     0,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,    29,     0,
       0,    30,     0,     0,    31,    32,    33,    34,     0,     0,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
      36,    37,     0,     0,     0,    38,     0,     0,     0,   252,
      39,     0,    40,     1,     2,     3,     4,     0,     5,     0,
       0,     0,     0,     0,     0,     6,   321,     7,     8,     0,
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
      35,     0,     0,     0,     0,     0,     0,     0,     0,    36,
      37,     0,     0,     0,    38,     1,     2,     3,     4,    39,
       5,    40,   110,     0,     0,     0,     0,   112,   116,     7,
       0,   113,     0,     0,     0,     1,     2,     3,     4,     0,
       5,     0,   110,     0,     0,     0,     0,   112,     0,     7,
      18,   113,     0,     0,     0,     0,     0,     0,     0,     0,
      24,    25,    26,     0,     0,     0,     0,     0,     0,   125,
      18,     0,     0,     0,     0,     0,     0,     0,    35,     0,
      24,    25,    26,     0,     0,     0,     0,    36,    37,     0,
       0,     0,    38,     1,     2,     3,     4,     0,    35,     1,
       2,     3,     4,     0,     5,   108,   110,    36,    37,     0,
     259,   112,    38,     7,     0,   113,     0,     0,     0,     1,
       2,     3,     4,     0,     5,     0,   110,     0,   132,     0,
     314,   112,     0,     7,    18,   113,     0,     0,    24,    25,
      26,     0,     0,     0,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,    18,     0,     0,     0,     0,     0,
       0,     0,    35,     0,    24,    25,    26,     1,     2,     3,
       4,    36,    37,     0,     0,     0,    38,     0,     0,   108,
       0,     7,    35,     1,     2,     3,     4,     0,     5,     0,
     110,    36,    37,     0,   316,   112,    38,     7,     0,   113,
       0,     0,    18,     1,     2,     3,     4,     0,     5,     0,
     304,     0,    24,    25,    26,   112,     0,     7,    18,   305,
       0,     0,     0,     0,     0,     0,     0,     0,    24,    25,
      26,     0,     0,     0,     0,     0,     0,     0,    18,     0,
       0,     0,     0,     0,    38,     0,    35,     0,    24,    25,
      26,     0,     0,     0,     0,    36,    37,     0,     0,     0,
      38,     0,     0,     0,     0,     0,    35,     1,     2,     3,
       4,     0,     5,     0,   110,    36,    37,     0,     0,   112,
      38,     7,     0,   113,     0,     0,     1,     2,     3,     4,
       0,     5,     0,     0,     0,     0,     0,     0,   112,     0,
       7,     0,    18,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    24,    25,    26,     0,     0,     0,     0,     0,
       0,    18,     0,     0,   310,     0,     0,     0,     0,     0,
      35,    24,    25,    26,     0,     0,     0,     0,     0,    36,
      37,     0,     0,     0,    38,     0,     0,     0,     0,    35,
       1,     2,     3,     4,     0,     5,     0,     0,    36,    37,
       0,     0,   112,    38,     7,     1,     2,     3,     4,     0,
       5,     0,     0,     0,     0,     0,   338,   112,     0,     7,
       0,     0,     0,     0,   328,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    24,    25,    26,     0,     0,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      24,    25,    26,    35,     0,     0,     0,     0,     0,     0,
       0,     0,    36,    37,     0,     0,     0,    38,    35,     1,
       2,     3,     4,     0,     5,     0,     0,    36,    37,     0,
       0,   112,    38,     7,     1,     2,     3,     4,     0,     5,
       0,     0,     0,     0,     0,   351,   112,     0,     7,     0,
       0,     0,     0,     0,    18,     0,     0,   341,     1,     2,
       3,     4,     0,     5,    24,    25,    26,     0,     0,    18,
     112,     0,     7,     1,     2,     3,     4,     0,     5,    24,
      25,    26,    35,     0,   353,   112,     0,     7,     0,     0,
       0,    36,    37,    18,     0,     0,    38,    35,     0,     0,
       0,     0,     0,    24,    25,    26,    36,    37,    18,     0,
       0,    38,     1,     2,     3,     4,     0,     5,    24,    25,
      26,    35,     0,   359,   112,     0,     7,     0,     0,     0,
      36,    37,     0,     0,     0,    38,    35,     0,     0,     0,
       0,     0,     0,     0,     0,    36,    37,    18,     0,     0,
      38,     1,     2,     3,     4,     0,     5,    24,    25,    26,
       0,     0,     0,   108,     0,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,     0,     0,     0,     0,
       0,     0,     0,     0,    36,    37,    18,     0,     0,    38,
       0,     0,     0,     0,     0,     0,    24,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38
};

static const yytype_int16 yycheck[] =
{
       0,    27,    42,    29,    39,     6,     6,    19,    14,    21,
      22,   161,   144,    11,     6,     9,    10,    18,    18,    18,
      16,    14,    27,    18,    45,    46,    14,    45,    46,    82,
      83,    31,    32,    33,    34,    15,    14,    55,    15,    14,
      40,    15,    42,     0,    14,    41,    45,    46,    41,    55,
      45,    46,    78,    41,    80,    90,    82,    92,    84,    94,
      86,    37,    88,    41,    99,   100,    41,    17,   103,    37,
     105,    41,   107,    67,    68,    65,    76,    64,   228,    55,
       3,     4,     5,     6,    81,     8,    37,    55,    86,    78,
      41,    54,    15,    79,    17,     3,     4,     5,     6,    38,
       8,     5,   128,   129,   181,   182,   183,    15,   108,    17,
     110,   112,   112,   113,    86,    38,    19,    20,    21,   119,
     120,    16,    17,    55,   256,    48,    49,    50,    15,   129,
      38,    15,   132,    41,    58,   135,    15,    28,    29,    15,
      48,    49,    50,   143,    57,   145,    14,     7,     8,    44,
     151,    12,    13,   303,    45,    46,    41,    80,    66,    45,
      46,    22,    23,    24,    25,   191,    14,    75,    76,    27,
      28,   206,    80,    36,    37,   325,    14,    72,    73,    74,
      75,    63,    77,    37,    79,   185,    81,    16,    83,    16,
      85,    58,    87,    86,    89,    41,    91,    14,    93,    55,
      95,    96,    97,    98,   173,   174,   101,   102,    11,   104,
      55,   106,    15,   253,    14,     3,     4,     5,     6,    41,
       8,    41,    10,    14,   250,    14,    14,    15,   240,    17,
      14,    19,   232,    14,   234,   150,     0,   152,   153,   154,
     155,   156,   157,   243,   293,   160,   247,   248,   162,   144,
      38,   251,   163,   253,   164,   165,   166,   167,   168,   169,
      48,    49,    50,   175,   176,    35,    69,    70,    71,    72,
      73,    74,    75,    76,    77,   171,   170,     5,    66,   177,
     178,   179,   180,     3,     4,     5,     6,    75,    76,   172,
      38,    -1,    80,   293,   184,    15,   296,    17,    -1,    -1,
      -1,   302,    -1,    -1,   304,   305,   332,    -1,    -1,    -1,
     310,    -1,   312,   313,    -1,    -1,    -1,    -1,    38,     3,
       4,     5,     6,    -1,     8,    -1,    -1,    -1,    48,    49,
      50,    15,    -1,    17,    -1,    -1,    -1,   337,    -1,    -1,
     340,   341,    -1,    -1,     3,     4,     5,     6,    -1,     8,
      -1,    10,    -1,    -1,    38,   355,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    48,    49,    50,    26,    27,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    38,
      39,    40,    66,    42,    43,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    -1,    80,    56,    -1,    -1,
      59,    60,    61,    62,    -1,    -1,    -1,    66,     3,     4,
       5,     6,    -1,     8,    -1,    -1,    75,    76,    -1,    -1,
      15,    80,    17,    18,    -1,    84,    85,    -1,    87,    -1,
      -1,    26,    27,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    38,    39,    40,    -1,    42,    43,    -1,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    -1,
      -1,    56,    -1,    -1,    59,    60,    61,    62,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    76,    -1,    -1,    -1,    80,    -1,    -1,    -1,    84,
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
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    -1,    -1,    -1,    80,     3,     4,     5,     6,    85,
       8,    87,    10,    -1,    -1,    -1,    -1,    15,    16,    17,
      -1,    19,    -1,    -1,    -1,     3,     4,     5,     6,    -1,
       8,    -1,    10,    -1,    -1,    -1,    -1,    15,    -1,    17,
      38,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      48,    49,    50,    -1,    -1,    -1,    -1,    75,    76,    -1,
      -1,    -1,    80,     3,     4,     5,     6,    -1,    66,     3,
       4,     5,     6,    -1,     8,    15,    10,    75,    76,    -1,
      14,    15,    80,    17,    -1,    19,    -1,    -1,    -1,     3,
       4,     5,     6,    -1,     8,    -1,    10,    -1,    38,    -1,
      14,    15,    -1,    17,    38,    19,    -1,    -1,    48,    49,
      50,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    -1,    48,    49,    50,     3,     4,     5,
       6,    75,    76,    -1,    -1,    -1,    80,    -1,    -1,    15,
      -1,    17,    66,     3,     4,     5,     6,    -1,     8,    -1,
      10,    75,    76,    -1,    14,    15,    80,    17,    -1,    19,
      -1,    -1,    38,     3,     4,     5,     6,    -1,     8,    -1,
      10,    -1,    48,    49,    50,    15,    -1,    17,    38,    19,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    66,    -1,    48,    49,
      50,    -1,    -1,    -1,    -1,    75,    76,    -1,    -1,    -1,
      80,    -1,    -1,    -1,    -1,    -1,    66,     3,     4,     5,
       6,    -1,     8,    -1,    10,    75,    76,    -1,    -1,    15,
      80,    17,    -1,    19,    -1,    -1,     3,     4,     5,     6,
      -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,    15,    -1,
      17,    -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      66,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,    75,
      76,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    66,
       3,     4,     5,     6,    -1,     8,    -1,    -1,    75,    76,
      -1,    -1,    15,    80,    17,     3,     4,     5,     6,    -1,
       8,    -1,    -1,    -1,    -1,    -1,    14,    15,    -1,    17,
      -1,    -1,    -1,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    -1,    -1,    -1,    80,    66,     3,
       4,     5,     6,    -1,     8,    -1,    -1,    75,    76,    -1,
      -1,    15,    80,    17,     3,     4,     5,     6,    -1,     8,
      -1,    -1,    -1,    -1,    -1,    14,    15,    -1,    17,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    41,     3,     4,
       5,     6,    -1,     8,    48,    49,    50,    -1,    -1,    38,
      15,    -1,    17,     3,     4,     5,     6,    -1,     8,    48,
      49,    50,    66,    -1,    14,    15,    -1,    17,    -1,    -1,
      -1,    75,    76,    38,    -1,    -1,    80,    66,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    75,    76,    38,    -1,
      -1,    80,     3,     4,     5,     6,    -1,     8,    48,    49,
      50,    66,    -1,    14,    15,    -1,    17,    -1,    -1,    -1,
      75,    76,    -1,    -1,    -1,    80,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    38,    -1,    -1,
      80,     3,     4,     5,     6,    -1,     8,    48,    49,    50,
      -1,    -1,    -1,    15,    -1,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    38,    -1,    -1,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     8,    15,    17,    18,    26,
      27,    30,    31,    32,    33,    34,    35,    36,    38,    39,
      40,    42,    43,    47,    48,    49,    50,    51,    52,    53,
      56,    59,    60,    61,    62,    66,    75,    76,    80,    85,
      87,    89,    90,    91,    92,    93,    94,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,    15,   112,
      10,    14,    15,    19,    93,    95,    16,    93,    95,    15,
      15,    45,    46,   161,   161,    37,    93,    95,   121,    15,
     121,   121,    38,   118,   118,    93,    93,    93,    93,   104,
      98,    98,   113,    17,   160,    93,     0,    91,   161,   161,
      11,    15,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    27,    65,    64,    12,    13,    22,    23,    24,    25,
      81,    79,    78,    82,    83,     7,     8,     9,    10,    67,
      68,    19,    20,    21,    54,    38,     5,   161,   161,   161,
     161,    93,   161,   118,   161,   118,   161,   118,   161,   118,
     161,   118,   161,   118,    28,    29,   141,   161,   160,   161,
     160,   161,   160,   161,   161,   161,   161,   160,   160,   161,
     161,   160,   161,   160,   161,   160,    93,    93,    86,    95,
      93,    14,    55,    14,    41,    16,    93,    93,    45,    46,
      37,    37,   118,    41,    93,   118,    93,    15,    15,    93,
      58,    17,    84,    90,   160,   155,   161,    93,    94,    14,
      95,    94,    94,    94,    94,    94,    94,    94,   100,   102,
     103,   105,   105,   105,   105,   105,   105,   106,   107,   108,
     109,   109,   110,   110,   111,   111,   111,   111,   114,   114,
     114,   115,    93,    96,    97,   118,    15,   160,    57,   100,
      14,    93,    11,    86,    10,    19,    93,    14,    14,   121,
      41,    93,    41,    63,    14,    95,    14,    95,   118,    93,
      16,    16,    16,   155,    14,    28,    37,    55,    37,    93,
      97,    93,    58,    95,   100,    93,    93,    55,    14,    93,
      41,    41,    93,    93,    14,    14,   100,    14,   118,    93,
      14,    14,    93,    14,    93,    41,    14,    14,    14,    14,
      93,    14
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    90,    90,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      92,    93,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    95,    95,    95,    95,    95,
      95,    95,    95,    96,    96,    96,    97,    98,    98,    98,
      99,    99,    99,   100,   100,   101,   101,   102,   102,   103,
     103,   104,   104,   104,   104,   104,   104,   104,   105,   105,
     106,   106,   107,   107,   108,   108,   108,   109,   109,   109,
     110,   110,   110,   110,   110,   111,   111,   112,   112,   113,
     113,   113,   113,   114,   114,   115,   115,   116,   116,   117,
     117,   117,   117,   117,   118,   118,   118,   119,   119,   119,
     119,   119,   119,   120,   120,   121,   122,   122,   123,   124,
     125,   126,   126,   126,   127,   128,   128,   129,   130,   130,
     131,   132,   132,   133,   134,   134,   135,   136,   136,   137,
     138,   138,   139,   140,   140,   141,   141,   142,   143,   144,
     145,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     147,   148,   149,   149,   149,   150,   151,   152,   153,   153,
     154,   155,   156,   157,   157,   158,   159,   159,   160,   160,
     160,   161,   161,   161,   161
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       5,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     1,     2,     2,     3,     3,
       4,     4,     5,     1,     2,     2,     2,     1,     3,     4,
       1,     4,     5,     1,     5,     1,     3,     1,     3,     1,
       2,     1,     3,     3,     3,     3,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     2,     1,     2,     1,
       3,     3,     3,     1,     3,     1,     4,     1,     4,     1,
       2,     3,     2,     3,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     1,     2,     2,     2,
       3,     1,     2,     3,     1,     1,     2,     1,     1,     2,
       1,     1,     2,     1,     1,     2,     1,     1,     2,     1,
       1,     2,     1,     2,     3,     4,     1,     4,     2,     1,
       2,     5,     6,     6,     6,     7,     7,     7,     8,     6,
       2,     4,     3,     2,     3,     2,     5,     1,     3,     4,
       2,     4,     2,     4,     5,     2,     4,     5,     3,     3,
       3,     1,     1,     2,     2
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
#line 1956 "y.tab.c"
    break;

  case 4:
#line 59 "gwarf_yacc.y"
    {   
        if((yyvsp[0].statement_value) != NULL){
            statement *tmp = find_statement_list(0, statement_base);
            append_statement(tmp, (yyvsp[0].statement_value));
        }
    }
#line 1967 "y.tab.c"
    break;

  case 5:
#line 70 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1975 "y.tab.c"
    break;

  case 6:
#line 74 "gwarf_yacc.y"
    {   
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1983 "y.tab.c"
    break;

  case 7:
#line 78 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1991 "y.tab.c"
    break;

  case 8:
#line 82 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1999 "y.tab.c"
    break;

  case 9:
#line 86 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2007 "y.tab.c"
    break;

  case 10:
#line 90 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2015 "y.tab.c"
    break;

  case 11:
#line 94 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2023 "y.tab.c"
    break;

  case 12:
#line 98 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2031 "y.tab.c"
    break;

  case 13:
#line 102 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2039 "y.tab.c"
    break;

  case 14:
#line 106 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = rego;
        (yyval.statement_value) = code_tmp;
    }
#line 2049 "y.tab.c"
    break;

  case 15:
#line 112 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = rewent;
        (yyval.statement_value) = code_tmp;
    }
#line 2059 "y.tab.c"
    break;

  case 16:
#line 118 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2067 "y.tab.c"
    break;

  case 17:
#line 122 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2075 "y.tab.c"
    break;

  case 18:
#line 126 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2083 "y.tab.c"
    break;

  case 19:
#line 130 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2091 "y.tab.c"
    break;

  case 20:
#line 134 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2099 "y.tab.c"
    break;

  case 21:
#line 138 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2107 "y.tab.c"
    break;

  case 22:
#line 142 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2115 "y.tab.c"
    break;

  case 23:
#line 146 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2123 "y.tab.c"
    break;

  case 24:
#line 150 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2131 "y.tab.c"
    break;

  case 25:
#line 154 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2139 "y.tab.c"
    break;

  case 26:
#line 158 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2147 "y.tab.c"
    break;

  case 27:
#line 162 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2155 "y.tab.c"
    break;

  case 28:
#line 166 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2163 "y.tab.c"
    break;

  case 29:
#line 170 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2171 "y.tab.c"
    break;

  case 30:
#line 177 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = pack_eq;
        code_tmp->code.pack_eq.right = (yyvsp[0].parameter_list);
        code_tmp->code.pack_eq.left = (yyvsp[-3].parameter_list);
        (yyval.statement_value) = code_tmp;
        puts("SSS");
    }
#line 2184 "y.tab.c"
    break;

  case 31:
#line 190 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[0].statement_value);
    }
#line 2192 "y.tab.c"
    break;

  case 33:
#line 199 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ASSIGnMENT_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2205 "y.tab.c"
    break;

  case 34:
#line 208 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AADD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2218 "y.tab.c"
    break;

  case 35:
#line 217 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ASUB_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2231 "y.tab.c"
    break;

  case 36:
#line 226 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AMUL_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2244 "y.tab.c"
    break;

  case 37:
#line 235 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ADIV_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2257 "y.tab.c"
    break;

  case 38:
#line 244 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AMOD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2270 "y.tab.c"
    break;

  case 39:
#line 253 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AINTDIV_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2283 "y.tab.c"
    break;

  case 40:
#line 262 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = APOW_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2296 "y.tab.c"
    break;

  case 41:
#line 271 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LADD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-1].statement_value);
        code_tmp->code.operation.right_exp = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2309 "y.tab.c"
    break;

  case 42:
#line 280 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = FADD_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2322 "y.tab.c"
    break;

  case 43:
#line 289 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LSUB_func;
        code_tmp->code.operation.left_exp = (yyvsp[-1].statement_value);
        code_tmp->code.operation.right_exp = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2335 "y.tab.c"
    break;

  case 44:
#line 298 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = FSUB_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2348 "y.tab.c"
    break;

  case 45:
#line 310 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_value((yyvsp[0].statement_value));
        (yyval.parameter_list)->u.var = (yyval.parameter_list)->u.value;
        (yyval.parameter_list)->type = only_value;
    }
#line 2358 "y.tab.c"
    break;

  case 46:
#line 316 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_value((yyvsp[0].statement_value));
        (yyval.parameter_list)->u.var = (yyval.parameter_list)->u.value;
        (yyval.parameter_list)->type = put_args;
    }
#line 2368 "y.tab.c"
    break;

  case 47:
#line 322 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_value((yyvsp[0].statement_value));
        (yyval.parameter_list)->u.var = (yyval.parameter_list)->u.value;
        (yyval.parameter_list)->type = put_kwargs;
    }
#line 2378 "y.tab.c"
    break;

  case 48:
#line 328 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_name((yyvsp[-2].statement_value));
        (yyval.parameter_list)->u.value = (yyvsp[0].statement_value);
        (yyval.parameter_list)->type = name_value;
    }
#line 2388 "y.tab.c"
    break;

  case 49:
#line 334 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_value((yyvsp[0].statement_value), (yyvsp[-2].parameter_list));
        tmp->type = only_value;
        tmp->u.var = tmp->u.value;
        (yyval.parameter_list) = (yyvsp[-2].parameter_list);
    }
#line 2399 "y.tab.c"
    break;

  case 50:
#line 341 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_value((yyvsp[0].statement_value), (yyvsp[-3].parameter_list));
        tmp->type = put_args;
        tmp->u.var = tmp->u.value;
        (yyval.parameter_list) = (yyvsp[-3].parameter_list);
    }
#line 2410 "y.tab.c"
    break;

  case 51:
#line 348 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_value((yyvsp[0].statement_value), (yyvsp[-3].parameter_list));
        tmp->type = put_kwargs;
        tmp->u.var = tmp->u.value;
        (yyval.parameter_list) = (yyvsp[-3].parameter_list);
    }
#line 2421 "y.tab.c"
    break;

  case 52:
#line 355 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_name((yyvsp[-2].statement_value), (yyvsp[-4].parameter_list));
        tmp->u.value = (yyvsp[0].statement_value);
        tmp->type = name_value;
        (yyval.parameter_list) = (yyvsp[-4].parameter_list);
    }
#line 2432 "y.tab.c"
    break;

  case 53:
#line 366 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_value((yyvsp[0].statement_value));
    }
#line 2440 "y.tab.c"
    break;

  case 54:
#line 370 "gwarf_yacc.y"
    {
        append_parameter_value((yyvsp[0].statement_value), (yyvsp[-1].parameter_list));
        (yyval.parameter_list) = (yyvsp[-1].parameter_list);
    }
#line 2449 "y.tab.c"
    break;

  case 55:
#line 375 "gwarf_yacc.y"
    {
        append_parameter_value((yyvsp[0].statement_value), (yyvsp[-1].parameter_list));
        (yyval.parameter_list) = (yyvsp[-1].parameter_list);
    }
#line 2458 "y.tab.c"
    break;

  case 56:
#line 383 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2466 "y.tab.c"
    break;

  case 58:
#line 392 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = (yyvsp[-2].statement_value);
        code_tmp->code.call.parameter_list = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2478 "y.tab.c"
    break;

  case 59:
#line 400 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = (yyvsp[-3].statement_value);
        code_tmp->code.call.parameter_list = (yyvsp[-1].parameter_list);
        (yyval.statement_value) = code_tmp;
    }
#line 2490 "y.tab.c"
    break;

  case 61:
#line 412 "gwarf_yacc.y"
    {
        statement *lambda_tmp =  make_statement();
        lambda_tmp->type = lambda_func;

        lambda_tmp->code.lambda_func.parameter_list = NULL;
        lambda_tmp->code.lambda_func.done = (yyvsp[0].statement_value);

        (yyval.statement_value) = lambda_tmp;
    }
#line 2504 "y.tab.c"
    break;

  case 62:
#line 422 "gwarf_yacc.y"
    {
        statement *lambda_tmp =  make_statement();
        lambda_tmp->type = lambda_func;

        lambda_tmp->code.lambda_func.parameter_list = (yyvsp[-3].parameter_list);
        lambda_tmp->code.lambda_func.done = (yyvsp[0].statement_value);

        (yyval.statement_value) = lambda_tmp;
    }
#line 2518 "y.tab.c"
    break;

  case 64:
#line 436 "gwarf_yacc.y"
    {
        statement *chose_tmp =  make_statement();
        chose_tmp->type = chose_exp;

        chose_tmp->code.chose_exp.condition = (yyvsp[-2].statement_value);
        chose_tmp->code.chose_exp.true_do = (yyvsp[-4].statement_value);
        chose_tmp->code.chose_exp.false_do = (yyvsp[0].statement_value);

        (yyval.statement_value) = chose_tmp;
    }
#line 2533 "y.tab.c"
    break;

  case 66:
#line 451 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = OR_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2546 "y.tab.c"
    break;

  case 68:
#line 464 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AND_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2559 "y.tab.c"
    break;

  case 70:
#line 477 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NOT_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        puts("NOT FUNC");
        (yyval.statement_value) = code_tmp;
    }
#line 2573 "y.tab.c"
    break;

  case 72:
#line 491 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = EQUAL_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2586 "y.tab.c"
    break;

  case 73:
#line 500 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MORE_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2599 "y.tab.c"
    break;

  case 74:
#line 509 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LESS_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2612 "y.tab.c"
    break;

  case 75:
#line 518 "gwarf_yacc.y"
        {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MOREEQ_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2625 "y.tab.c"
    break;

  case 76:
#line 527 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LESSEQ_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2638 "y.tab.c"
    break;

  case 77:
#line 536 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NOTEQ_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2651 "y.tab.c"
    break;

  case 79:
#line 549 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITNOTOR_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        puts("NOT FUNC");
        (yyval.statement_value) = code_tmp;
    }
#line 2665 "y.tab.c"
    break;

  case 81:
#line 563 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITOR_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2678 "y.tab.c"
    break;

  case 83:
#line 576 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITAND_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        puts("NOT FUNC");
        (yyval.statement_value) = code_tmp;
    }
#line 2692 "y.tab.c"
    break;

  case 85:
#line 590 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITRIGHT_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        puts("NOT FUNC");
        (yyval.statement_value) = code_tmp;
    }
#line 2706 "y.tab.c"
    break;

  case 86:
#line 600 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITLEFT_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2719 "y.tab.c"
    break;

  case 88:
#line 613 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ADD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2732 "y.tab.c"
    break;

  case 89:
#line 622 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = SUB_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2745 "y.tab.c"
    break;

  case 91:
#line 635 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MUL_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2758 "y.tab.c"
    break;

  case 92:
#line 644 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = DIV_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2771 "y.tab.c"
    break;

  case 93:
#line 653 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MOD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2784 "y.tab.c"
    break;

  case 94:
#line 662 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = INTDIV_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2797 "y.tab.c"
    break;

  case 96:
#line 676 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NEGATIVE_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2810 "y.tab.c"
    break;

  case 98:
#line 691 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITNOT_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2823 "y.tab.c"
    break;

  case 100:
#line 705 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = POW_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2836 "y.tab.c"
    break;

  case 101:
#line 714 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LOG_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2849 "y.tab.c"
    break;

  case 102:
#line 723 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = SQRT_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2862 "y.tab.c"
    break;

  case 104:
#line 736 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = point;
        code_tmp->code.point.base_var = (yyvsp[-2].statement_value);
        code_tmp->code.point.child_var = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp; 
    }
#line 2874 "y.tab.c"
    break;

  case 106:
#line 750 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = down;
        code_tmp->code.down.base_var = (yyvsp[-3].statement_value);
        code_tmp->code.down.child_var = (yyvsp[-1].statement_value);
        (yyval.statement_value) = code_tmp; 
    }
#line 2886 "y.tab.c"
    break;

  case 108:
#line 763 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = slice;
        code_tmp->code.slice.base_var = (yyvsp[-3].statement_value);
        code_tmp->code.slice.value = (yyvsp[-1].parameter_list);
        (yyval.statement_value) = code_tmp; 
    }
#line 2898 "y.tab.c"
    break;

  case 110:
#line 776 "gwarf_yacc.y"
    {
        statement *statement_tmp = malloc(sizeof(statement));
        statement_tmp->type = base_list;
        statement_tmp->code.base_list.value = NULL;

        (yyval.statement_value) = statement_tmp;
    }
#line 2910 "y.tab.c"
    break;

  case 111:
#line 784 "gwarf_yacc.y"
    {
        statement *statement_tmp = malloc(sizeof(statement));
        statement_tmp->type = base_list;
        statement_tmp->code.base_list.value = (yyvsp[-1].parameter_list);

        (yyval.statement_value) = statement_tmp;
    }
#line 2922 "y.tab.c"
    break;

  case 112:
#line 792 "gwarf_yacc.y"
    {
        statement *statement_tmp = malloc(sizeof(statement));
        statement_tmp->type = base_dict;
        statement_tmp->code.base_dict.value = NULL;

        (yyval.statement_value) = statement_tmp;
    }
#line 2934 "y.tab.c"
    break;

  case 113:
#line 800 "gwarf_yacc.y"
    {
        statement *statement_tmp = malloc(sizeof(statement));
        statement_tmp->type = base_dict;
        statement_tmp->code.base_dict.value = (yyvsp[-1].parameter_list);

        (yyval.statement_value) = statement_tmp;
    }
#line 2946 "y.tab.c"
    break;

  case 116:
#line 813 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2954 "y.tab.c"
    break;

  case 117:
#line 820 "gwarf_yacc.y"
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
#line 2971 "y.tab.c"
    break;

  case 118:
#line 833 "gwarf_yacc.y"
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
#line 2987 "y.tab.c"
    break;

  case 119:
#line 845 "gwarf_yacc.y"
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
#line 3003 "y.tab.c"
    break;

  case 120:
#line 857 "gwarf_yacc.y"
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
#line 3019 "y.tab.c"
    break;

  case 121:
#line 869 "gwarf_yacc.y"
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
#line 3035 "y.tab.c"
    break;

  case 122:
#line 881 "gwarf_yacc.y"
    {
        // NULL代表空值，是GWARF_value
        statement *code_tmp =  make_statement();
        code_tmp->type = base_value;
        code_tmp->code.base_value.value.type = NULL_value;
        code_tmp->code.base_value.value.value.int_value = 0;
        (yyval.statement_value) = code_tmp;
    }
#line 3048 "y.tab.c"
    break;

  case 124:
#line 894 "gwarf_yacc.y"
    {
        (yyvsp[0].statement_value)->code.base_var.from = (yyvsp[-2].statement_value);
        (yyval.statement_value) = (yyvsp[0].statement_value);
    }
#line 3057 "y.tab.c"
    break;

  case 125:
#line 902 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->code.base_var.var_name = malloc(sizeof((yyvsp[0].string_value)));
        char *name_tmp = code_tmp->code.base_var.var_name;
        code_tmp->type = base_var;
        code_tmp->code.base_var.from = NULL;
        strcpy(name_tmp, (yyvsp[0].string_value));
        (yyval.statement_value) = code_tmp;
    }
#line 3071 "y.tab.c"
    break;

  case 126:
#line 915 "gwarf_yacc.y"
    {
        // STRING is char * which the len is 1
        char *tmp = malloc(sizeof((yyvsp[0].string_value)));
        strcpy(tmp, (yyvsp[0].string_value));
        (yyval.string_value) = tmp;
    }
#line 3082 "y.tab.c"
    break;

  case 127:
#line 922 "gwarf_yacc.y"
    {
        char *tmp = realloc((yyvsp[-1].string_value), strlen((yyvsp[-1].string_value)) + strlen((yyvsp[0].string_value)));  // get address
        strcat(tmp, (yyvsp[0].string_value));
        (yyval.string_value) = tmp;
    }
#line 3092 "y.tab.c"
    break;

  case 128:
#line 931 "gwarf_yacc.y"
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
#line 3107 "y.tab.c"
    break;

  case 129:
#line 945 "gwarf_yacc.y"
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
#line 3122 "y.tab.c"
    break;

  case 130:
#line 959 "gwarf_yacc.y"
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
#line 3138 "y.tab.c"
    break;

  case 132:
#line 975 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.return_code.value = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3147 "y.tab.c"
    break;

  case 133:
#line 980 "gwarf_yacc.y"
    {
        (yyvsp[-2].statement_value)->code.return_code.value = (yyvsp[-1].statement_value);
        (yyvsp[-2].statement_value)->code.return_code.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-2].statement_value);
    }
#line 3157 "y.tab.c"
    break;

  case 134:
#line 989 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = return_code;
        code_tmp->code.return_code.times = NULL;
        code_tmp->code.return_code.value = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3169 "y.tab.c"
    break;

  case 136:
#line 1001 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.restarted.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3178 "y.tab.c"
    break;

  case 137:
#line 1009 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = restarted;
        code_tmp->code.restarted.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3189 "y.tab.c"
    break;

  case 139:
#line 1020 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.restart.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3198 "y.tab.c"
    break;

  case 140:
#line 1028 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = restart;
        code_tmp->code.restart.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3209 "y.tab.c"
    break;

  case 142:
#line 1039 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.continued.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3218 "y.tab.c"
    break;

  case 143:
#line 1047 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = continued;
        code_tmp->code.continued.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3229 "y.tab.c"
    break;

  case 145:
#line 1058 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.continue_cycle.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3238 "y.tab.c"
    break;

  case 146:
#line 1066 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = continue_cycle;
        code_tmp->code.continue_cycle.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3249 "y.tab.c"
    break;

  case 148:
#line 1077 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.break_cycle.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3258 "y.tab.c"
    break;

  case 149:
#line 1085 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = break_cycle;
        code_tmp->code.break_cycle.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3269 "y.tab.c"
    break;

  case 151:
#line 1096 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.broken.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3278 "y.tab.c"
    break;

  case 152:
#line 1103 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = broken;
        code_tmp->code.broken.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3289 "y.tab.c"
    break;

  case 153:
#line 1113 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3298 "y.tab.c"
    break;

  case 154:
#line 1118 "gwarf_yacc.y"
    {
        append_elif((yyvsp[-1].if_list_base), (yyvsp[-2].statement_value)->code.if_branch.done);
        (yyval.statement_value) = (yyvsp[-2].statement_value);
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 3308 "y.tab.c"
    break;

  case 155:
#line 1127 "gwarf_yacc.y"
    {
        statement *done_tmp =  make_statement();
        (yyval.if_list_base) = make_if((yyvsp[-1].statement_value), done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
    }
#line 3318 "y.tab.c"
    break;

  case 156:
#line 1133 "gwarf_yacc.y"
    {
        statement *done_tmp =  make_statement();
        (yyval.if_list_base) = make_if(NULL, done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
    }
#line 3328 "y.tab.c"
    break;

  case 157:
#line 1142 "gwarf_yacc.y"
    {
        statement *if_tmp =  make_statement(), *done_tmp =  make_statement();
        if_tmp->type = if_branch;
        if_tmp->code.if_branch.done = make_if((yyvsp[-1].statement_value), done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = if_tmp;
    }
#line 3340 "y.tab.c"
    break;

  case 158:
#line 1153 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 3348 "y.tab.c"
    break;

  case 159:
#line 1160 "gwarf_yacc.y"
    {
        statement *block_tmp =  make_statement();
        block_tmp->type = code_block;
        block_tmp->code.code_block.done = make_statement();
        statement_base = append_statement_list(block_tmp->code.code_block.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = block_tmp;
    }
#line 3360 "y.tab.c"
    break;

  case 160:
#line 1171 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 3368 "y.tab.c"
    break;

  case 161:
#line 1178 "gwarf_yacc.y"
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
#line 3383 "y.tab.c"
    break;

  case 162:
#line 1189 "gwarf_yacc.y"
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
#line 3398 "y.tab.c"
    break;

  case 163:
#line 1200 "gwarf_yacc.y"
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
#line 3413 "y.tab.c"
    break;

  case 164:
#line 1211 "gwarf_yacc.y"
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
#line 3428 "y.tab.c"
    break;

  case 165:
#line 1222 "gwarf_yacc.y"
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
#line 3443 "y.tab.c"
    break;

  case 166:
#line 1233 "gwarf_yacc.y"
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
#line 3458 "y.tab.c"
    break;

  case 167:
#line 1244 "gwarf_yacc.y"
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
#line 3473 "y.tab.c"
    break;

  case 168:
#line 1255 "gwarf_yacc.y"
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
#line 3488 "y.tab.c"
    break;

  case 169:
#line 1266 "gwarf_yacc.y"
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_in_cycle;
        for_tmp->code.for_in_cycle.iter = (yyvsp[-1].statement_value);
        for_tmp->code.for_in_cycle.var = (yyvsp[-3].statement_value);
        for_tmp->code.for_in_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_in_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = for_tmp;
    }
#line 3502 "y.tab.c"
    break;

  case 170:
#line 1279 "gwarf_yacc.y"
    {
        statement *import_tmp =  make_statement();
        import_tmp->type = include_import;
        import_tmp->code.include_import.file = (yyvsp[0].statement_value);
        (yyval.statement_value) = import_tmp;
    }
#line 3513 "y.tab.c"
    break;

  case 171:
#line 1289 "gwarf_yacc.y"
    {
        statement *import_tmp =  make_statement();
        import_tmp->type = import_class;
        import_tmp->code.import_class.file = (yyvsp[-2].statement_value);

        import_tmp->code.import_class.var = (yyvsp[0].statement_value);

        (yyval.statement_value) = import_tmp;
    }
#line 3527 "y.tab.c"
    break;

  case 172:
#line 1302 "gwarf_yacc.y"
    {
        statement *raise_tmp =  make_statement();
        raise_tmp->type = raise_e;
        raise_tmp->code.raise_e.done = (yyvsp[-1].statement_value);
        raise_tmp->code.raise_e.info = (yyvsp[0].statement_value);
        (yyval.statement_value) = raise_tmp;
    }
#line 3539 "y.tab.c"
    break;

  case 173:
#line 1310 "gwarf_yacc.y"
    {
        statement *raise_tmp =  make_statement();
        raise_tmp->type = throw_e;
        raise_tmp->code.throw_e.done = (yyvsp[0].statement_value);
        (yyval.statement_value) = raise_tmp;
    }
#line 3550 "y.tab.c"
    break;

  case 174:
#line 1317 "gwarf_yacc.y"
    {
        statement *raise_tmp =  make_statement();
        raise_tmp->type = assert_e;
        raise_tmp->code.assert_e.condition = (yyvsp[-1].statement_value);
        raise_tmp->code.assert_e.info = (yyvsp[0].statement_value);
        (yyval.statement_value) = raise_tmp;
    }
#line 3562 "y.tab.c"
    break;

  case 175:
#line 1328 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3571 "y.tab.c"
    break;

  case 176:
#line 1336 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // out statement_base (FILO)

        (yyvsp[-4].statement_value)->code.try_code.var = (yyvsp[0].statement_value);  

        (yyvsp[-4].statement_value)->code.try_code.except = make_statement();
        statement_base = append_statement_list((yyvsp[-4].statement_value)->code.try_code.except, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = (yyvsp[-4].statement_value);
    }
#line 3585 "y.tab.c"
    break;

  case 177:
#line 1349 "gwarf_yacc.y"
    {
        statement *try_tmp =  make_statement();
        try_tmp->type = try_code;
        try_tmp->code.try_code.try = make_statement();
        statement_base = append_statement_list(try_tmp->code.try_code.try, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = try_tmp;
    }
#line 3597 "y.tab.c"
    break;

  case 178:
#line 1360 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyvsp[0].statement_value)->code.while_cycle.first_do = true;
        (yyval.statement_value) = (yyvsp[0].statement_value);
    }
#line 3607 "y.tab.c"
    break;

  case 179:
#line 1366 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyvsp[0].statement_value)->code.while_cycle.first_do = true;
        (yyval.statement_value) = (yyvsp[0].statement_value);
    }
#line 3617 "y.tab.c"
    break;

  case 180:
#line 1375 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyvsp[-1].statement_value)->code.while_cycle.first_do = false;
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3627 "y.tab.c"
    break;

  case 181:
#line 1384 "gwarf_yacc.y"
    {
        statement *while_tmp =  make_statement();
        while_tmp->type = while_cycle;
        while_tmp->code.while_cycle.condition = (yyvsp[-1].statement_value);
        while_tmp->code.while_cycle.done = make_statement();
        statement_base = append_statement_list(while_tmp->code.while_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = while_tmp;
    }
#line 3640 "y.tab.c"
    break;

  case 182:
#line 1396 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 3648 "y.tab.c"
    break;

  case 183:
#line 1403 "gwarf_yacc.y"
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
#line 3666 "y.tab.c"
    break;

  case 184:
#line 1417 "gwarf_yacc.y"
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
#line 3684 "y.tab.c"
    break;

  case 185:
#line 1434 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 3692 "y.tab.c"
    break;

  case 186:
#line 1441 "gwarf_yacc.y"
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
#line 3709 "y.tab.c"
    break;

  case 187:
#line 1454 "gwarf_yacc.y"
    {   
        statement *def_tmp =  make_statement();
        def_tmp->type = def;

        def_tmp->code.def.var = (yyvsp[-3].statement_value);
        def_tmp->code.def.parameter_list = (yyvsp[-1].parameter_list);
        def_tmp->code.def.done = make_statement();
        statement_base = append_statement_list(def_tmp->code.def.done, statement_base);  // new statement_base (FILO)

        (yyval.statement_value) = def_tmp;
    }
#line 3725 "y.tab.c"
    break;


#line 3729 "y.tab.c"

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
#line 1481 "gwarf_yacc.y"

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
