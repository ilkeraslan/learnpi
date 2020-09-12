/* A Bison parser, made by GNU Bison 3.5.1.  */

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
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "learnpi.h"
#include "functions.h"

#define YYDEBUG 1

int yylex();   

#line 81 "parser.tab.c"

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
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    TYPE = 258,
    COMPLEX_TYPE = 259,
    INTEGER = 260,
    NAME = 261,
    VALUE = 262,
    BUILT_IN_FUNCTION = 263,
    IF = 264,
    ELSE = 265,
    EOL = 266,
    WHILE = 267,
    FOR = 268,
    FUN = 269,
    OR_OPERATION = 270,
    AND_OPERATION = 271,
    NOT_OPERATION = 272,
    CMP = 273,
    UMINUS = 274
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 12 "parser.y"

  struct ast *ast;
  struct symbol_list *symbol_list;
  struct val *value;
  int integer;
  int function_id;
  char *str;
  int type;

#line 163 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   344

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  197

#define YYUNDEFTOK  2
#define YYMAXUTOK   274


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
      26,    27,    22,    20,    31,    21,     2,    23,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    30,
       2,    19,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    28,    24,    29,     2,     2,     2,     2,
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
      15,    16,    17,    18,    25
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    44,    44,    45,    51,    52,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   108,   109,   118,   119,   122,
     123
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "COMPLEX_TYPE", "INTEGER",
  "NAME", "VALUE", "BUILT_IN_FUNCTION", "IF", "ELSE", "EOL", "WHILE",
  "FOR", "FUN", "OR_OPERATION", "AND_OPERATION", "NOT_OPERATION", "CMP",
  "'='", "'+'", "'-'", "'*'", "'/'", "'|'", "UMINUS", "'('", "')'", "'{'",
  "'}'", "';'", "','", "$accept", "learnpi", "statement", "exp", "list",
  "explist", "sym_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,    61,
      43,    45,    42,    47,   124,   274,    40,    41,   123,   125,
      59,    44
};
# endif

#define YYPACT_NINF (-87)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -87,    35,   -87,   -10,     0,     4,   -15,   -87,    20,    28,
      34,    37,    24,     7,     7,     7,   -87,   283,   -87,     6,
      92,     7,    45,   179,   183,   204,     7,    39,   -87,   -87,
     292,   -87,     7,     7,     7,     7,     7,     7,     7,   -87,
       7,   -87,     7,   321,   -87,   247,    -1,   -87,    40,     7,
     211,     7,   302,   259,    64,   -87,   118,   118,   198,    54,
      54,   -87,   -87,    -9,    81,     7,   -87,   -87,   224,    75,
      85,   237,    87,     7,    91,    93,   -87,   -87,   -87,   -87,
      97,    99,   104,   122,   109,   114,   147,   270,    64,   125,
     119,   105,   138,   171,   171,   123,   129,   150,   171,   133,
       7,   -87,   171,   152,   171,   171,    -6,   -87,   -87,   153,
     171,    -2,   -87,   312,   -87,   171,    21,    26,   136,    69,
     171,   155,   140,   -87,   139,    29,   141,    79,   159,   165,
     -87,   154,   186,   170,   164,   -87,   187,   172,   189,   -87,
     174,   207,   -87,   213,   197,   196,   208,   -87,   171,   226,
     215,   230,   221,   222,   171,   243,   -87,   227,   233,   255,
     171,   260,   261,    46,   171,   -87,   262,   171,    53,   171,
     171,   254,   -87,    62,   171,    88,   258,   -87,    89,    90,
     -87,   266,   -87,   265,   267,   -87,   -87,   268,   -87,   273,
     -87,   -87,   280,   -87,   -87,   -87,   -87
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,    49,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     0,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    47,    43,
       0,    37,     0,     0,     0,     0,     0,     0,     0,    34,
       0,    36,     0,    50,    54,    57,     0,    52,     0,     0,
       0,     0,     0,     0,     0,    46,    45,    44,    38,    39,
      40,    41,    42,     0,     0,     0,    53,    51,     0,     0,
       0,     0,     0,     0,    59,     0,    33,    32,    35,    58,
       0,     0,     0,    55,     0,     0,    55,     0,     0,     0,
       0,     0,     0,    55,    55,     0,     0,     0,    55,     0,
       0,    60,    55,     0,    55,    55,     0,    56,    25,     0,
      55,     0,    30,     0,     4,    55,     0,     0,     0,    24,
      55,     0,     0,    29,     0,     0,     0,    14,     0,    18,
      19,     0,     0,     0,     0,    28,     0,     0,     0,    13,
       0,     0,    17,     0,     0,     0,     0,    27,    55,     0,
       0,     0,     0,     0,    55,     0,    26,     0,     0,     0,
      55,     0,     0,     0,    55,    31,     0,    55,     0,    55,
      55,     0,    23,     0,    55,     0,     0,    12,     0,     0,
      22,     0,    21,     0,     0,     8,    11,     0,    10,     0,
      16,    20,     0,     7,     9,    15,     6
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -87,   -87,   310,    72,   -86,   -20,   228
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    94,    17,    95,    46,    75
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      99,    18,    76,    48,    21,   118,    19,   106,   107,   122,
      20,    22,   111,     6,     7,     8,   114,    39,   116,   117,
      63,    77,    64,   119,   121,    40,    66,   123,    13,   125,
      27,    14,   126,    15,   133,     2,     3,   128,     4,     5,
     137,     6,     7,     8,     9,    79,    23,    10,    11,    12,
     127,     6,     7,     8,    24,   129,    13,   171,   138,    14,
      25,    15,   157,    26,   176,    54,    13,    67,   163,    14,
      74,    15,    44,   181,   168,   172,    37,    38,   173,   131,
     132,   175,   177,   178,   179,    28,    29,    30,   183,   140,
     141,   182,    78,    43,    45,    45,    50,    52,    53,   184,
     187,   189,    82,    41,    56,    57,    58,    59,    60,    61,
      62,    42,    45,    83,    45,    86,   104,   185,   188,   190,
      89,    68,    88,    71,    90,     4,     5,    91,     6,     7,
       8,     9,    92,    93,    10,    11,    96,    45,    35,    36,
      37,    38,    97,    13,   102,    87,    14,   103,    15,   105,
       4,     5,   108,     6,     7,     8,     9,   109,    98,    10,
      11,   110,   112,   115,   120,   130,   134,   136,    13,   135,
     139,    14,   113,    15,     4,     5,   143,     6,     7,     8,
       9,   146,   144,    10,    11,     6,     7,     8,   142,     6,
       7,     8,    13,   147,    49,    14,   145,    15,   148,   150,
      13,   149,   151,    14,    13,    15,    47,    14,   154,    15,
       6,     7,     8,    32,    33,    51,    -1,   152,    35,    36,
      37,    38,    69,   153,   155,    13,    32,    33,    14,    34,
      15,    35,    36,    37,    38,    80,   158,   156,    70,    32,
      33,   160,    34,   159,    35,    36,    37,    38,    84,   161,
     162,    81,    32,    33,   164,    34,   165,    35,    36,    37,
      38,   166,    32,    33,    85,    34,   167,    35,    36,    37,
      38,   169,   170,   174,    32,    33,   192,    34,    65,    35,
      36,    37,    38,   180,     0,    32,    33,   186,    34,    73,
      35,    36,    37,    38,    31,   191,   193,   194,    32,    33,
     100,    34,   195,    35,    36,    37,    38,    32,    33,   196,
      34,    16,    35,    36,    37,    38,   101,    32,    33,    55,
      34,     0,    35,    36,    37,    38,     0,    32,    33,    72,
      34,     0,    35,    36,    37,    38,    32,    33,     0,   124,
       0,    35,    36,    37,    38
};

static const yytype_int16 yycheck[] =
{
      86,    11,    11,    23,    19,    11,     6,    93,    94,    11,
       6,    26,    98,     6,     7,     8,   102,    11,   104,   105,
      40,    30,    42,    29,   110,    19,    27,    29,    21,   115,
       6,    24,    11,    26,   120,     0,     1,    11,     3,     4,
      11,     6,     7,     8,     9,    65,    26,    12,    13,    14,
      29,     6,     7,     8,    26,    29,    21,    11,    29,    24,
      26,    26,   148,    26,    11,    26,    21,    27,   154,    24,
       6,    26,    27,    11,   160,    29,    22,    23,   164,    10,
      11,   167,    29,   169,   170,    13,    14,    15,   174,    10,
      11,    29,    11,    21,    22,    23,    24,    25,    26,    11,
      11,    11,    27,    11,    32,    33,    34,    35,    36,    37,
      38,    19,    40,    28,    42,    28,    11,    29,    29,    29,
      27,    49,    31,    51,    27,     3,     4,    28,     6,     7,
       8,     9,    28,    11,    12,    13,    27,    65,    20,    21,
      22,    23,    28,    21,    19,    73,    24,    28,    26,    11,
       3,     4,    29,     6,     7,     8,     9,    28,    11,    12,
      13,    11,    29,    11,    11,    29,    11,    28,    21,    29,
      29,    24,   100,    26,     3,     4,    11,     6,     7,     8,
       9,    11,    28,    12,    13,     6,     7,     8,    29,     6,
       7,     8,    21,    29,    11,    24,    10,    26,    11,    10,
      21,    29,    28,    24,    21,    26,    27,    24,    11,    26,
       6,     7,     8,    15,    16,    11,    18,    10,    20,    21,
      22,    23,    11,    10,    28,    21,    15,    16,    24,    18,
      26,    20,    21,    22,    23,    11,    10,    29,    27,    15,
      16,    11,    18,    28,    20,    21,    22,    23,    11,    28,
      28,    27,    15,    16,    11,    18,    29,    20,    21,    22,
      23,    28,    15,    16,    27,    18,    11,    20,    21,    22,
      23,    11,    11,    11,    15,    16,    11,    18,    31,    20,
      21,    22,    23,    29,    -1,    15,    16,    29,    18,    30,
      20,    21,    22,    23,    11,    29,    29,    29,    15,    16,
      30,    18,    29,    20,    21,    22,    23,    15,    16,    29,
      18,     1,    20,    21,    22,    23,    88,    15,    16,    27,
      18,    -1,    20,    21,    22,    23,    -1,    15,    16,    27,
      18,    -1,    20,    21,    22,    23,    15,    16,    -1,    27,
      -1,    20,    21,    22,    23
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    33,     0,     1,     3,     4,     6,     7,     8,     9,
      12,    13,    14,    21,    24,    26,    34,    35,    11,     6,
       6,    19,    26,    26,    26,    26,    26,     6,    35,    35,
      35,    11,    15,    16,    18,    20,    21,    22,    23,    11,
      19,    11,    19,    35,    27,    35,    37,    27,    37,    11,
      35,    11,    35,    35,    26,    27,    35,    35,    35,    35,
      35,    35,    35,    37,    37,    31,    27,    27,    35,    11,
      27,    35,    27,    30,     6,    38,    11,    30,    11,    37,
      11,    27,    27,    28,    11,    27,    28,    35,    31,    27,
      27,    28,    28,    11,    34,    36,    27,    28,    11,    36,
      30,    38,    19,    28,    11,    11,    36,    36,    29,    28,
      11,    36,    29,    35,    36,    11,    36,    36,    11,    29,
      11,    36,    11,    29,    27,    36,    11,    29,    11,    29,
      29,    10,    11,    36,    11,    29,    28,    11,    29,    29,
      10,    11,    29,    11,    28,    10,    11,    29,    11,    29,
      10,    28,    10,    10,    11,    28,    29,    36,    10,    28,
      11,    28,    28,    36,    11,    29,    28,    11,    36,    11,
      11,    11,    29,    36,    11,    36,    11,    29,    36,    36,
      29,    11,    29,    36,    11,    29,    29,    11,    29,    11,
      29,    29,    11,    29,    29,    29,    29
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    33,    33,    33,    34,    34,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    34,    35,    35,
      35,    35,    35,    35,    35,    35,    35,    35,    35,    35,
      35,    35,    35,    35,    35,    36,    36,    37,    37,    38,
      38
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     8,     3,    17,    16,    15,    16,
      15,    15,    14,    10,     9,    16,    15,    10,     9,     9,
      15,    14,    14,    13,     8,     7,    11,    10,     9,     8,
       7,    12,     5,     5,     3,     5,     3,     2,     3,     3,
       3,     3,     3,     2,     3,     3,     3,     2,     1,     1,
       3,     4,     3,     4,     3,     0,     2,     1,     3,     1,
       3
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
#line 45 "parser.y"
                       {
      struct val *value = eval((yyvsp[0].ast));
      if(value) {
         treefree((yyvsp[0].ast));
      }
    }
#line 1482 "parser.tab.c"
    break;

  case 4:
#line 51 "parser.y"
                                                { dodef((yyvsp[-5].str), (yyvsp[-3].symbol_list), (yyvsp[0].ast)); }
#line 1488 "parser.tab.c"
    break;

  case 5:
#line 52 "parser.y"
                       { yyerrok; yyparse(); }
#line 1494 "parser.tab.c"
    break;

  case 6:
#line 55 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-13].ast), (yyvsp[-8].ast), (yyvsp[-2].ast)); }
#line 1500 "parser.tab.c"
    break;

  case 7:
#line 56 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-12].ast), (yyvsp[-7].ast), (yyvsp[-2].ast)); }
#line 1506 "parser.tab.c"
    break;

  case 8:
#line 57 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-11].ast), (yyvsp[-6].ast), (yyvsp[-1].ast)); }
#line 1512 "parser.tab.c"
    break;

  case 9:
#line 58 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-12].ast), (yyvsp[-8].ast), (yyvsp[-2].ast)); }
#line 1518 "parser.tab.c"
    break;

  case 10:
#line 59 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-11].ast), (yyvsp[-7].ast), (yyvsp[-1].ast)); }
#line 1524 "parser.tab.c"
    break;

  case 11:
#line 60 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-11].ast), (yyvsp[-7].ast), (yyvsp[-2].ast)); }
#line 1530 "parser.tab.c"
    break;

  case 12:
#line 61 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-10].ast), (yyvsp[-6].ast), (yyvsp[-1].ast)); }
#line 1536 "parser.tab.c"
    break;

  case 13:
#line 62 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-6].ast), (yyvsp[-2].ast), NULL); }
#line 1542 "parser.tab.c"
    break;

  case 14:
#line 63 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-5].ast), (yyvsp[-1].ast), NULL); }
#line 1548 "parser.tab.c"
    break;

  case 15:
#line 64 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-13].ast), (yyvsp[-8].ast), (yyvsp[-2].ast)); }
#line 1554 "parser.tab.c"
    break;

  case 16:
#line 65 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-12].ast), (yyvsp[-7].ast), (yyvsp[-1].ast)); }
#line 1560 "parser.tab.c"
    break;

  case 17:
#line 66 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-7].ast), (yyvsp[-2].ast), NULL); }
#line 1566 "parser.tab.c"
    break;

  case 18:
#line 67 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-6].ast), (yyvsp[-1].ast), NULL); }
#line 1572 "parser.tab.c"
    break;

  case 19:
#line 68 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-6].ast), (yyvsp[-2].ast), NULL); }
#line 1578 "parser.tab.c"
    break;

  case 20:
#line 69 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-12].ast), (yyvsp[-8].ast), (yyvsp[-2].ast)); }
#line 1584 "parser.tab.c"
    break;

  case 21:
#line 70 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-11].ast), (yyvsp[-7].ast), (yyvsp[-1].ast)); }
#line 1590 "parser.tab.c"
    break;

  case 22:
#line 71 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-11].ast), (yyvsp[-7].ast), (yyvsp[-2].ast)); }
#line 1596 "parser.tab.c"
    break;

  case 23:
#line 72 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-10].ast), (yyvsp[-6].ast), (yyvsp[-1].ast)); }
#line 1602 "parser.tab.c"
    break;

  case 24:
#line 73 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-5].ast), (yyvsp[-1].ast), NULL); }
#line 1608 "parser.tab.c"
    break;

  case 25:
#line 74 "parser.y"
                                                                                  { (yyval.ast) = newflow(IF_STATEMENT, (yyvsp[-4].ast), (yyvsp[-1].ast), NULL); }
#line 1614 "parser.tab.c"
    break;

  case 26:
#line 75 "parser.y"
                                                                                  { (yyval.ast) = newflow(LOOP_STATEMENT, (yyvsp[-7].ast), (yyvsp[-2].ast), NULL); }
#line 1620 "parser.tab.c"
    break;

  case 27:
#line 76 "parser.y"
                                                                                  { (yyval.ast) = newflow(LOOP_STATEMENT, (yyvsp[-6].ast), (yyvsp[-2].ast), NULL); }
#line 1626 "parser.tab.c"
    break;

  case 28:
#line 77 "parser.y"
                                                                                  { (yyval.ast) = newflow(LOOP_STATEMENT, (yyvsp[-6].ast), (yyvsp[-2].ast), NULL); }
#line 1632 "parser.tab.c"
    break;

  case 29:
#line 78 "parser.y"
                                                                                  { (yyval.ast) = newflow(LOOP_STATEMENT, (yyvsp[-5].ast), (yyvsp[-1].ast), NULL); }
#line 1638 "parser.tab.c"
    break;

  case 30:
#line 79 "parser.y"
                                                                                  { (yyval.ast) = newflow(LOOP_STATEMENT, (yyvsp[-4].ast), (yyvsp[-1].ast), NULL); }
#line 1644 "parser.tab.c"
    break;

  case 31:
#line 80 "parser.y"
                                                                                  { (yyval.ast) = new_for_flow(FOR_STATEMENT, (yyvsp[-9].ast), (yyvsp[-7].ast), (yyvsp[-5].ast), (yyvsp[-1].ast)); }
#line 1650 "parser.tab.c"
    break;

  case 32:
#line 81 "parser.y"
                                                                                  { (yyval.ast) = new_assignment((yyvsp[-3].str), (yyvsp[-1].ast) ); }
#line 1656 "parser.tab.c"
    break;

  case 33:
#line 82 "parser.y"
                                                                                  { (yyval.ast) = new_assignment((yyvsp[-3].str), (yyvsp[-1].ast) ); }
#line 1662 "parser.tab.c"
    break;

  case 34:
#line 83 "parser.y"
                                                                                  { (yyval.ast) = new_declaration((yyvsp[-1].str), (yyvsp[-2].type)); }
#line 1668 "parser.tab.c"
    break;

  case 35:
#line 84 "parser.y"
                                                                                  { (yyval.ast) = new_complex_assignment((yyvsp[-3].str), (yyvsp[-4].type), (yyvsp[-1].ast));}
#line 1674 "parser.tab.c"
    break;

  case 36:
#line 85 "parser.y"
                                                                                  { (yyval.ast) = new_declaration((yyvsp[-1].str), (yyvsp[-2].type)); }
#line 1680 "parser.tab.c"
    break;

  case 38:
#line 89 "parser.y"
                                             { (yyval.ast) = new_comparison((yyvsp[-1].function_id), (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1686 "parser.tab.c"
    break;

  case 39:
#line 90 "parser.y"
                                             { (yyval.ast) = new_ast_with_children('+', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1692 "parser.tab.c"
    break;

  case 40:
#line 91 "parser.y"
                                             { (yyval.ast) = new_ast_with_children('-', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1698 "parser.tab.c"
    break;

  case 41:
#line 92 "parser.y"
                                             { (yyval.ast) = new_ast_with_children('*', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1704 "parser.tab.c"
    break;

  case 42:
#line 93 "parser.y"
                                             { (yyval.ast) = new_ast_with_children('/', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1710 "parser.tab.c"
    break;

  case 43:
#line 94 "parser.y"
                                             { (yyval.ast) = new_ast_with_child('|', (yyvsp[0].ast)); }
#line 1716 "parser.tab.c"
    break;

  case 44:
#line 95 "parser.y"
                                             { (yyval.ast) = new_ast_with_children(LOGICAL_AND, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1722 "parser.tab.c"
    break;

  case 45:
#line 96 "parser.y"
                                             { (yyval.ast) = new_ast_with_children(LOGICAL_OR, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1728 "parser.tab.c"
    break;

  case 46:
#line 97 "parser.y"
                                             { (yyval.ast) = (yyvsp[-1].ast); }
#line 1734 "parser.tab.c"
    break;

  case 47:
#line 98 "parser.y"
                                             { (yyval.ast) = new_ast_with_child(UNARY_MINUS, (yyvsp[0].ast)); }
#line 1740 "parser.tab.c"
    break;

  case 48:
#line 99 "parser.y"
                                             { (yyval.ast) = new_value((yyvsp[0].value)); }
#line 1746 "parser.tab.c"
    break;

  case 49:
#line 100 "parser.y"
                                             { (yyval.ast) = new_reference((yyvsp[0].str)); }
#line 1752 "parser.tab.c"
    break;

  case 50:
#line 101 "parser.y"
                                             { (yyval.ast) = new_assignment((yyvsp[-2].str), (yyvsp[0].ast)); }
#line 1758 "parser.tab.c"
    break;

  case 51:
#line 102 "parser.y"
                                             { (yyval.ast) = new_builtin_function((yyvsp[-3].function_id), NULL, (yyvsp[-1].ast)); }
#line 1764 "parser.tab.c"
    break;

  case 52:
#line 103 "parser.y"
                                             { (yyval.ast) = new_builtin_function((yyvsp[-2].function_id), NULL, NULL); }
#line 1770 "parser.tab.c"
    break;

  case 53:
#line 104 "parser.y"
                                             { (yyval.ast) = new_user_function((yyvsp[-3].str), (yyvsp[-1].ast)); }
#line 1776 "parser.tab.c"
    break;

  case 54:
#line 105 "parser.y"
                                             { (yyval.ast) = new_user_function((yyvsp[-2].str), NULL); }
#line 1782 "parser.tab.c"
    break;

  case 55:
#line 108 "parser.y"
                    { (yyval.ast) = NULL; }
#line 1788 "parser.tab.c"
    break;

  case 56:
#line 109 "parser.y"
                    {
                  if ((yyvsp[0].ast) == NULL) {
                        (yyval.ast) = (yyvsp[-1].ast);
                  } else {
                        (yyval.ast) = new_ast_with_children(STATEMENT_LIST, (yyvsp[-1].ast), (yyvsp[0].ast));
                  }
               }
#line 1800 "parser.tab.c"
    break;

  case 58:
#line 119 "parser.y"
                       { (yyval.ast) = new_ast_with_children(STATEMENT_LIST, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1806 "parser.tab.c"
    break;

  case 59:
#line 122 "parser.y"
                     { (yyval.symbol_list) = create_symbol_list((yyvsp[0].str), NULL); }
#line 1812 "parser.tab.c"
    break;

  case 60:
#line 123 "parser.y"
                       { (yyval.symbol_list) = create_symbol_list((yyvsp[-2].str), (yyvsp[0].symbol_list)); }
#line 1818 "parser.tab.c"
    break;


#line 1822 "parser.tab.c"

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
#line 126 "parser.y"
