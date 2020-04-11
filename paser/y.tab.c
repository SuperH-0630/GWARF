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
    #include"../gwarf_interpreter/interprete.h"
    #define yylex yylex_self
    extern int yylex (void);
    // 此处声明：定义的token：INDENTA不会在yacc中被使用，但将会在lex中被使用

#line 79 "y.tab.c"

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

#line 229 "y.tab.c"

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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  68
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   275

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  158

#define YYUNDEFTOK  2
#define YYMAXUTOK   300


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
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    25,    25,    29,    36,    43,    53,    57,    61,    65,
      69,    73,    77,    81,    85,    89,    95,   101,   105,   109,
     113,   117,   124,   128,   140,   141,   150,   159,   168,   177,
     186,   198,   199,   208,   220,   221,   230,   242,   243,   244,
     251,   259,   270,   284,   298,   313,   314,   322,   335,   340,
     349,   355,   364,   375,   382,   393,   400,   411,   422,   433,
     444,   455,   466,   477,   491,   498,   510,   514,   515,   523,
     533,   534,   542,   552,   553,   561,   571,   572,   580,   590,
     591,   599,   609,   610,   617,   627,   628,   629,   630
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "INT", "STRING", "VAR", "ADD",
  "SUB", "DIV", "MUL", "EQ", "LESS", "MORE", "RB", "LB", "RP", "LP",
  "WHILE", "POW", "EQUAL", "MOREEQ", "LESSEQ", "NOTEQ", "BREAK", "IF",
  "ELSE", "ELIF", "BROKEN", "CONTINUE", "CONTINUED", "RESTART",
  "RESTARTED", "REGO", "REWENT", "RI", "LI", "DEFAULT", "FOR", "COMMA",
  "GLOBAL", "NONLOCAL", "INDENTA", "STOPN", "STOPF", "BLOCK", "$accept",
  "command_block", "command_list", "command", "top_exp", "third_number",
  "second_number", "first_number", "element", "base_number",
  "nonlocal_token", "global_token", "default_token", "base_var_",
  "base_var_token", "if_block", "elif_exp", "if_exp", "block_block",
  "block_exp", "for_block", "for_exp", "while_block", "while_exp", "block",
  "restarted_exp", "restarted_token", "restart_exp", "restart_token",
  "continued_exp", "continued_token", "continue_exp", "continue_token",
  "break_exp", "break_token", "broken_exp", "broken_token", "stop_token", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300
};
# endif

#define YYPACT_NINF (-30)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     182,   -30,   -30,   -30,   119,    -5,   -30,     1,   -30,   -30,
     -30,   -30,   -30,   -25,   -25,   119,     6,    10,     6,     6,
     -30,    27,   182,   -30,   -25,    54,    13,    14,   -30,   -30,
     -25,   -25,   -25,    19,   -30,   207,    15,   -25,    15,   -25,
      15,   -25,    15,   -25,   119,   -25,   119,   -25,   119,   -25,
     119,   -25,   119,   -25,   119,    22,   119,   119,   -30,   -30,
     -10,   -10,     3,   -30,   119,    11,   -30,   -30,   -30,   -30,
     -25,   -10,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   -10,   -10,   -10,   119,   -30,    29,    15,   -10,
     182,   -30,   -10,   -30,   -10,   -30,   -10,   -30,   -10,   -30,
     -10,   -30,   -10,   -30,   -10,   -30,   -10,   -30,   -10,   -30,
     -30,    28,    32,   -30,   -30,     6,   -30,    25,    24,    13,
      13,    13,    13,    13,    13,    14,    14,   -30,   -30,   -30,
     119,   -30,   142,   -30,   -30,   -30,   188,    34,    45,    38,
     -30,   -30,    44,   222,   226,    39,   -30,   -30,   -30,    65,
     -30,    69,   239,   -30,   -30,   -30,    75,   -30
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    40,    41,    47,     0,     0,    81,     0,    84,    78,
      75,    72,    69,     0,     0,     0,     0,     0,     0,     0,
      54,     0,     2,     3,     0,    22,    24,    31,    34,    37,
       0,     0,     0,    38,    45,     0,     0,     0,     0,     0,
       0,     5,     0,     0,    67,     0,    70,     0,    73,     0,
      76,     0,    79,     0,    82,     0,     0,     0,    85,    86,
      15,    16,     0,    38,     0,     0,    43,    42,     1,     4,
       0,     6,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    20,    18,    17,     0,    51,     0,     0,     8,
       0,    48,    21,    53,    19,    55,     7,    64,    14,    68,
      13,    71,    12,    74,    11,    77,     9,    80,    10,    83,
      39,     0,     0,    88,    87,     0,    44,     0,     0,    27,
      26,    25,    28,    29,    30,    32,    33,    36,    35,    23,
       0,    49,     0,    65,    52,    46,     0,     0,     0,     0,
      66,    56,     0,     0,     0,     0,    50,    59,    58,     0,
      57,     0,     0,    62,    60,    61,     0,    63
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -30,   -30,   -22,   -20,    -3,   -30,   191,    18,    -9,   -30,
     -30,   -30,   -30,     0,   -11,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,   -19,   -30,   -29,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,   -30,   -30,   -30,   -30,   -30,    56
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    63,    34,    35,    88,    36,    37,    38,
      39,    40,    41,    42,    91,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    96
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      33,    55,    69,    70,    33,    64,    62,    66,    67,    93,
      56,    95,     3,    97,     1,     2,    57,     3,    58,    59,
      78,    79,    33,    80,    81,    65,     4,    68,     1,     2,
      85,     3,    90,   113,   114,    99,   110,   101,   115,   103,
       4,   105,   133,   107,   130,   109,   134,    15,     1,     2,
     117,     3,   146,   111,   112,   116,    33,    33,   147,   131,
       4,    15,   118,   138,   136,    33,    72,    73,   132,    60,
      61,   127,   128,   143,    74,    75,    76,    77,   152,   153,
      71,    15,   129,   154,   144,    33,    82,    83,    84,   157,
      33,    89,     0,    92,     0,    94,   125,   126,     0,    98,
       0,   100,     0,   102,   135,   104,     0,   106,     0,   108,
       0,     0,    69,    70,   137,     0,     0,    33,     0,     0,
       0,     0,     1,     2,     0,     3,     0,   139,     0,     0,
      33,     0,    33,   142,     4,   145,    33,     0,    33,     0,
     149,   151,     0,    33,    33,     1,     2,     0,     3,   156,
       0,     0,    33,     0,     0,    15,     0,     4,   140,     0,
       5,     0,     0,     0,     0,     0,     6,     7,     0,     0,
       8,     9,    10,    11,    12,    13,    14,     0,    15,    16,
      17,     0,    18,    19,     0,     1,     2,    20,     3,     0,
       0,     1,     2,     0,     3,     0,     0,     4,     0,     0,
       5,     0,   141,     4,     0,     0,     6,     7,     0,     0,
       8,     9,    10,    11,    12,    13,    14,     0,    15,    16,
      17,     0,    18,    19,    15,     1,     2,    20,     3,     1,
       2,     0,     3,    86,    87,     0,   148,     4,     0,     0,
     150,     4,     1,     2,     0,     3,     0,     0,     0,     0,
      58,    59,     0,   155,     4,     0,     0,     0,    15,     0,
       0,     0,    15,   119,   120,   121,   122,   123,   124,     0,
       0,     0,     0,     0,     0,    15
};

static const yytype_int16 yycheck[] =
{
       0,     4,    22,    22,     4,    16,    15,    18,    19,    38,
      15,    40,     6,    42,     3,     4,    15,     6,    43,    44,
       7,     8,    22,     9,    10,    15,    15,     0,     3,     4,
      11,     6,    17,    43,    44,    44,    14,    46,    35,    48,
      15,    50,    14,    52,    15,    54,    14,    36,     3,     4,
      39,     6,    14,    56,    57,    64,    56,    57,    14,    88,
      15,    36,    65,    39,    39,    65,    12,    13,    90,    13,
      14,    80,    81,    39,    20,    21,    22,    23,    39,    14,
      24,    36,    85,    14,    39,    85,    30,    31,    32,    14,
      90,    35,    -1,    37,    -1,    39,    78,    79,    -1,    43,
      -1,    45,    -1,    47,   115,    49,    -1,    51,    -1,    53,
      -1,    -1,   132,   132,   117,    -1,    -1,   117,    -1,    -1,
      -1,    -1,     3,     4,    -1,     6,    -1,   130,    -1,    -1,
     130,    -1,   132,   136,    15,   138,   136,    -1,   138,    -1,
     143,   144,    -1,   143,   144,     3,     4,    -1,     6,   152,
      -1,    -1,   152,    -1,    -1,    36,    -1,    15,    16,    -1,
      18,    -1,    -1,    -1,    -1,    -1,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    -1,    36,    37,
      38,    -1,    40,    41,    -1,     3,     4,    45,     6,    -1,
      -1,     3,     4,    -1,     6,    -1,    -1,    15,    -1,    -1,
      18,    -1,    14,    15,    -1,    -1,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    -1,    36,    37,
      38,    -1,    40,    41,    36,     3,     4,    45,     6,     3,
       4,    -1,     6,    26,    27,    -1,    14,    15,    -1,    -1,
      14,    15,     3,     4,    -1,     6,    -1,    -1,    -1,    -1,
      43,    44,    -1,    14,    15,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    36,    72,    73,    74,    75,    76,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     6,    15,    18,    24,    25,    28,    29,
      30,    31,    32,    33,    34,    36,    37,    38,    40,    41,
      45,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    63,    64,    65,    66,
      67,    68,    69,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    50,    15,    15,    43,    44,
      83,    83,    54,    59,    60,    15,    60,    60,     0,    49,
      68,    83,    12,    13,    20,    21,    22,    23,     7,     8,
       9,    10,    83,    83,    83,    11,    26,    27,    62,    83,
      17,    70,    83,    70,    83,    70,    83,    70,    83,    54,
      83,    54,    83,    54,    83,    54,    83,    54,    83,    54,
      14,    50,    50,    43,    44,    35,    54,    39,    50,    52,
      52,    52,    52,    52,    52,    53,    53,    54,    54,    50,
      15,    70,    48,    14,    14,    60,    39,    50,    39,    50,
      16,    14,    50,    39,    39,    50,    14,    14,    14,    50,
      14,    50,    39,    14,    14,    14,    50,    14
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    48,    48,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    50,    50,    51,    51,    51,    51,    51,    51,
      51,    52,    52,    52,    53,    53,    53,    54,    54,    54,
      55,    55,    56,    57,    58,    59,    59,    60,    61,    61,
      62,    62,    63,    64,    65,    66,    67,    67,    67,    67,
      67,    67,    67,    67,    68,    69,    70,    71,    71,    72,
      73,    73,    74,    75,    75,    76,    77,    77,    78,    79,
      79,    80,    81,    81,    82,    83,    83,    83,    83
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     1,     3,
       1,     1,     2,     2,     3,     1,     4,     1,     2,     3,
       4,     1,     4,     2,     1,     2,     5,     6,     6,     6,
       7,     7,     7,     8,     2,     4,     3,     1,     2,     1,
       1,     2,     1,     1,     2,     1,     1,     2,     1,     1,
       2,     1,     1,     2,     1,     1,     1,     2,     2
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
#line 30 "gwarf_yacc.y"
    {
        if((yyvsp[0].statement_value) != NULL){
            statement *tmp = find_statement_list(0, statement_base);
            append_statement(tmp, (yyvsp[0].statement_value));
        }
    }
#line 1546 "y.tab.c"
    break;

  case 4:
#line 37 "gwarf_yacc.y"
    {   
        if((yyvsp[0].statement_value) != NULL){
            statement *tmp = find_statement_list(0, statement_base);
            append_statement(tmp, (yyvsp[0].statement_value));
        }
    }
#line 1557 "y.tab.c"
    break;

  case 5:
#line 44 "gwarf_yacc.y"
    {   
        if((yyvsp[0].statement_value) != NULL){
            statement *tmp = find_statement_list(0, statement_base);
            append_statement(tmp, (yyvsp[0].statement_value));
        }
    }
#line 1568 "y.tab.c"
    break;

  case 6:
#line 54 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1576 "y.tab.c"
    break;

  case 7:
#line 58 "gwarf_yacc.y"
    {   
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1584 "y.tab.c"
    break;

  case 8:
#line 62 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1592 "y.tab.c"
    break;

  case 9:
#line 66 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1600 "y.tab.c"
    break;

  case 10:
#line 70 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1608 "y.tab.c"
    break;

  case 11:
#line 74 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1616 "y.tab.c"
    break;

  case 12:
#line 78 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1624 "y.tab.c"
    break;

  case 13:
#line 82 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1632 "y.tab.c"
    break;

  case 14:
#line 86 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1640 "y.tab.c"
    break;

  case 15:
#line 90 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = rego;
        (yyval.statement_value) = code_tmp;
    }
#line 1650 "y.tab.c"
    break;

  case 16:
#line 96 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = rewent;
        (yyval.statement_value) = code_tmp;
    }
#line 1660 "y.tab.c"
    break;

  case 17:
#line 102 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1668 "y.tab.c"
    break;

  case 18:
#line 106 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1676 "y.tab.c"
    break;

  case 19:
#line 110 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1684 "y.tab.c"
    break;

  case 20:
#line 114 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1692 "y.tab.c"
    break;

  case 21:
#line 118 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1700 "y.tab.c"
    break;

  case 22:
#line 125 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[0].statement_value);
    }
#line 1708 "y.tab.c"
    break;

  case 23:
#line 129 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ASSIGMENT_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 1721 "y.tab.c"
    break;

  case 25:
#line 142 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = EQUAL_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 1734 "y.tab.c"
    break;

  case 26:
#line 151 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MORE_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 1747 "y.tab.c"
    break;

  case 27:
#line 160 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LESS_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 1760 "y.tab.c"
    break;

  case 28:
#line 169 "gwarf_yacc.y"
        {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MOREEQ_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 1773 "y.tab.c"
    break;

  case 29:
#line 178 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LESSEQ_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 1786 "y.tab.c"
    break;

  case 30:
#line 187 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NOTEQ_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 1799 "y.tab.c"
    break;

  case 32:
#line 200 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ADD_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 1812 "y.tab.c"
    break;

  case 33:
#line 209 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = SUB_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 1825 "y.tab.c"
    break;

  case 35:
#line 222 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MUL_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 1838 "y.tab.c"
    break;

  case 36:
#line 231 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = DIV_func;
        code_tmp->code.operation.left_exp = (yyvsp[-2].statement_value);
        code_tmp->code.operation.right_exp = (yyvsp[0].statement_value);
        (yyval.statement_value) = code_tmp;
    }
#line 1851 "y.tab.c"
    break;

  case 39:
#line 245 "gwarf_yacc.y"
    {
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1859 "y.tab.c"
    break;

  case 40:
#line 252 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = base_value;
        code_tmp->code.base_value.value.type = NUMBER_value;
        code_tmp->code.base_value.value.value.double_value = (double)(yyvsp[0].double_value);
        (yyval.statement_value) = code_tmp;
    }
#line 1871 "y.tab.c"
    break;

  case 41:
#line 260 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = base_value;
        code_tmp->code.base_value.value.type = INT_value;
        code_tmp->code.base_value.value.value.int_value = (int)(yyvsp[0].double_value);
        (yyval.statement_value) = code_tmp;
    }
#line 1883 "y.tab.c"
    break;

  case 42:
#line 271 "gwarf_yacc.y"
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
#line 1898 "y.tab.c"
    break;

  case 43:
#line 285 "gwarf_yacc.y"
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
#line 1913 "y.tab.c"
    break;

  case 44:
#line 299 "gwarf_yacc.y"
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
#line 1929 "y.tab.c"
    break;

  case 46:
#line 315 "gwarf_yacc.y"
    {
        (yyvsp[0].statement_value)->code.base_var.from = (yyvsp[-2].statement_value);
        (yyval.statement_value) = (yyvsp[0].statement_value);
    }
#line 1938 "y.tab.c"
    break;

  case 47:
#line 323 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->code.base_var.var_name = malloc(sizeof((yyvsp[0].string_value)));
        char *name_tmp = code_tmp->code.base_var.var_name;
        code_tmp->type = base_var;
        code_tmp->code.base_var.from = NULL;
        strcpy(name_tmp, (yyvsp[0].string_value));
        (yyval.statement_value) = code_tmp;
    }
#line 1952 "y.tab.c"
    break;

  case 48:
#line 336 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 1961 "y.tab.c"
    break;

  case 49:
#line 341 "gwarf_yacc.y"
    {
        append_elif((yyvsp[-1].if_list_base), (yyvsp[-2].statement_value)->code.if_branch.done);
        (yyval.statement_value) = (yyvsp[-2].statement_value);
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 1971 "y.tab.c"
    break;

  case 50:
#line 350 "gwarf_yacc.y"
    {
        statement *done_tmp =  make_statement();
        (yyval.if_list_base) = make_if((yyvsp[-1].statement_value), done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
    }
#line 1981 "y.tab.c"
    break;

  case 51:
#line 356 "gwarf_yacc.y"
    {
        statement *done_tmp =  make_statement();
        (yyval.if_list_base) = make_if(NULL, done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
    }
#line 1991 "y.tab.c"
    break;

  case 52:
#line 365 "gwarf_yacc.y"
    {
        statement *if_tmp =  make_statement(), *done_tmp =  make_statement();
        if_tmp->type = if_branch;
        if_tmp->code.if_branch.done = make_if((yyvsp[-1].statement_value), done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = if_tmp;
    }
#line 2003 "y.tab.c"
    break;

  case 53:
#line 376 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 2011 "y.tab.c"
    break;

  case 54:
#line 383 "gwarf_yacc.y"
    {
        statement *block_tmp =  make_statement();
        block_tmp->type = code_block;
        block_tmp->code.code_block.done = make_statement();
        statement_base = append_statement_list(block_tmp->code.code_block.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = block_tmp;
    }
#line 2023 "y.tab.c"
    break;

  case 55:
#line 394 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 2031 "y.tab.c"
    break;

  case 56:
#line 401 "gwarf_yacc.y"
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
#line 2046 "y.tab.c"
    break;

  case 57:
#line 412 "gwarf_yacc.y"
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
#line 2061 "y.tab.c"
    break;

  case 58:
#line 423 "gwarf_yacc.y"
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
#line 2076 "y.tab.c"
    break;

  case 59:
#line 434 "gwarf_yacc.y"
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
#line 2091 "y.tab.c"
    break;

  case 60:
#line 445 "gwarf_yacc.y"
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
#line 2106 "y.tab.c"
    break;

  case 61:
#line 456 "gwarf_yacc.y"
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
#line 2121 "y.tab.c"
    break;

  case 62:
#line 467 "gwarf_yacc.y"
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
#line 2136 "y.tab.c"
    break;

  case 63:
#line 478 "gwarf_yacc.y"
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
#line 2151 "y.tab.c"
    break;

  case 64:
#line 492 "gwarf_yacc.y"
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
#line 2159 "y.tab.c"
    break;

  case 65:
#line 499 "gwarf_yacc.y"
    {
        statement *while_tmp =  make_statement();
        while_tmp->type = while_cycle;
        while_tmp->code.while_cycle.condition = (yyvsp[-1].statement_value);
        while_tmp->code.while_cycle.done = make_statement();
        statement_base = append_statement_list(while_tmp->code.while_cycle.done, statement_base);  // new statement_base (FILO)
        (yyval.statement_value) = while_tmp;
    }
#line 2172 "y.tab.c"
    break;

  case 68:
#line 516 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.restarted.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2181 "y.tab.c"
    break;

  case 69:
#line 524 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = restarted;
        code_tmp->code.restarted.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2192 "y.tab.c"
    break;

  case 71:
#line 535 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.restart.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2201 "y.tab.c"
    break;

  case 72:
#line 543 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = restart;
        code_tmp->code.restart.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2212 "y.tab.c"
    break;

  case 74:
#line 554 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.continued.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2221 "y.tab.c"
    break;

  case 75:
#line 562 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = continued;
        code_tmp->code.continued.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2232 "y.tab.c"
    break;

  case 77:
#line 573 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.continue_cycle.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2241 "y.tab.c"
    break;

  case 78:
#line 581 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = continue_cycle;
        code_tmp->code.continue_cycle.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2252 "y.tab.c"
    break;

  case 80:
#line 592 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.break_cycle.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2261 "y.tab.c"
    break;

  case 81:
#line 600 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = break_cycle;
        code_tmp->code.break_cycle.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2272 "y.tab.c"
    break;

  case 83:
#line 611 "gwarf_yacc.y"
    {
        (yyvsp[-1].statement_value)->code.broken.times = (yyvsp[0].statement_value);
        (yyval.statement_value) = (yyvsp[-1].statement_value);
    }
#line 2281 "y.tab.c"
    break;

  case 84:
#line 618 "gwarf_yacc.y"
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = broken;
        code_tmp->code.broken.times = NULL;
        (yyval.statement_value) = code_tmp;
    }
#line 2292 "y.tab.c"
    break;


#line 2296 "y.tab.c"

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
#line 633 "gwarf_yacc.y"

int yyerror(char const *str)
{
    fprintf(stderr, "parser error near [%s] ;\n", yytext, yytext);
    return 0;
}

int parser(char *file)
{
    yyin = fopen(file,"r");
    yyparse();
    return 0;
}
