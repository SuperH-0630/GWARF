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
    DO = 340
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

#line 314 "y.tab.c"

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
#define YYFINAL  121
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   908

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  176
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  330

#define YYUNDEFTOK  2
#define YYMAXUTOK   340


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
      85
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    39,    39,    43,    50,    60,    64,    68,    72,    76,
      80,    84,    88,    92,    96,   102,   108,   112,   116,   120,
     124,   128,   132,   136,   140,   144,   148,   152,   156,   163,
     170,   171,   180,   189,   198,   207,   216,   225,   234,   243,
     252,   261,   270,   282,   283,   293,   302,   312,   324,   325,
     335,   347,   348,   358,   367,   379,   380,   389,   398,   407,
     416,   425,   437,   438,   447,   459,   460,   469,   478,   487,
     499,   500,   509,   518,   530,   531,   539,   547,   558,   559,
     560,   569,   577,   585,   592,   605,   617,   629,   641,   653,
     670,   682,   683,   691,   704,   711,   720,   734,   748,   763,
     768,   777,   783,   792,   803,   810,   821,   828,   839,   850,
     861,   872,   883,   894,   905,   916,   929,   939,   952,   960,
     970,   978,   991,  1002,  1008,  1017,  1026,  1038,  1045,  1059,
    1076,  1083,  1096,  1111,  1118,  1125,  1133,  1141,  1149,  1161,
    1166,  1172,  1180,  1189,  1197,  1201,  1206,  1214,  1221,  1222,
    1223,  1227,  1228,  1233,  1242,  1253,  1254,  1262,  1272,  1273,
    1281,  1291,  1292,  1300,  1310,  1311,  1319,  1329,  1330,  1338,
    1348,  1349,  1356,  1366,  1367,  1368,  1369
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
  "BITNOT", "BITNOTOR", "BITRIGHT", "BITLEFT", "PASS", "DO", "$accept",
  "command_block", "command_list", "command", "top_exp", "eq_number",
  "bit_number", "bit_move", "bool_number", "third_number", "second_number",
  "first_number", "zero_number", "call_number", "element", "base_value",
  "base_var_", "base_var_token", "base_string", "nonlocal_token",
  "global_token", "default_token", "if_block", "elif_exp", "if_exp",
  "block_block", "block_exp", "for_block", "for_exp", "include_exp",
  "import_exp", "raise_exp", "try_block", "try_exp", "try_token",
  "do_while_block", "while_block", "while_exp", "class_block", "class_exp",
  "def_block", "def_exp", "formal_parameter", "arguments",
  "slice_arguments", "slice_arguments_token", "block", "return_exp",
  "return_token", "restarted_exp", "restarted_token", "restart_exp",
  "restart_token", "continued_exp", "continued_token", "continue_exp",
  "continue_token", "break_exp", "break_token", "broken_exp",
  "broken_token", "stop_token", YY_NULLPTR
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
     335,   336,   337,   338,   339,   340
};
# endif

#define YYPACT_NINF (-138)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     496,  -138,  -138,  -138,  -138,   599,   774,    27,  -138,    31,
    -138,  -138,  -138,  -138,  -138,   -31,   -31,   182,    42,    36,
      42,    42,  -138,  -138,  -138,  -138,   599,  -138,   599,  -138,
     774,   774,   774,   774,   599,   774,   774,   239,    18,    53,
     496,  -138,   -31,    -4,    55,   -24,    29,   203,    90,     8,
     139,  -138,    -5,  -138,  -138,  -138,    59,   -31,   -31,   -31,
     109,    18,   -31,    18,   -31,    18,   -31,   -31,   -31,   -31,
      18,    18,   -31,   -31,    18,   -31,    18,   -31,    18,   -31,
     774,   -31,   599,   -31,   599,   -31,   599,   -31,   599,   -31,
     599,   -31,   599,   -18,    63,   774,   774,  -138,  -138,    99,
      99,   774,    51,    91,   -28,   599,   560,  -138,  -138,     1,
       6,   774,  -138,    81,  -138,   203,    -4,    -4,   -24,   349,
      78,  -138,  -138,    99,   828,   828,   828,   828,   828,   828,
     828,  -138,  -138,   828,   239,   239,   239,   239,   239,   599,
     599,   599,   599,   599,   599,   599,   599,   599,   599,   599,
     599,   599,   599,   599,   599,   599,    77,   774,   599,  -138,
      99,    99,    99,  -138,    96,    18,    99,  -138,    99,  -138,
      99,  -138,    99,    99,    99,    99,  -138,    85,    99,    99,
    -138,    99,  -138,    99,  -138,    99,   599,    99,   -18,    99,
     -18,    99,   -18,    99,   -18,    99,   -18,    99,   -18,   599,
    -138,   121,   142,  -138,  -138,  -138,    42,   774,  -138,   774,
     -18,   579,   126,    -7,    93,   158,  -138,   599,   155,   432,
     164,  -138,   101,    55,    55,    55,    55,    55,    55,    55,
      55,   -24,   -24,   -24,    29,    29,   203,   203,    90,    90,
      90,    90,    90,    90,     8,     8,   139,   139,   139,   139,
    -138,  -138,  -138,  -138,  -138,    20,   129,    25,   638,  -138,
     -18,   774,  -138,   131,   -18,   111,  -138,  -138,  -138,  -138,
    -138,   189,   657,   161,   686,   774,    16,  -138,   774,   193,
      43,  -138,    87,   -18,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,  -138,   129,  -138,   215,   599,   774,  -138,   221,   735,
     750,   195,   223,  -138,    51,   774,  -138,   103,  -138,  -138,
     -18,  -138,  -138,  -138,   225,  -138,   226,   789,  -138,  -138,
      16,   235,  -138,  -138,  -138,   236,  -138,   774,  -138,  -138
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    84,    85,    94,    93,     0,     0,     0,   169,     0,
     172,   166,   163,   160,   157,     0,     0,     0,     0,     0,
       0,     0,   105,    88,    87,    90,     0,   154,     0,   122,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     3,     0,    29,    30,    43,    48,    51,    55,    62,
      65,    70,    74,    78,    79,    91,    86,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     151,     0,   155,     0,   158,     0,   161,     0,   164,     0,
     167,     0,   170,    80,     0,     0,     0,   173,   174,    14,
      15,     0,   139,    79,     0,     0,     0,    97,    96,     0,
       0,     0,   119,     0,   116,    52,    40,    42,    47,     0,
       0,     1,     4,     5,     0,     0,     0,     0,     0,     0,
       0,    39,    41,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
      19,    17,    16,   102,     0,     0,     7,    99,    20,   104,
      18,   106,    27,    26,    25,    24,   120,     0,    28,     6,
     125,    23,   127,    21,   130,    22,   152,    13,   156,    12,
     159,    11,   162,    10,   165,     8,   168,     9,   171,     0,
      83,     0,     0,   176,   175,   143,     0,     0,    89,     0,
      98,     0,     0,    74,     0,     0,   118,     0,     0,     0,
       0,   123,     0,    31,    32,    33,    34,    35,    36,    37,
      38,    44,    45,    46,    49,    50,    53,    54,    58,    57,
      56,    59,    60,    61,    63,    64,    67,    66,    68,    69,
      71,    72,    73,    75,   139,     0,     0,    74,     0,   144,
      81,     0,   100,     0,   153,     0,   126,   103,    92,   141,
     140,    79,     0,     0,     0,     0,     0,   131,     0,   133,
       0,   128,     0,   117,   150,   148,   149,   124,    76,   147,
      82,    77,   146,   145,     0,     0,     0,   107,     0,     0,
       0,     0,     0,   134,     0,     0,   132,     0,   129,   101,
     121,   142,   110,   109,     0,   108,     0,     0,   115,   135,
       0,   136,   113,   111,   112,     0,   137,     0,   114,   138
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -138,  -138,   130,   -36,    -6,   134,   244,   -14,    57,   -22,
      33,    74,    62,    64,    24,  -138,   -16,   -15,  -138,  -138,
    -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,  -138,  -138,  -138,  -138,  -138,  -138,  -118,  -138,  -138,
    -138,  -138,  -138,  -137,  -138,    -2,   -33,  -138,  -138,  -138,
    -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,   258
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,   165,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,   280,   104,   258,   259,   120,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    99
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      94,   103,   221,   105,   122,   107,   108,   124,   156,   208,
     156,   102,   115,   209,    97,    98,   214,   149,   150,   255,
     199,   215,     4,   118,   111,   112,   113,   114,   167,    93,
     169,   157,   171,   157,   288,   119,   158,   176,   177,   199,
     156,   180,    95,   182,   199,   184,    96,   158,     4,   158,
     109,   106,   110,   121,   278,   158,   275,   306,   137,   138,
     158,   209,   290,   157,   159,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   186,   151,   152,   200,   282,   158,
       1,     2,     3,     4,   307,     5,   220,   101,   206,   201,
     202,   253,     6,   139,   140,   205,     7,   147,   148,     4,
     212,   308,   207,   276,   287,   216,   188,   277,   190,     4,
     192,   261,   194,   320,   196,    17,   198,   236,   237,     7,
     231,   232,   233,    97,    98,    23,    24,    25,   209,   210,
     213,   278,   262,   134,   135,   266,   136,   163,   164,   217,
     103,   278,   263,    34,   203,   204,   203,   204,   290,   199,
     254,   256,    35,    36,    97,    98,   267,    37,   153,   154,
     155,     1,     2,     3,     4,   158,     5,   274,   101,   116,
     117,   284,   281,     6,   238,   239,   240,   241,   242,   243,
     286,   257,   260,   122,   289,     1,     2,     3,     4,   295,
       5,   268,   101,   271,   234,   235,    17,     6,   279,   103,
     296,   269,   299,   270,   305,   273,    23,    24,    25,   254,
     264,   246,   247,   248,   249,   141,   142,   250,   251,   252,
      17,   244,   245,   265,    34,   143,   144,   145,   146,   309,
      23,    24,    25,    35,    36,   312,   317,   318,    37,   322,
     323,   283,     1,     2,     3,     4,   327,     5,    34,   219,
     328,     0,   292,     0,     6,   294,   293,    35,    36,     0,
     303,     0,    37,     0,     0,     0,   298,     0,   301,   302,
       0,     0,   304,     0,   100,     0,     0,    17,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    23,    24,    25,
     311,   321,     0,   314,   316,     0,     0,     0,     0,   319,
     123,     0,     0,     0,   326,    34,     0,     0,     0,     0,
       0,   325,     0,     0,     0,   160,   161,   162,   166,   310,
     168,   329,   170,     0,   172,   173,   174,   175,     0,     0,
     178,   179,     0,   181,     0,   183,     0,   185,     0,   187,
       0,   189,     0,   191,     0,   193,     0,   195,     0,   197,
       0,     0,     1,     2,     3,     4,     0,     5,     0,     0,
       0,     0,     0,     0,     6,     0,   119,     7,   223,   224,
     225,   226,   227,   228,   229,     8,     9,   230,   222,    10,
      11,    12,    13,    14,    15,    16,     0,    17,    18,    19,
       0,    20,    21,     0,     0,     0,    22,    23,    24,    25,
      26,    27,    28,     0,     0,    29,     0,     0,    30,    31,
      32,    33,     0,     0,     0,    34,     0,     0,     0,     0,
       0,     0,     0,     0,    35,    36,     0,     0,     0,    37,
       0,     0,     0,   218,    38,     1,     2,     3,     4,     0,
       5,     0,     0,     0,     0,     0,     0,     6,   285,     0,
       7,     0,     0,     0,     0,     0,     0,     0,     8,     9,
       0,     0,    10,    11,    12,    13,    14,    15,    16,     0,
      17,    18,    19,     0,    20,    21,     0,     0,     0,    22,
      23,    24,    25,    26,    27,    28,     0,     0,    29,     0,
       0,    30,    31,    32,    33,     0,     0,     0,    34,     1,
       2,     3,     4,     0,     5,     0,     0,    35,    36,     0,
       0,     6,    37,     0,     7,     0,     0,    38,     0,     0,
       0,     0,     8,     9,     0,     0,    10,    11,    12,    13,
      14,    15,    16,     0,    17,    18,    19,     0,    20,    21,
       0,     0,     0,    22,    23,    24,    25,    26,    27,    28,
       0,     0,    29,     0,     0,    30,    31,    32,    33,     0,
       0,     0,    34,     1,     2,     3,     4,     0,     5,     0,
       0,    35,    36,     0,     0,     6,    37,     0,     0,     0,
       0,    38,     1,     2,     3,     4,     0,     5,     0,     0,
       0,     0,     0,     0,     6,     0,     0,     0,    17,     0,
       0,   211,     1,     2,     3,     4,     0,     5,    23,    24,
      25,     0,     0,     0,     6,     0,     0,    17,     0,     0,
     272,     0,     0,     0,     0,     0,    34,    23,    24,    25,
       0,     0,     0,     0,     0,    35,    36,    17,     0,     0,
      37,     1,     2,     3,     4,    34,     5,    23,    24,    25,
       0,     0,     0,     6,    35,    36,     0,     0,     0,    37,
       1,     2,     3,     4,     0,     5,     0,     0,     0,     0,
       0,   297,     6,     0,     0,   291,    17,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    23,    24,    25,     1,
       2,     3,     4,     0,     5,    17,     0,     0,     0,     0,
       0,     6,     0,     0,    34,    23,    24,    25,     0,     0,
       0,     0,     0,    35,    36,     0,     0,     0,    37,     0,
       0,     0,     0,    34,    17,     0,     0,   300,     0,     0,
       0,     0,    35,    36,    23,    24,    25,    37,     1,     2,
       3,     4,     0,     5,     0,     0,     0,     0,     0,   313,
       6,     0,    34,     1,     2,     3,     4,     0,     5,     0,
       0,    35,    36,     0,   315,     6,    37,     0,     0,     0,
       0,     0,     0,    17,     0,     0,     0,     1,     2,     3,
       4,     0,     5,    23,    24,    25,     0,     0,    17,     6,
       0,     0,     1,     2,     3,     4,     0,     5,    23,    24,
      25,    34,     0,   324,     6,     0,     0,     0,     0,     0,
      35,    36,    17,     0,     0,    37,    34,     0,     0,     0,
       0,     0,    23,    24,    25,    35,    36,    17,     0,     0,
      37,     1,     2,     3,     4,     0,     5,    23,    24,    25,
      34,     0,     0,     6,     0,     0,     0,     0,     0,    35,
      36,     0,     0,     0,    37,    34,     0,     0,     0,     0,
       0,     0,     0,     0,    35,    36,    17,     0,     0,    37,
       0,     0,     0,     0,     0,     0,    23,    24,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37
};

static const yytype_int16 yycheck[] =
{
       6,    17,   120,    18,    40,    20,    21,    11,    15,    37,
      15,    17,    34,    41,    45,    46,    15,     9,    10,   156,
      38,    15,     6,    37,    30,    31,    32,    33,    61,     5,
      63,    38,    65,    38,    14,    17,    54,    70,    71,    38,
      15,    74,    15,    76,    38,    78,    15,    54,     6,    54,
      26,    15,    28,     0,    38,    54,    63,    14,    82,    83,
      54,    41,    37,    38,     5,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    80,    67,    68,    14,   215,    54,
       3,     4,     5,     6,    41,     8,   119,    10,    37,    95,
      96,    14,    15,    64,    65,   101,    18,     7,     8,     6,
     106,    14,    11,    10,   222,   111,    82,    14,    84,     6,
      86,    15,    88,    10,    90,    38,    92,   139,   140,    18,
     134,   135,   136,    45,    46,    48,    49,    50,    41,   105,
     106,    38,   165,    78,    79,    14,    81,    28,    29,    58,
     156,    38,    57,    66,    45,    46,    45,    46,    37,    38,
     156,   157,    75,    76,    45,    46,    14,    80,    19,    20,
      21,     3,     4,     5,     6,    54,     8,    41,    10,    35,
      36,    16,    14,    15,   141,   142,   143,   144,   145,   146,
      16,   157,   158,   219,    55,     3,     4,     5,     6,    58,
       8,   206,    10,   209,   137,   138,    38,    15,   214,   215,
      11,   207,    41,   209,    11,   211,    48,    49,    50,   215,
     186,   149,   150,   151,   152,    12,    13,   153,   154,   155,
      38,   147,   148,   199,    66,    22,    23,    24,    25,    14,
      48,    49,    50,    75,    76,    14,    41,    14,    80,    14,
      14,   217,     3,     4,     5,     6,    11,     8,    66,   119,
      14,    -1,   258,    -1,    15,   261,   258,    75,    76,    -1,
     276,    -1,    80,    -1,    -1,    -1,   272,    -1,   274,   275,
      -1,    -1,   278,    -1,    16,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
     296,   307,    -1,   299,   300,    -1,    -1,    -1,    -1,   305,
      42,    -1,    -1,    -1,   320,    66,    -1,    -1,    -1,    -1,
      -1,   317,    -1,    -1,    -1,    57,    58,    59,    60,   295,
      62,   327,    64,    -1,    66,    67,    68,    69,    -1,    -1,
      72,    73,    -1,    75,    -1,    77,    -1,    79,    -1,    81,
      -1,    83,    -1,    85,    -1,    87,    -1,    89,    -1,    91,
      -1,    -1,     3,     4,     5,     6,    -1,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    -1,    17,    18,   124,   125,
     126,   127,   128,   129,   130,    26,    27,   133,   120,    30,
      31,    32,    33,    34,    35,    36,    -1,    38,    39,    40,
      -1,    42,    43,    -1,    -1,    -1,    47,    48,    49,    50,
      51,    52,    53,    -1,    -1,    56,    -1,    -1,    59,    60,
      61,    62,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    80,
      -1,    -1,    -1,    84,    85,     3,     4,     5,     6,    -1,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    -1,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      38,    39,    40,    -1,    42,    43,    -1,    -1,    -1,    47,
      48,    49,    50,    51,    52,    53,    -1,    -1,    56,    -1,
      -1,    59,    60,    61,    62,    -1,    -1,    -1,    66,     3,
       4,     5,     6,    -1,     8,    -1,    -1,    75,    76,    -1,
      -1,    15,    80,    -1,    18,    -1,    -1,    85,    -1,    -1,
      -1,    -1,    26,    27,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    38,    39,    40,    -1,    42,    43,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    56,    -1,    -1,    59,    60,    61,    62,    -1,
      -1,    -1,    66,     3,     4,     5,     6,    -1,     8,    -1,
      -1,    75,    76,    -1,    -1,    15,    80,    -1,    -1,    -1,
      -1,    85,     3,     4,     5,     6,    -1,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,    38,    -1,
      -1,    41,     3,     4,     5,     6,    -1,     8,    48,    49,
      50,    -1,    -1,    -1,    15,    -1,    -1,    38,    -1,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    66,    48,    49,    50,
      -1,    -1,    -1,    -1,    -1,    75,    76,    38,    -1,    -1,
      80,     3,     4,     5,     6,    66,     8,    48,    49,    50,
      -1,    -1,    -1,    15,    75,    76,    -1,    -1,    -1,    80,
       3,     4,     5,     6,    -1,     8,    -1,    -1,    -1,    -1,
      -1,    14,    15,    -1,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,     3,
       4,     5,     6,    -1,     8,    38,    -1,    -1,    -1,    -1,
      -1,    15,    -1,    -1,    66,    48,    49,    50,    -1,    -1,
      -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    66,    38,    -1,    -1,    41,    -1,    -1,
      -1,    -1,    75,    76,    48,    49,    50,    80,     3,     4,
       5,     6,    -1,     8,    -1,    -1,    -1,    -1,    -1,    14,
      15,    -1,    66,     3,     4,     5,     6,    -1,     8,    -1,
      -1,    75,    76,    -1,    14,    15,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    -1,     3,     4,     5,
       6,    -1,     8,    48,    49,    50,    -1,    -1,    38,    15,
      -1,    -1,     3,     4,     5,     6,    -1,     8,    48,    49,
      50,    66,    -1,    14,    15,    -1,    -1,    -1,    -1,    -1,
      75,    76,    38,    -1,    -1,    80,    66,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    75,    76,    38,    -1,    -1,
      80,     3,     4,     5,     6,    -1,     8,    48,    49,    50,
      66,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    75,
      76,    -1,    -1,    -1,    80,    66,    -1,    -1,    -1,    -1,
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
       0,     3,     4,     5,     6,     8,    15,    18,    26,    27,
      30,    31,    32,    33,    34,    35,    36,    38,    39,    40,
      42,    43,    47,    48,    49,    50,    51,    52,    53,    56,
      59,    60,    61,    62,    66,    75,    76,    80,    85,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   100,    90,    15,    15,    45,    46,   147,
     147,    10,    90,   102,   129,   103,    15,   103,   103,   100,
     100,    90,    90,    90,    90,    95,    91,    91,    93,    17,
     132,     0,    89,   147,    11,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    81,    82,    83,    64,
      65,    12,    13,    22,    23,    24,    25,     7,     8,     9,
      10,    67,    68,    19,    20,    21,    15,    38,    54,     5,
     147,   147,   147,    28,    29,   109,   147,   132,   147,   132,
     147,   132,   147,   147,   147,   147,   132,   132,   147,   147,
     132,   147,   132,   147,   132,   147,    90,   147,   100,   147,
     100,   147,   100,   147,   100,   147,   100,   147,   100,    38,
      14,    90,    90,    45,    46,    90,    37,    11,    37,    41,
     100,    41,    90,   100,    15,    15,    90,    58,    84,    88,
     132,   123,   147,    92,    92,    92,    92,    92,    92,    92,
      92,    93,    93,    93,    94,    94,    95,    95,    96,    96,
      96,    96,    96,    96,    97,    97,    98,    98,    98,    98,
      99,    99,    99,    14,    90,   129,    90,   100,   130,   131,
     100,    15,   132,    57,   100,   100,    14,    14,   103,    90,
      90,   102,    41,    90,    41,    63,    10,    14,    38,   102,
     128,    14,   129,   100,    16,    16,    16,   123,    14,    55,
      37,    37,    90,   131,    90,    58,    11,    14,    90,    41,
      41,    90,    90,   102,    90,    11,    14,    41,    14,    14,
     100,    90,    14,    14,    90,    14,    90,    41,    14,    90,
      10,   102,    14,    14,    14,    90,   102,    11,    14,    90
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    88,    88,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    90,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    92,    92,    92,    92,    92,    93,    93,
      93,    94,    94,    94,    94,    95,    95,    95,    95,    95,
      95,    95,    96,    96,    96,    97,    97,    97,    97,    97,
      98,    98,    98,    98,    99,    99,    99,    99,   100,   100,
     100,   100,   100,   100,   101,   101,   101,   101,   101,   101,
     101,   102,   102,   103,   104,   104,   105,   106,   107,   108,
     108,   109,   109,   110,   111,   112,   113,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   115,   116,   117,   117,
     118,   119,   120,   121,   121,   122,   123,   124,   125,   125,
     126,   127,   127,   128,   128,   128,   128,   128,   128,   129,
     129,   129,   129,   129,   130,   130,   130,   131,   132,   132,
     132,   133,   133,   133,   134,   135,   135,   136,   137,   137,
     138,   139,   139,   140,   141,   141,   142,   143,   143,   144,
     145,   145,   146,   147,   147,   147,   147
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     1,     3,     3,     3,     2,     1,     3,
       3,     1,     2,     3,     3,     1,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     3,     1,     3,     4,     4,     1,     1,
       2,     3,     4,     3,     1,     1,     1,     1,     1,     3,
       1,     1,     4,     1,     1,     2,     2,     2,     3,     2,
       3,     4,     1,     4,     2,     1,     2,     5,     6,     6,
       6,     7,     7,     7,     8,     6,     2,     4,     3,     2,
       2,     5,     1,     3,     4,     2,     4,     2,     4,     5,
       2,     4,     5,     1,     2,     3,     3,     4,     5,     1,
       3,     3,     5,     2,     1,     2,     2,     2,     3,     3,
       3,     1,     2,     3,     1,     1,     2,     1,     1,     2,
       1,     1,     2,     1,     1,     2,     1,     1,     2,     1,
       1,     2,     1,     1,     1,     2,     2
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
#line 44 "gwarf_yacc.y"
    {
        if((yyvsp[0].statement_value) != NULL){
            statement *tmp = find_statement_list(0, statement_base);
            append_statement(tmp, (yyvsp[0].statement_value));
        }
    }
#line 1860 "y.tab.c"
    break;

  case 4:
#line 51 "gwarf_yacc.y"
    {   
        if((yyvsp[0].statement_value) != NULL){
            statement *tmp = find_statement_list(0, statement_base);
            append_statement(tmp, (yyvsp[0].statement_value));
        }
    }
#line 1871 "y.tab.c"
    break;

  case 5:
#line 61 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1879 "y.tab.c"
    break;

  case 6:
#line 65 "gwarf_yacc.y"
    {   
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1887 "y.tab.c"
    break;

  case 7:
#line 69 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1895 "y.tab.c"
    break;

  case 8:
#line 73 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1903 "y.tab.c"
    break;

  case 9:
#line 77 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1911 "y.tab.c"
    break;

  case 10:
#line 81 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1919 "y.tab.c"
    break;

  case 11:
#line 85 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1927 "y.tab.c"
    break;

  case 12:
#line 89 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1935 "y.tab.c"
    break;

  case 13:
#line 93 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1943 "y.tab.c"
    break;

  case 14:
#line 97 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = rego;
        (yyval.statement_value) = code_tmp;
    }
#line 1953 "y.tab.c"
    break;

  case 15:
#line 103 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = rewent;
        (yyval.statement_value) = code_tmp;
    }
#line 1963 "y.tab.c"
    break;

  case 16:
#line 109 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1971 "y.tab.c"
    break;

  case 17:
#line 113 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1979 "y.tab.c"
    break;

  case 18:
#line 117 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1987 "y.tab.c"
    break;

  case 19:
#line 121 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1995 "y.tab.c"
    break;

  case 20:
#line 125 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2003 "y.tab.c"
    break;

  case 21:
#line 129 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2011 "y.tab.c"
    break;

  case 22:
#line 133 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2019 "y.tab.c"
    break;

  case 23:
#line 137 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2027 "y.tab.c"
    break;

  case 24:
#line 141 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2035 "y.tab.c"
    break;

  case 25:
#line 145 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2043 "y.tab.c"
    break;

  case 26:
#line 149 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2051 "y.tab.c"
    break;

  case 27:
#line 153 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2059 "y.tab.c"
    break;

  case 28:
#line 157 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2067 "y.tab.c"
    break;

  case 29:
#line 164 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[0].statement_value);
    }
#line 2075 "y.tab.c"
    break;

  case 31:
#line 172 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ASSIGnMENT_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2088 "y.tab.c"
    break;

  case 32:
#line 181 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AADD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2101 "y.tab.c"
    break;

  case 33:
#line 190 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ASUB_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2114 "y.tab.c"
    break;

  case 34:
#line 199 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AMUL_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2127 "y.tab.c"
    break;

  case 35:
#line 208 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ADIV_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2140 "y.tab.c"
    break;

  case 36:
#line 217 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AMOD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2153 "y.tab.c"
    break;

  case 37:
#line 226 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AINTDIV_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2166 "y.tab.c"
    break;

  case 38:
#line 235 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = APOW_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2179 "y.tab.c"
    break;

  case 39:
#line 244 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LADD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-1].statement_value);
        code_tmp->code.operation.right_exp = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2192 "y.tab.c"
    break;

  case 40:
#line 253 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = FADD_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2205 "y.tab.c"
    break;

  case 41:
#line 262 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LSUB_func;
        code_tmp->code.operation.left_exp = (yyvsp[-1].statement_value);
        code_tmp->code.operation.right_exp = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2218 "y.tab.c"
    break;

  case 42:
#line 271 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = FSUB_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2231 "y.tab.c"
    break;

  case 44:
#line 284 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITAND_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        puts("NOT FUNC");
        (yyval.statement_value) = code_tmp;
    }
#line 2245 "y.tab.c"
    break;

  case 45:
#line 294 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITOR_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2258 "y.tab.c"
    break;

  case 46:
#line 303 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITNOTOR_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        puts("NOT FUNC");
        (yyval.statement_value) = code_tmp;
    }
#line 2272 "y.tab.c"
    break;

  case 47:
#line 313 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITNOT_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2285 "y.tab.c"
    break;

  case 49:
#line 326 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITRIGHT_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        puts("NOT FUNC");
        (yyval.statement_value) = code_tmp;
    }
#line 2299 "y.tab.c"
    break;

  case 50:
#line 336 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITLEFT_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2312 "y.tab.c"
    break;

  case 52:
#line 349 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NOT_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        puts("NOT FUNC");
        (yyval.statement_value) = code_tmp;
    }
#line 2326 "y.tab.c"
    break;

  case 53:
#line 359 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AND_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2339 "y.tab.c"
    break;

  case 54:
#line 368 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = OR_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2352 "y.tab.c"
    break;

  case 56:
#line 381 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = EQUAL_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2365 "y.tab.c"
    break;

  case 57:
#line 390 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MORE_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2378 "y.tab.c"
    break;

  case 58:
#line 399 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LESS_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2391 "y.tab.c"
    break;

  case 59:
#line 408 "gwarf_yacc.y"
        {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MOREEQ_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2404 "y.tab.c"
    break;

  case 60:
#line 417 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LESSEQ_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2417 "y.tab.c"
    break;

  case 61:
#line 426 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NOTEQ_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2430 "y.tab.c"
    break;

  case 63:
#line 439 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ADD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2443 "y.tab.c"
    break;

  case 64:
#line 448 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = SUB_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2456 "y.tab.c"
    break;

  case 66:
#line 461 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MUL_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2469 "y.tab.c"
    break;

  case 67:
#line 470 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = DIV_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2482 "y.tab.c"
    break;

  case 68:
#line 479 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MOD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2495 "y.tab.c"
    break;

  case 69:
#line 488 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = INTDIV_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2508 "y.tab.c"
    break;

  case 71:
#line 501 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = POW_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2521 "y.tab.c"
    break;

  case 72:
#line 510 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LOG_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2534 "y.tab.c"
    break;

  case 73:
#line 519 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = SQRT_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2547 "y.tab.c"
    break;

  case 75:
#line 532 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = (yyvsp[-2].statement_value);
        code_tmp->code.call.parameter_list = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2559 "y.tab.c"
    break;

  case 76:
#line 540 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = (yyvsp[-3].statement_value);
        code_tmp->code.call.parameter_list = (yyvsp[-1].parameter_list);
        (yyval.statement_value) = code_tmp;
    }
#line 2571 "y.tab.c"
    break;

  case 77:
#line 548 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = slice;
        code_tmp->code.slice.base_var = (yyvsp[-3].statement_value);
        code_tmp->code.slice.value = (yyvsp[-1].parameter_list);
        (yyval.statement_value) = code_tmp; 
    }
#line 2583 "y.tab.c"
    break;

  case 80:
#line 561 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NEGATIVE_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 2596 "y.tab.c"
    break;

  case 81:
#line 570 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = point;
        code_tmp->code.point.base_var = (yyvsp[-2].statement_value);
        code_tmp->code.point.child_var = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp; 
    }
#line 2608 "y.tab.c"
    break;

  case 82:
#line 578 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = down;
        code_tmp->code.down.base_var = (yyvsp[-3].statement_value);
        code_tmp->code.down.child_var = (yyvsp[-1].statement_value);
        (yyval.statement_value) = code_tmp; 
    }
#line 2620 "y.tab.c"
    break;

  case 83:
#line 586 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2628 "y.tab.c"
    break;

  case 84:
#line 593 "gwarf_yacc.y"
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
#line 2645 "y.tab.c"
    break;

  case 85:
#line 606 "gwarf_yacc.y"
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
#line 2661 "y.tab.c"
    break;

  case 86:
#line 618 "gwarf_yacc.y"
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
#line 2677 "y.tab.c"
    break;

  case 87:
#line 630 "gwarf_yacc.y"
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
#line 2693 "y.tab.c"
    break;

  case 88:
#line 642 "gwarf_yacc.y"
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
#line 2709 "y.tab.c"
    break;

  case 89:
#line 654 "gwarf_yacc.y"
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
#line 2730 "y.tab.c"
    break;

  case 90:
#line 671 "gwarf_yacc.y"
    {
        // NULL代表空值，是GWARF_value
        statement *code_tmp =  make_statement();
        code_tmp->type = base_value;
        code_tmp->code.base_value.value.type = NULL_value;
        code_tmp->code.base_value.value.value.int_value = 0;
        (yyval.statement_value) = code_tmp;
    }
#line 2743 "y.tab.c"
    break;

  case 92:
#line 684 "gwarf_yacc.y"
    {
        (yyvsp[0].statement_value)->code.base_var.from = (yyvsp[-2].statement_value);
        (yyval.statement_value) = (yyvsp[0].statement_value);
    }
#line 2752 "y.tab.c"
    break;

  case 93:
#line 692 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->code.base_var.var_name = malloc(sizeof((yyvsp[0].string_value)));
        char *name_tmp = code_tmp->code.base_var.var_name;
        code_tmp->type = base_var;
        code_tmp->code.base_var.from = NULL;
        strcpy(name_tmp, (yyvsp[0].string_value));
        (yyval.statement_value) = code_tmp;
    }
#line 2766 "y.tab.c"
    break;

  case 94:
#line 705 "gwarf_yacc.y"
    {
        // STRING is char * which the len is 1
        char *tmp = malloc(sizeof((yyvsp[0].string_value)));
        strcpy(tmp, (yyvsp[0].string_value));
        (yyval.string_value) = tmp;
    }
#line 2777 "y.tab.c"
    break;

  case 95:
#line 712 "gwarf_yacc.y"
    {
        char *tmp = realloc((yyvsp[-1].string_value), strlen((yyvsp[-1].string_value)) + strlen((yyvsp[0].string_value)));  // get address
        strcat(tmp, (yyvsp[0].string_value));
        (yyval.string_value) = tmp;
    }
#line 2787 "y.tab.c"
    break;

  case 96:
#line 721 "gwarf_yacc.y"
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
#line 2802 "y.tab.c"
    break;

  case 97:
#line 735 "gwarf_yacc.y"
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
#line 2817 "y.tab.c"
    break;

  case 98:
#line 749 "gwarf_yacc.y"
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
#line 2833 "y.tab.c"
    break;

  case 99:
#line 764 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2842 "y.tab.c"
    break;

  case 100:
#line 769 "gwarf_yacc.y"
    {
        append_elif((yyvsp[-1].if_list_base), (yyvsp[-2].statement_value)->code.if_branch.done);
        (yyval.statement_value) = (yyvsp[-2].statement_value);
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 2852 "y.tab.c"
    break;

  case 101:
#line 778 "gwarf_yacc.y"
    {
        statement *done_tmp =  make_statement();
        (yyval.if_list_base) = make_if((yyvsp[-1].statement_value), done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
    }
#line 2862 "y.tab.c"
    break;

  case 102:
#line 784 "gwarf_yacc.y"
    {
        statement *done_tmp =  make_statement();
        (yyval.if_list_base) = make_if(NULL, done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
    }
#line 2872 "y.tab.c"
    break;

  case 103:
#line 793 "gwarf_yacc.y"
    {
        statement *if_tmp =  make_statement(), *done_tmp =  make_statement();
        if_tmp->type = if_branch;
        if_tmp->code.if_branch.done = make_if((yyvsp[-1].statement_value), done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = if_tmp;
    }
#line 2884 "y.tab.c"
    break;

  case 104:
#line 804 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 2892 "y.tab.c"
    break;

  case 105:
#line 811 "gwarf_yacc.y"
    {
        statement *block_tmp =  make_statement();
        block_tmp->type = code_block;
        block_tmp->code.code_block.done = make_statement();
        statement_base = append_statement_list(block_tmp->code.code_block.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = block_tmp;
    }
#line 2904 "y.tab.c"
    break;

  case 106:
#line 822 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 2912 "y.tab.c"
    break;

  case 107:
#line 829 "gwarf_yacc.y"
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
#line 2927 "y.tab.c"
    break;

  case 108:
#line 840 "gwarf_yacc.y"
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
#line 2942 "y.tab.c"
    break;

  case 109:
#line 851 "gwarf_yacc.y"
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
#line 2957 "y.tab.c"
    break;

  case 110:
#line 862 "gwarf_yacc.y"
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
#line 2972 "y.tab.c"
    break;

  case 111:
#line 873 "gwarf_yacc.y"
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
#line 2987 "y.tab.c"
    break;

  case 112:
#line 884 "gwarf_yacc.y"
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
#line 3002 "y.tab.c"
    break;

  case 113:
#line 895 "gwarf_yacc.y"
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
#line 3017 "y.tab.c"
    break;

  case 114:
#line 906 "gwarf_yacc.y"
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
#line 3032 "y.tab.c"
    break;

  case 115:
#line 917 "gwarf_yacc.y"
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_in_cycle;
        for_tmp->code.for_in_cycle.iter = (yyvsp[-1].statement_value);
        for_tmp->code.for_in_cycle.var = (yyvsp[-3].statement_value);
        for_tmp->code.for_in_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_in_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = for_tmp;
    }
#line 3046 "y.tab.c"
    break;

  case 116:
#line 930 "gwarf_yacc.y"
    {
        statement *import_tmp =  make_statement();
        import_tmp->type = include_import;
        import_tmp->code.include_import.file = (yyvsp[0].statement_value);
        (yyval.statement_value) = import_tmp;
    }
#line 3057 "y.tab.c"
    break;

  case 117:
#line 940 "gwarf_yacc.y"
    {
        statement *import_tmp =  make_statement();
        import_tmp->type = import_class;
        import_tmp->code.import_class.file = (yyvsp[-2].statement_value);

        import_tmp->code.import_class.var = (yyvsp[0].statement_value);

        (yyval.statement_value) = import_tmp;
    }
#line 3071 "y.tab.c"
    break;

  case 118:
#line 953 "gwarf_yacc.y"
    {
        statement *raise_tmp =  make_statement();
        raise_tmp->type = raise_e;
        raise_tmp->code.raise_e.done = (yyvsp[-1].statement_value);
        raise_tmp->code.raise_e.info = (yyvsp[0].statement_value);
        (yyval.statement_value) = raise_tmp;
    }
#line 3083 "y.tab.c"
    break;

  case 119:
#line 961 "gwarf_yacc.y"
    {
        statement *raise_tmp =  make_statement();
        raise_tmp->type = throw_e;
        raise_tmp->code.throw_e.done = (yyvsp[0].statement_value);
        (yyval.statement_value) = raise_tmp;
    }
#line 3094 "y.tab.c"
    break;

  case 120:
#line 971 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3103 "y.tab.c"
    break;

  case 121:
#line 979 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // out statement_base (FILO)

        (yyvsp[-4].statement_value)->code.try_code.var = (yyvsp[0].statement_value);  

        (yyvsp[-4].statement_value)->code.try_code.except = make_statement();
        statement_base = append_statement_list((yyvsp[-4].statement_value)->code.try_code.except, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = (yyvsp[-4].statement_value);
    }
#line 3117 "y.tab.c"
    break;

  case 122:
#line 992 "gwarf_yacc.y"
    {
        statement *try_tmp =  make_statement();
        try_tmp->type = try_code;
        try_tmp->code.try_code.try = make_statement();
        statement_base = append_statement_list(try_tmp->code.try_code.try, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = try_tmp;
    }
#line 3129 "y.tab.c"
    break;

  case 123:
#line 1003 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyvsp[0].statement_value)->code.while_cycle.first_do = true;
        (yyval.statement_value) = (yyvsp[0].statement_value);
    }
#line 3139 "y.tab.c"
    break;

  case 124:
#line 1009 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyvsp[0].statement_value)->code.while_cycle.first_do = true;
        (yyval.statement_value) = (yyvsp[0].statement_value);
    }
#line 3149 "y.tab.c"
    break;

  case 125:
#line 1018 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyvsp[-1].statement_value)->code.while_cycle.first_do = false;
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3159 "y.tab.c"
    break;

  case 126:
#line 1027 "gwarf_yacc.y"
    {
        statement *while_tmp =  make_statement();
        while_tmp->type = while_cycle;
        while_tmp->code.while_cycle.condition = (yyvsp[-1].statement_value);
        while_tmp->code.while_cycle.done = make_statement();
        statement_base = append_statement_list(while_tmp->code.while_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = while_tmp;
    }
#line 3172 "y.tab.c"
    break;

  case 127:
#line 1039 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 3180 "y.tab.c"
    break;

  case 128:
#line 1046 "gwarf_yacc.y"
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
#line 3198 "y.tab.c"
    break;

  case 129:
#line 1060 "gwarf_yacc.y"
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
#line 3216 "y.tab.c"
    break;

  case 130:
#line 1077 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 3224 "y.tab.c"
    break;

  case 131:
#line 1084 "gwarf_yacc.y"
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
#line 3241 "y.tab.c"
    break;

  case 132:
#line 1097 "gwarf_yacc.y"
    {   
        statement *def_tmp =  make_statement();
        def_tmp->type = def;

        def_tmp->code.def.var = (yyvsp[-3].statement_value);
        def_tmp->code.def.parameter_list = (yyvsp[-1].parameter_list);
        def_tmp->code.def.done = make_statement();
        statement_base = append_statement_list(def_tmp->code.def.done, statement_base);  // new statement_base (FILO)

        (yyval.statement_value) = def_tmp;
    }
#line 3257 "y.tab.c"
    break;

  case 133:
#line 1112 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_name((yyvsp[0].statement_value)->code.base_var.var_name);
        (yyval.parameter_list)->type = only_name;
        free((yyvsp[0].statement_value)->code.base_var.var_name);
        free((yyvsp[0].statement_value));
    }
#line 3268 "y.tab.c"
    break;

  case 134:
#line 1119 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_name((yyvsp[0].statement_value)->code.base_var.var_name);
        (yyval.parameter_list)->type = put_args;
        free((yyvsp[0].statement_value)->code.base_var.var_name);
        free((yyvsp[0].statement_value));
    }
#line 3279 "y.tab.c"
    break;

  case 135:
#line 1126 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_name((yyvsp[-2].statement_value)->code.base_var.var_name);
        (yyval.parameter_list)->u.value = (yyvsp[0].statement_value);
        (yyval.parameter_list)->type = name_value;
        free((yyvsp[-2].statement_value)->code.base_var.var_name);
        free((yyvsp[-2].statement_value));
    }
#line 3291 "y.tab.c"
    break;

  case 136:
#line 1134 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_name((yyvsp[0].statement_value)->code.base_var.var_name, (yyvsp[-2].parameter_list));
        tmp->type = only_name;
        (yyval.parameter_list) = (yyvsp[-2].parameter_list);
        free((yyvsp[0].statement_value)->code.base_var.var_name);
        free((yyvsp[0].statement_value));
    }
#line 3303 "y.tab.c"
    break;

  case 137:
#line 1142 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_name((yyvsp[0].statement_value)->code.base_var.var_name, (yyvsp[-3].parameter_list));
        tmp->type = put_args;
        (yyval.parameter_list) = (yyvsp[-3].parameter_list);
        free((yyvsp[0].statement_value)->code.base_var.var_name);
        free((yyvsp[0].statement_value));
    }
#line 3315 "y.tab.c"
    break;

  case 138:
#line 1150 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_name((yyvsp[-2].statement_value)->code.base_var.var_name, (yyvsp[-4].parameter_list));
        tmp->u.value = (yyvsp[0].statement_value);
        tmp->type = name_value;
        (yyval.parameter_list) = (yyvsp[-4].parameter_list);
        free((yyvsp[-2].statement_value)->code.base_var.var_name);
        free((yyvsp[-2].statement_value));
    }
#line 3328 "y.tab.c"
    break;

  case 139:
#line 1162 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_value((yyvsp[0].statement_value));
        (yyval.parameter_list)->type = only_value;
    }
#line 3337 "y.tab.c"
    break;

  case 140:
#line 1167 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_value((yyvsp[0].statement_value), (yyvsp[-2].parameter_list));
        tmp->type = only_value;
        (yyval.parameter_list) = (yyvsp[-2].parameter_list);
    }
#line 3347 "y.tab.c"
    break;

  case 141:
#line 1173 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_name((yyvsp[-2].statement_value)->code.base_var.var_name);
        (yyval.parameter_list)->u.value = (yyvsp[0].statement_value);
        (yyval.parameter_list)->type = name_value;
        free((yyvsp[-2].statement_value)->code.base_var.var_name);
        free((yyvsp[-2].statement_value));
    }
#line 3359 "y.tab.c"
    break;

  case 142:
#line 1181 "gwarf_yacc.y"
    {
        parameter *tmp = append_parameter_name((yyvsp[-2].statement_value)->code.base_var.var_name, (yyvsp[-4].parameter_list));
        tmp->u.value = (yyvsp[0].statement_value);
        tmp->type = name_value;
        (yyval.parameter_list) = (yyvsp[-4].parameter_list);
        free((yyvsp[-2].statement_value)->code.base_var.var_name);
        free((yyvsp[-2].statement_value));
    }
#line 3372 "y.tab.c"
    break;

  case 143:
#line 1190 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_value((yyvsp[0].statement_value));
        (yyval.parameter_list)->type = put_args;
    }
#line 3381 "y.tab.c"
    break;

  case 144:
#line 1198 "gwarf_yacc.y"
    {
        (yyval.parameter_list) = make_parameter_value((yyvsp[0].statement_value));
    }
#line 3389 "y.tab.c"
    break;

  case 145:
#line 1202 "gwarf_yacc.y"
    {
        append_parameter_value((yyvsp[0].statement_value), (yyvsp[-1].parameter_list));
        (yyval.parameter_list) = (yyvsp[-1].parameter_list);
    }
#line 3398 "y.tab.c"
    break;

  case 146:
#line 1207 "gwarf_yacc.y"
    {
        append_parameter_value((yyvsp[0].statement_value), (yyvsp[-1].parameter_list));
        (yyval.parameter_list) = (yyvsp[-1].parameter_list);
    }
#line 3407 "y.tab.c"
    break;

  case 147:
#line 1215 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3415 "y.tab.c"
    break;

  case 152:
#line 1229 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.return_code.value = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3424 "y.tab.c"
    break;

  case 153:
#line 1234 "gwarf_yacc.y"
    {
        (yyvsp[-2].statement_value)->code.return_code.value = (yyvsp[-1].statement_value);
        (yyvsp[-2].statement_value)->code.return_code.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-2].statement_value);
    }
#line 3434 "y.tab.c"
    break;

  case 154:
#line 1243 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = return_code;
        code_tmp->code.return_code.times = NULL;
        code_tmp->code.return_code.value = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3446 "y.tab.c"
    break;

  case 156:
#line 1255 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.restarted.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3455 "y.tab.c"
    break;

  case 157:
#line 1263 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = restarted;
        code_tmp->code.restarted.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3466 "y.tab.c"
    break;

  case 159:
#line 1274 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.restart.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3475 "y.tab.c"
    break;

  case 160:
#line 1282 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = restart;
        code_tmp->code.restart.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3486 "y.tab.c"
    break;

  case 162:
#line 1293 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.continued.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3495 "y.tab.c"
    break;

  case 163:
#line 1301 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = continued;
        code_tmp->code.continued.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3506 "y.tab.c"
    break;

  case 165:
#line 1312 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.continue_cycle.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3515 "y.tab.c"
    break;

  case 166:
#line 1320 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = continue_cycle;
        code_tmp->code.continue_cycle.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3526 "y.tab.c"
    break;

  case 168:
#line 1331 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.break_cycle.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3535 "y.tab.c"
    break;

  case 169:
#line 1339 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = break_cycle;
        code_tmp->code.break_cycle.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3546 "y.tab.c"
    break;

  case 171:
#line 1350 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.broken.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 3555 "y.tab.c"
    break;

  case 172:
#line 1357 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = broken;
        code_tmp->code.broken.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 3566 "y.tab.c"
    break;


#line 3570 "y.tab.c"

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
#line 1372 "gwarf_yacc.y"

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
