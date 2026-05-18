/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "iec.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atributos.h"
#include "instset.h"
#include "algcode.h"
#include "symbols.h"
#include "ecc.h"
#include "listadin.h"
#include "errors.h"
#include "instcon.h"
#include "asmltab.h"



#define YYSTYPE ATRIBUTOS
#include "lex.yy.c"


int yyerror (const char *str)
{
	/*printf("[%s] - in %s\n", str, yytext);
	print_linha();*/
	printf(": %d: %s before '%s'\n",err_getLine(), str,yytext);
	//error_exit(0);
	exit(0);
}

int operationResultType(int t1, int t2){
    if(t1 == t2){
        return t1;
    }
    if(t1 == TY_REAL || t2 == TY_REAL){
        return TY_REAL;
    }
    if(t1 == TY_INT || t2 == TY_INT){
        return TY_INT;
    }
    return TY_BYTE;
}

int getTypeSize(int type){
    switch(type){
        case TY_INT:
            return 2;
        case TY_BYTE:
            return 1;
        case TY_REAL:
            return 4;
    }
    err_printFatalError("Invalid type.");
    return 0;
}

int expr_postfix = 0;
int in_evt = 0;
int intaux;
int setConEv = 0;
char straux[100];
char straux2[100];
char straux3[100];


typedef union _data {
  float f;
  char  b[4];
} myFloat;
myFloat float_temp;


#line 138 "iec.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "iec.tab.h".  */
#ifndef YY_YY_IEC_TAB_H_INCLUDED
# define YY_YY_IEC_TAB_H_INCLUDED
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
    T_FUNCTION_BLOCK = 258,
    T_END_FUNCTION_BLOCK = 259,
    T_SYSTEM = 260,
    T_END_SYSTEM = 261,
    T_DEVICE = 262,
    T_END_DEVICE = 263,
    T_CUSTOM = 264,
    T_ALGORITHM = 265,
    T_END_ALGORITHM = 266,
    T_IN = 267,
    T_END_FBS = 268,
    T_FBS = 269,
    T_EVENT_CONNECTIONS = 270,
    T_DATA_CONNECTIONS = 271,
    T_END_CONNECTIONS = 272,
    T_EVENT_INPUT = 273,
    T_EVENT_OUTPUT = 274,
    T_END_EVENT = 275,
    T_EC_STATES = 276,
    T_END_STATES = 277,
    T_EC_TRANSITIONS = 278,
    T_END_TRANSITIONS = 279,
    T_VAR = 280,
    T_VAR_INPUT = 281,
    T_VAR_OUTPUT = 282,
    T_END_VAR = 283,
    T_TWO_POINTS = 284,
    T_SEMICOLON = 285,
    T_ASSIGNMENT = 286,
    T_OP = 287,
    T_CP = 288,
    T_COMA = 289,
    T_POINT = 290,
    T_HASH = 291,
    T_ARROW = 292,
    T_OR = 293,
    T_AND = 294,
    T_NOT = 295,
    T_XOR = 296,
    T_GT = 297,
    T_LT = 298,
    T_EQ = 299,
    T_GE = 300,
    T_LE = 301,
    T_ADD = 302,
    T_SUB = 303,
    T_DIV = 304,
    T_MUL = 305,
    T_ID = 306,
    T_NUMBER = 307,
    T_NUMBER_REAL = 308,
    T_AT = 309,
    T_TO = 310,
    T_RESOURCE = 311,
    T_END_RESOURCE = 312,
    T_TASK = 313,
    T_ON = 314,
    T_WITH = 315,
    T_IF = 316,
    T_THEN = 317,
    T_END_IF = 318,
    T_ELSE = 319,
    T_ELSIF = 320,
    T_WHILE = 321,
    T_DO = 322,
    T_END_WHILE = 323,
    T_BI_ADD = 324,
    T_BI_MUL = 325,
    T_BI_SUB = 326,
    T_BI_DIV = 327,
    T_BI_MOD = 328,
    T_BI_GT = 329,
    T_BI_GE = 330,
    T_BI_EQ = 331,
    T_BI_LT = 332,
    T_BI_LE = 333,
    T_BI_NE = 334,
    T_BI_SET_REG = 335,
    T_BI_GET_REG = 336,
    T_BI_GET_REG_REAL = 337,
    T_ASM = 338,
    T_END_ASM = 339,
    T_NISND = 340,
    T_NIRCV = 341,
    T_STORE = 342,
    T_LOAD = 343,
    T_GOTO = 344,
    T_CONST = 345,
    T_IFEQ = 346
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_IEC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 281 "iec.tab.c" /* yacc.c:358  */

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   286

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  86
/* YYNRULES -- Number of rules.  */
#define YYNRULES  154
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  304

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   346

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    97,    97,    98,    99,   103,   104,   105,   118,   123,
     128,   133,   136,   139,   118,   156,   167,   156,   197,   198,
     204,   206,   211,   213,   217,   219,   222,   225,   230,   231,
     235,   235,   238,   240,   244,   245,   246,   250,   252,   254,
     273,   275,   272,   278,   280,   285,   284,   291,   293,   297,
     299,   303,   305,   309,   311,   315,   343,   344,   348,   354,
     355,   359,   359,   362,   362,   368,   369,   373,   373,   381,
     387,   388,   392,   393,   393,   403,   404,   407,   415,   415,
     421,   421,   427,   428,   431,   441,   443,   448,   448,   457,
     459,   460,   461,   462,   463,   467,   472,   474,   478,   481,
     484,   488,   497,   500,   501,   508,   516,   522,   523,   527,
     528,   529,   533,   534,   535,   539,   542,   546,   554,   586,
     585,   596,   597,   597,   607,   613,   607,   624,   640,   645,
     650,   663,   667,   680,   683,   695,   699,   714,   721,   736,
     749,   753,   768,   782,   787,   798,   805,   817,   818,   835,
     839,   840,   841,   842,   843
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_FUNCTION_BLOCK",
  "T_END_FUNCTION_BLOCK", "T_SYSTEM", "T_END_SYSTEM", "T_DEVICE",
  "T_END_DEVICE", "T_CUSTOM", "T_ALGORITHM", "T_END_ALGORITHM", "T_IN",
  "T_END_FBS", "T_FBS", "T_EVENT_CONNECTIONS", "T_DATA_CONNECTIONS",
  "T_END_CONNECTIONS", "T_EVENT_INPUT", "T_EVENT_OUTPUT", "T_END_EVENT",
  "T_EC_STATES", "T_END_STATES", "T_EC_TRANSITIONS", "T_END_TRANSITIONS",
  "T_VAR", "T_VAR_INPUT", "T_VAR_OUTPUT", "T_END_VAR", "T_TWO_POINTS",
  "T_SEMICOLON", "T_ASSIGNMENT", "T_OP", "T_CP", "T_COMA", "T_POINT",
  "T_HASH", "T_ARROW", "T_OR", "T_AND", "T_NOT", "T_XOR", "T_GT", "T_LT",
  "T_EQ", "T_GE", "T_LE", "T_ADD", "T_SUB", "T_DIV", "T_MUL", "T_ID",
  "T_NUMBER", "T_NUMBER_REAL", "T_AT", "T_TO", "T_RESOURCE",
  "T_END_RESOURCE", "T_TASK", "T_ON", "T_WITH", "T_IF", "T_THEN",
  "T_END_IF", "T_ELSE", "T_ELSIF", "T_WHILE", "T_DO", "T_END_WHILE",
  "T_BI_ADD", "T_BI_MUL", "T_BI_SUB", "T_BI_DIV", "T_BI_MOD", "T_BI_GT",
  "T_BI_GE", "T_BI_EQ", "T_BI_LT", "T_BI_LE", "T_BI_NE", "T_BI_SET_REG",
  "T_BI_GET_REG", "T_BI_GET_REG_REAL", "T_ASM", "T_END_ASM", "T_NISND",
  "T_NIRCV", "T_STORE", "T_LOAD", "T_GOTO", "T_CONST", "T_IFEQ", "$accept",
  "StFile", "Blocks", "CustomFunctionBlock", "$@1", "$@2", "$@3", "$@4",
  "$@5", "$@6", "FunctionBlock", "$@7", "$@8", "FbContinue",
  "EventInputListContainer", "EventOutputListContainer", "EventList",
  "Event", "EcStatesListContainer", "EcStatesList", "EcStates", "$@9",
  "EcActionsList", "EcActionsListComa", "EcAction", "EcTransListContainer",
  "$@10", "$@11", "EcTransList", "EcTrans", "$@12",
  "VarInputListContainer", "VarOutputListContainer", "VarListContainer",
  "VarList", "VarDecl", "VarDeclAssig", "System", "DeviceList", "Device",
  "$@13", "$@14", "ResourceList", "Resource", "$@15", "FbsListContainer",
  "FbsList", "FbsDeclaration", "$@16", "ConstAssigList", "ConstAssig",
  "EventConnListContainer", "$@17", "DataConnListContainer", "$@18",
  "ConnectionList", "Connection", "AlgorithmList", "Algorithm", "$@19",
  "StatementList", "AsmBlock", "AsmCode", "Instruction", "AsmIf",
  "AsmIdNumGoto", "AsmIdNum", "Call_stat", "While_stat", "If_stat", "$@20",
  "IFContinue", "$@21", "$@22", "$@23", "Assignment", "M", "Expr",
  "Logical_Expr", "Logical_Expr_p2", "Logical_Expr_p1", "Relational_Expr",
  "Arithmetic_Expr", "Arithmetic_Expr_p1", "Factor", "Relational_Operator", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346
};
# endif

#define YYPACT_NINF -226

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-226)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      62,   -35,   -27,    24,    52,    17,  -226,  -226,  -226,  -226,
      65,     4,  -226,  -226,  -226,    42,    28,    94,    65,  -226,
    -226,    91,    95,  -226,  -226,    42,    -9,  -226,   104,    77,
      91,  -226,  -226,   107,    -8,   105,   134,   126,   133,  -226,
    -226,  -226,   -12,  -226,  -226,   133,   128,   106,  -226,   136,
     135,  -226,  -226,  -226,   136,  -226,   117,    -6,  -226,   -13,
    -226,   144,   -14,   140,   120,   144,   106,   143,  -226,  -226,
    -226,   145,  -226,    -2,  -226,  -226,   122,   138,   142,  -226,
    -226,   123,   153,  -226,  -226,    -3,   132,   137,  -226,     8,
     174,  -226,   139,   -14,   141,  -226,   171,  -226,   154,   156,
    -226,   146,  -226,  -226,   158,   147,   187,   178,   184,   162,
     148,   166,   170,   -19,   172,    -5,  -226,  -226,  -226,   186,
     152,  -226,  -226,  -226,  -226,  -226,   -19,   -19,  -226,  -226,
    -226,   173,   175,   176,  -226,  -226,   168,   165,  -226,   109,
      47,    59,  -226,   159,  -226,  -226,   160,  -226,  -226,   197,
     171,  -226,   179,  -226,   -19,   -19,   -19,   183,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,   -19,   -19,   -19,   -19,   -19,
      48,   180,   -11,  -226,   160,   163,   178,     3,  -226,   182,
     185,   188,  -226,   -19,   -19,    47,    59,    59,  -226,  -226,
    -226,  -226,   169,  -226,  -226,   -10,   190,   186,  -226,   191,
     -19,   -19,  -226,  -226,   193,  -226,  -226,  -226,   -19,  -226,
    -226,   165,  -226,   177,   181,  -226,  -226,   167,   207,   -19,
     164,   189,    54,  -226,   192,   196,   -16,  -226,   194,  -226,
    -226,   195,   199,  -226,  -226,  -226,   201,  -226,  -226,  -226,
    -226,    51,    51,    60,   198,  -226,  -226,   149,  -226,   200,
     202,  -226,   204,     7,   205,  -226,  -226,    99,  -226,   203,
    -226,  -226,  -226,  -226,   206,  -226,  -226,  -226,  -226,    60,
     210,  -226,   208,  -226,  -226,    66,   211,  -226,  -226,  -226,
    -226,   212,  -226,   213,  -226,  -226,  -226,  -226,  -226,    40,
    -226,  -226,   -19,  -226,    53,   209,   227,   214,  -226,  -226,
    -226,  -226,    66,  -226
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     3,     7,     6,     4,    15,
       0,     0,     1,     5,     2,    20,     0,     0,    60,     8,
      24,    22,     0,    58,    59,    20,     0,    24,     0,     0,
      22,    21,    26,     0,     0,     0,     0,    61,    47,    25,
      23,    30,     0,    29,    40,    47,     0,     0,    53,    49,
      32,    27,    28,    43,    49,    63,     0,     0,    66,     0,
      53,    51,    36,     0,    41,    51,     0,     0,    62,    65,
      48,     0,    54,     0,    53,     9,     0,     0,    33,    35,
      31,     0,     0,    44,    16,     0,     0,     0,    50,     0,
       0,    38,    39,     0,     0,    42,    85,    64,     0,    56,
      52,     0,    37,    34,     0,     0,     0,     0,    18,     0,
       0,     0,     0,   134,     0,     0,    71,    17,    78,     0,
       0,    86,    67,    57,    55,    10,   134,     0,   148,   144,
     145,     0,     0,     0,   149,    45,   129,   131,   133,   135,
     137,   140,   143,     0,    69,    70,     0,    80,    19,     0,
       0,    89,     0,   147,   134,   134,   134,     0,   128,   128,
     150,   152,   154,   151,   153,     0,     0,     0,     0,     0,
       0,     0,     0,    83,     0,     0,     0,     0,   146,     0,
       0,     0,    46,   134,   134,   136,   138,   139,   142,   141,
      72,    73,     0,    79,    82,     0,     0,     0,    11,     0,
     134,   134,    96,    94,     0,    92,    91,    90,   134,   116,
     117,   130,   132,     0,     0,    81,    87,     0,     0,   134,
       0,     0,     0,    93,     0,     0,     0,    76,     0,    89,
      68,     0,     0,   119,    89,   103,     0,   107,    95,   102,
     104,     0,     0,     0,     0,   108,    97,     0,   115,     0,
       0,    75,     0,     0,     0,   127,    89,     0,   106,     0,
     112,   113,   100,    98,     0,   109,   110,   105,    99,     0,
       0,    74,     0,    88,    12,     0,     0,   114,   111,   101,
      77,     0,    89,     0,   122,   124,   120,   118,    84,     0,
     121,    89,   134,    13,     0,     0,     0,     0,   125,    14,
     123,    89,     0,   126
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
     228,  -226,  -226,  -226,   222,   218,   224,  -226,  -226,  -226,
     215,  -226,  -226,  -226,   161,  -226,  -226,  -226,  -226,  -226,
    -226,   216,   219,   217,    -4,  -226,  -226,   230,   231,  -226,
    -226,  -226,   220,   -38,  -226,    87,  -226,   150,  -226,  -226,
      27,    84,  -226,    67,  -226,    88,  -147,  -226,  -226,  -226,
    -225,  -226,  -226,  -226,  -226,    -1,    21,  -176,  -226,  -226,
    -226,   -36,  -226,  -226,  -226,  -226,   108,  -126,  -226,    86,
      90,  -226,   110,   -70,  -124,  -226
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    25,    90,   151,   218,   282,   296,
       7,    15,    96,   106,    21,    28,    26,    33,    36,    42,
      43,    50,    63,    78,    79,    45,    53,    82,    64,    83,
     157,    49,    61,    75,    59,    72,   111,     8,    17,    18,
      47,    66,    57,    58,   150,   107,   115,   116,   213,   226,
     227,   119,   146,   148,   174,   172,   173,   108,   121,   229,
     177,   203,   222,   246,   247,   267,   262,   134,   205,   206,
     256,   286,   291,   292,   301,   207,   183,   135,   136,   137,
     138,   139,   140,   141,   142,   165
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     152,   204,    68,   153,   253,    97,   193,   215,   144,   257,
      51,    31,    40,   126,   198,    70,     9,   250,   273,    69,
       1,   127,     2,    76,    10,   194,    88,    11,   179,   180,
     181,   275,   128,   129,   130,   225,   100,    77,    71,    41,
     171,   171,    32,    32,   188,   189,   114,    69,   194,    71,
      56,   293,    12,    56,   199,    19,    73,   289,   199,    71,
      20,   131,   132,   133,   200,     1,   294,     2,   200,   201,
      89,     3,    16,   201,   220,   221,   302,   204,   190,    22,
     191,   204,   224,   131,   132,   133,   202,   131,   132,   133,
     202,   199,   235,   232,   166,   167,   186,   187,   259,   204,
      23,   200,   260,   261,   199,   236,   201,   264,   168,   169,
      27,   265,   266,   204,   200,   237,   297,   199,   204,   201,
     131,   132,   133,   202,    29,    35,   204,   200,    37,   283,
     284,   285,   201,   131,   132,   133,   202,    39,   238,   239,
     240,   241,   242,   243,   244,   245,   131,   132,   133,   202,
     199,   160,   161,   162,   163,   164,    41,    44,    46,    48,
     200,    55,    56,    60,    62,   201,   295,   276,    67,    74,
      80,    81,    86,    91,    87,    92,    93,    95,    94,   131,
     132,   133,   202,    98,   101,   105,   109,   110,    99,   113,
     102,   117,   104,   118,   120,   122,   124,   112,   114,   125,
     123,   143,   147,   149,   159,   154,   158,   155,   156,   175,
     170,   171,   178,   182,   196,   192,   208,   231,   209,   216,
     214,   210,   219,   223,   230,   248,   233,   249,   225,   255,
     258,   299,   271,    13,   274,    14,   228,   176,   269,   272,
     280,   287,   288,   290,   300,   252,   254,    30,    38,    24,
     268,    34,   270,   251,   103,   277,   234,    52,   278,   281,
     197,    54,   195,   263,   217,   145,   303,   184,   279,   211,
       0,   298,     0,    65,   212,   185,     0,     0,     0,     0,
       0,     0,    84,     0,     0,     0,    85
};

static const yytype_int16 yycheck[] =
{
     126,   177,     8,   127,   229,     8,    17,    17,    13,   234,
      22,    20,    20,    32,    11,    28,    51,    33,    11,    57,
       3,    40,     5,    37,    51,   172,    28,     3,   154,   155,
     156,   256,    51,    52,    53,    51,    28,    51,    51,    51,
      51,    51,    51,    51,   168,   169,    51,    85,   195,    51,
      56,    11,     0,    56,    51,    51,    60,   282,    51,    51,
      18,    80,    81,    82,    61,     3,   291,     5,    61,    66,
      74,     9,     7,    66,   200,   201,   301,   253,    30,    51,
      32,   257,   208,    80,    81,    82,    83,    80,    81,    82,
      83,    51,    38,   219,    47,    48,   166,   167,    47,   275,
       6,    61,    51,    52,    51,    51,    66,    47,    49,    50,
      19,    51,    52,   289,    61,    61,    63,    51,   294,    66,
      80,    81,    82,    83,    29,    21,   302,    61,    51,    63,
      64,    65,    66,    80,    81,    82,    83,    30,    84,    85,
      86,    87,    88,    89,    90,    91,    80,    81,    82,    83,
      51,    42,    43,    44,    45,    46,    51,    23,    32,    26,
      61,    33,    56,    27,    29,    66,   292,    68,    51,    25,
      30,    51,    29,    51,    29,    37,    34,    24,    55,    80,
      81,    82,    83,    51,    10,    14,    32,    31,    51,    31,
      51,     4,    51,    15,    10,    33,    30,    51,    51,    29,
      52,    29,    16,    51,    39,    32,    38,    32,    32,    12,
      51,    51,    33,    30,    51,    35,    34,    10,    33,    29,
      51,    33,    31,    30,    57,    33,    62,    31,    51,    30,
      29,     4,    30,     5,    29,     5,    55,   150,    89,    35,
      30,    30,    30,    30,    30,    51,    51,    25,    30,    18,
      52,    27,    52,   226,    93,    52,    67,    42,    52,    51,
     176,    45,   174,   242,   197,   115,   302,   159,   269,   183,
      -1,    62,    -1,    54,   184,   165,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    66
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     9,    93,    94,    95,   102,   129,    51,
      51,     3,     0,   102,   129,   103,     7,   130,   131,    51,
      18,   106,    51,     6,   130,    96,   108,    19,   107,    29,
     106,    20,    51,   109,   108,    21,   110,    51,   107,    30,
      20,    51,   111,   112,    23,   117,    32,   132,    26,   123,
     113,    22,   112,   118,   123,    33,    56,   134,   135,   126,
      27,   124,    29,   114,   120,   124,   133,    51,     8,   135,
      28,    51,   127,   126,    25,   125,    37,    51,   115,   116,
      30,    51,   119,   121,   125,   134,    29,    29,    28,   126,
      97,    51,    37,    34,    55,    24,   104,     8,    51,    51,
      28,    10,    51,   116,    51,    14,   105,   137,   149,    32,
      31,   128,    51,    31,    51,   138,   139,     4,    15,   143,
      10,   150,    33,    52,    30,    29,    32,    40,    51,    52,
      53,    80,    81,    82,   159,   169,   170,   171,   172,   173,
     174,   175,   176,    29,    13,   139,   144,    16,   145,    51,
     136,    98,   169,   176,    32,    32,    32,   122,    38,    39,
      42,    43,    44,    45,    46,   177,    47,    48,    49,    50,
      51,    51,   147,   148,   146,    12,   137,   152,    33,   169,
     169,   169,    30,   168,   168,   174,   175,   175,   176,   176,
      30,    32,    35,    17,   148,   147,    51,   143,    11,    51,
      61,    66,    83,   153,   159,   160,   161,   167,    34,    33,
      33,   171,   172,   140,    51,    17,    29,   145,    99,    31,
     169,   169,   154,    30,   169,    51,   141,   142,    55,   151,
      57,    10,   169,    62,    67,    38,    51,    61,    84,    85,
      86,    87,    88,    89,    90,    91,   155,   156,    33,    31,
      33,   142,    51,   152,    51,    30,   162,   152,    29,    47,
      51,    52,   158,   158,    47,    51,    52,   157,    52,    89,
      52,    30,    35,    11,    29,   152,    68,    52,    52,   157,
      30,    51,   100,    63,    64,    65,   163,    30,    30,   152,
      30,   164,   165,    11,   152,   169,   101,    63,    62,     4,
      30,   166,   152,   163
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    93,    93,    94,    94,    94,    96,    97,
      98,    99,   100,   101,    95,   103,   104,   102,   105,   105,
     106,   106,   107,   107,   108,   108,   109,   110,   111,   111,
     113,   112,   114,   114,   115,   115,   115,   116,   116,   116,
     118,   119,   117,   120,   120,   122,   121,   123,   123,   124,
     124,   125,   125,   126,   126,   127,   128,   128,   129,   130,
     130,   132,   131,   133,   131,   134,   134,   136,   135,   137,
     138,   138,   139,   140,   139,   141,   141,   142,   144,   143,
     146,   145,   147,   147,   148,   149,   149,   151,   150,   152,
     152,   152,   152,   152,   152,   153,   154,   154,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   156,   156,   157,
     157,   157,   158,   158,   158,   159,   159,   159,   160,   162,
     161,   163,   164,   163,   165,   166,   163,   167,   168,   169,
     170,   170,   171,   171,   172,   172,   173,   173,   174,   174,
     174,   175,   175,   175,   176,   176,   176,   176,   176,   176,
     177,   177,   177,   177,   177
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     2,     1,     1,     0,     0,
       0,     0,     0,     0,    25,     0,     0,    13,     1,     3,
       0,     3,     0,     3,     0,     3,     1,     3,     2,     1,
       0,     4,     0,     2,     3,     1,     0,     3,     2,     2,
       0,     0,     5,     0,     2,     0,     7,     0,     3,     0,
       3,     0,     3,     0,     2,     5,     0,     2,     4,     2,
       1,     0,     7,     0,     9,     2,     1,     0,    11,     3,
       2,     1,     4,     0,     8,     2,     1,     4,     0,     4,
       0,     4,     2,     1,     8,     0,     2,     0,     8,     0,
       2,     2,     2,     3,     2,     3,     0,     2,     2,     2,
       2,     3,     1,     1,     1,     2,     2,     1,     1,     1,
       1,     2,     1,     1,     2,     6,     4,     4,     6,     0,
       6,     2,     0,     5,     0,     0,     7,     4,     0,     1,
       4,     1,     4,     1,     0,     1,     3,     1,     3,     3,
       1,     3,     3,     1,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1
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
        case 8:
#line 118 "iec.y" /* yacc.c:1646  */
    {alg_reset();}
#line 1603 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 123 "iec.y" /* yacc.c:1646  */
    {
			alg_gen(I_GOTO, 0); /* the main */
			alg_gen(I_GOTO, 2); /* the init */
			sy_generateMap((yyvsp[-6]).str);
		}
#line 1613 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 128 "iec.y" /* yacc.c:1646  */
    {/*if(strcmp($10.str, "ALG_INIT")!=0){printf("ALG_INIT expected (%s). \n", $11.str); exit(1);}*/
			alg_backpath(1,alg_newLabel());
			alg_gen(I_ALLOC, sy_getTotalSize());
			}
#line 1622 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 133 "iec.y" /* yacc.c:1646  */
    {
			alg_gen(I_RET,0);
			}
#line 1630 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 136 "iec.y" /* yacc.c:1646  */
    {/*if(strcmp($14.str, "ALG_RUN")!=0){printf("ALG_RUN expected.\n"); exit(1);}*/
			alg_backpath(0,alg_newLabel());}
#line 1637 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 139 "iec.y" /* yacc.c:1646  */
    {
			alg_gen(I_RET,0);
			}
#line 1645 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 142 "iec.y" /* yacc.c:1646  */
    {
        //alg_backpath(0,ecc_generate());
        //alg_backpath(1, sy_generateInit());
        /*alg_selfPrint();*/

        sprintf(straux, "%s.asm", (yyvsp[-22]).str);
        alg_createAsmFile(straux);
        sprintf(straux, "%s.hex", (yyvsp[-22]).str);
        alg_createHexFile(straux);

        }
#line 1661 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 156 "iec.y" /* yacc.c:1646  */
    {sy_init(); ecc_init();alg_reset();
        sy_add("__alg", TY_BYTE, 0,0);
        sy_add("__est", TY_BYTE, 0,0);
	}
#line 1670 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 167 "iec.y" /* yacc.c:1646  */
    {
         alg_gen(I_GOTO, 0); /* the main */
         alg_gen(I_GOTO, 0); /* the init */

            dev_addfb((yyvsp[-8]).str);
        sy_generateMap((yyvsp[-8]).str);
         sy_copyToDevice((yyvsp[-8]).str);
        /* sy_print();*/
         }
#line 1684 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 180 "iec.y" /* yacc.c:1646  */
    {
        alg_backpath(0,ecc_generate());
        alg_backpath(1, sy_generateInit());
        /*alg_selfPrint();*/

        sprintf(straux, "%s.asm", (yyvsp[-11]).str);
        alg_createAsmFile(straux);
        sprintf(straux, "%s.hex", (yyvsp[-11]).str);
        alg_createHexFile(straux);
		sprintf(straux, "%s.ecc", (yyvsp[-11]).str);
		ecc_genMap(straux);
        }
#line 1701 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 219 "iec.y" /* yacc.c:1646  */
    {}
#line 1707 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 222 "iec.y" /* yacc.c:1646  */
    {sy_add((yyvsp[0]).str, TY_BYTE, 0, 1);}
#line 1713 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 235 "iec.y" /* yacc.c:1646  */
    {ecc_addState((yyvsp[0]).str);}
#line 1719 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 251 "iec.y" /* yacc.c:1646  */
    {ecc_addAlg2State("-", (yyvsp[-2]).str, (yyvsp[0]).str);}
#line 1725 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 253 "iec.y" /* yacc.c:1646  */
    {ecc_addAlg2State("-", NULL, (yyvsp[0]).str);}
#line 1731 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 255 "iec.y" /* yacc.c:1646  */
    {ecc_addAlg2State("-", (yyvsp[-1]).str,NULL);}
#line 1737 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 273 "iec.y" /* yacc.c:1646  */
    {expr_postfix = 1; in_evt = 1;}
#line 1743 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 275 "iec.y" /* yacc.c:1646  */
    {expr_postfix = 0; in_evt = 0;}
#line 1749 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 285 "iec.y" /* yacc.c:1646  */
    {
            ecc_addTrans((yyvsp[-4]).str, (yyvsp[-2]).str);
		}
#line 1757 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 315 "iec.y" /* yacc.c:1646  */
    {

        if(strcmp((yyvsp[-2]).str, "INT")==0){
            intaux = TY_INT;
        }else
        if(strcmp((yyvsp[-2]).str, "REAL")==0){
            intaux = TY_REAL;
        }else
        if(strcmp((yyvsp[-2]).str, "BYTE")==0){
            intaux = TY_BYTE;
        }else
        if(strcmp((yyvsp[-2]).str, "BOOL")==0){
            intaux = TY_BOOL;
        }else{
            printf("Undefined type '%s'.\n", (yyvsp[-2]).str);
        }

        if((yyvsp[-1]).isInit){
            if(intaux != TY_BYTE){
                err_printFatalError("Can not initialize not BYTE var. Not implemented yet.");
            }
            sy_addi((yyvsp[-4]).str, intaux, 0,0,1,(yyvsp[-1]).intval,NULL );
        }else{
            sy_add((yyvsp[-4]).str, intaux, 0,0 );
        }
	}
#line 1788 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 343 "iec.y" /* yacc.c:1646  */
    {(yyval).isInit = 0;}
#line 1794 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 344 "iec.y" /* yacc.c:1646  */
    {(yyval).intval = (yyvsp[0]).intval; (yyval).floatval = (yyvsp[0]).floatval; (yyval).isInit = 1;}
#line 1800 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 359 "iec.y" /* yacc.c:1646  */
    {sprintf(straux3,"%s", (yyvsp[-2]).str);}
#line 1806 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 362 "iec.y" /* yacc.c:1646  */
    {sprintf(straux3,"%s", (yyvsp[-4]).str);}
#line 1812 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 373 "iec.y" /* yacc.c:1646  */
    {sprintf(straux2, "%s", (yyvsp[-4]).str); ic_openxml(straux3, straux2);}
#line 1818 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 377 "iec.y" /* yacc.c:1646  */
    {ic_closexml();}
#line 1824 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 392 "iec.y" /* yacc.c:1646  */
    { ic_newInstance((yyvsp[-3]).str, (yyvsp[-1]).str, NULL, straux3, straux2); /*printf("instance %s, %s\n", $1.str, $3.str);*/ }
#line 1830 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 393 "iec.y" /* yacc.c:1646  */
    {alg_reset(); sprintf(straux, "%s", (yyvsp[-1]).str);}
#line 1836 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 394 "iec.y" /* yacc.c:1646  */
    {
            sprintf(straux,"_init_%s_%s_%s",straux3,straux2,(yyvsp[-7]).str);
            alg_createAsmFile(straux);
            /*printf("instance %s, TYPE:%s, INIT:%s, RES:%s, DEV:%s\n", $1.str, $3.str, straux,straux2,straux3);*/
            ic_newInstance((yyvsp[-7]).str, (yyvsp[-5]).str, straux,  straux3, straux2);
            }
#line 1847 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 407 "iec.y" /* yacc.c:1646  */
    {
        alg_gen(I_CONST, (yyvsp[-1]).intval);
        alg_gen(I_STORE, dev_getVarPos((yyvsp[-3]).str, straux));

        }
#line 1857 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 415 "iec.y" /* yacc.c:1646  */
    {setConEv = 1;}
#line 1863 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 421 "iec.y" /* yacc.c:1646  */
    {setConEv = 0;}
#line 1869 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 432 "iec.y" /* yacc.c:1646  */
    {

       /* printf("connection %s.%s to %s.%s\n", $1.str, $3.str, $5.str, $7.str);*/
        ic_newConnection((yyvsp[-7]).str, (yyvsp[-5]).str, (yyvsp[-3]).str, (yyvsp[-1]).str, straux3, straux2);
        }
#line 1879 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 448 "iec.y" /* yacc.c:1646  */
    {sy_add((yyvsp[-3]).str, 0, 1,0);}
#line 1885 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 450 "iec.y" /* yacc.c:1646  */
    {
        alg_gen(I_RET,0);

       /* alg_reset();*/
        }
#line 1895 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 467 "iec.y" /* yacc.c:1646  */
    {
		asm_backpath();
	}
#line 1903 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 478 "iec.y" /* yacc.c:1646  */
    {
		alg_gen(I_LOAD, (yyvsp[0]).intval);
	  }
#line 1911 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 481 "iec.y" /* yacc.c:1646  */
    {
		alg_gen(I_CONST, (yyvsp[0]).intval);
	  }
#line 1919 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 484 "iec.y" /* yacc.c:1646  */
    {
		alg_gen(I_STORE, (yyvsp[0]).intval);
	  }
#line 1927 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 488 "iec.y" /* yacc.c:1646  */
    {
		/* asm_addLabelCall($3.str, alg_newLabel());
		alg_gen(I_IF, 0); */
		if((yyvsp[0]).intval != -1){
            alg_gen((yyvsp[-2]).intval, (yyvsp[0]).intval);
		}else{
            alg_gen((yyvsp[-2]).intval, 0);
		}
	  }
#line 1941 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 497 "iec.y" /* yacc.c:1646  */
    {
		alg_gen(I_NISND, 0);
	  }
#line 1949 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 500 "iec.y" /* yacc.c:1646  */
    {alg_gen(I_OR,0);}
#line 1955 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 501 "iec.y" /* yacc.c:1646  */
    {
		alg_gen(I_NIRCV, 0);
	  }
#line 1963 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 508 "iec.y" /* yacc.c:1646  */
    {

		if((yyvsp[0]).intval != -1){
            alg_gen(I_GOTO, (yyvsp[0]).intval);
		}else{
            alg_gen(I_GOTO, 0);
		}
	  }
#line 1976 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 516 "iec.y" /* yacc.c:1646  */
    {
		asm_addLabel((yyvsp[-1]).str, alg_newLabel());
	  }
#line 1984 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 522 "iec.y" /* yacc.c:1646  */
    {(yyval).intval = I_IF;}
#line 1990 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 523 "iec.y" /* yacc.c:1646  */
    {(yyval).intval = I_IFEQ;}
#line 1996 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 527 "iec.y" /* yacc.c:1646  */
    {asm_addLabelCall((yyvsp[0]).str, alg_newLabel()); (yyval).intval = -1;}
#line 2002 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 528 "iec.y" /* yacc.c:1646  */
    {(yyval).intval = (yyvsp[0]).intval;}
#line 2008 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 529 "iec.y" /* yacc.c:1646  */
    {(yyval).intval = alg_newLabel() + (yyvsp[0]).intval;}
#line 2014 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 533 "iec.y" /* yacc.c:1646  */
    {(yyval).intval = sy_getPos((yyvsp[0]).str);}
#line 2020 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 535 "iec.y" /* yacc.c:1646  */
    {(yyval).intval = alg_newLabel() + (yyvsp[0]).intval;}
#line 2026 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 539 "iec.y" /* yacc.c:1646  */
    {
		alg_gen(I_ARSTORE, 0);
	}
#line 2034 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 542 "iec.y" /* yacc.c:1646  */
    {
		alg_gen(I_ARLOAD, 0);
		(yyval).type = TY_BYTE;
	}
#line 2043 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 546 "iec.y" /* yacc.c:1646  */
    {
		alg_gen(I_ARLOAD, TY_REAL);
		(yyval).type = TY_REAL;
	}
#line 2052 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 586 "iec.y" /* yacc.c:1646  */
    {
        alg_gen(I_IF,alg_getNextPos()+2);
        pinsert(alg_getNextPos());
        alg_gen(I_GOTO, 0);
	 }
#line 2062 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 596 "iec.y" /* yacc.c:1646  */
    {alg_backpath(pget(),alg_getNextPos());}
#line 2068 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 597 "iec.y" /* yacc.c:1646  */
    {
            alg_backpath(pget(),alg_getNextPos()+1);
			pinsert(alg_getNextPos());
            alg_gen(I_GOTO, 0);



        }
#line 2081 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 606 "iec.y" /* yacc.c:1646  */
    {alg_backpath(pget(),alg_getNextPos());}
#line 2087 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 607 "iec.y" /* yacc.c:1646  */
    {
		/*pinsert(alg_getNextPos());*/

        alg_backpath(pget(),alg_getNextPos()+1);
        alg_gen(I_GOTO, 0);
	}
#line 2098 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 613 "iec.y" /* yacc.c:1646  */
    {
        alg_gen(I_IF,alg_getNextPos()+2);
        pinsert(alg_getNextPos());
        alg_gen(I_GOTO, 0);
	 }
#line 2108 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 624 "iec.y" /* yacc.c:1646  */
    {
        if(sy_getType((yyvsp[-3]).str)!=(yyvsp[-1]).type){
            //err_printWarm("Assignment of differents types.");
            alg_gen(I_CONV,(yyvsp[-1]).type <<8|sy_getType((yyvsp[-3]).str));
        }
            if(expr_postfix == 0){
                alg_gen(I_STORE, getTypeSize(sy_getType((yyvsp[-3]).str))<<8 | sy_getPos((yyvsp[-3]).str));
            }
        }
#line 2122 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 640 "iec.y" /* yacc.c:1646  */
    {(yyval).label = alg_newLabel();}
#line 2128 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 650 "iec.y" /* yacc.c:1646  */
    {

            alg_gen(I_OR,(yyvsp[-3]).type<<8 | (yyvsp[-1]).type);
            (yyval).type = TY_BYTE;




//			printf("%s %s %s---\n", $1.str, $4.str, "|");
			(yyval).str = malloc(sizeof(char)*(strlen((yyvsp[-3]).str)+strlen((yyvsp[0]).str)+2) );
			sprintf((yyval).str, "%s%s%s", (yyvsp[-3]).str, (yyvsp[0]).str, "|");

	  }
#line 2146 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 667 "iec.y" /* yacc.c:1646  */
    {

            alg_gen(I_AND,(yyvsp[-3]).type<<8 | (yyvsp[-1]).type);
            (yyval).type = TY_BYTE;

		//if(expr_postfix == 1){
			//printf($$.str, "%s %s %s\n", $1.str, $4.str, "&");
			(yyval).str = malloc(sizeof(char)*(strlen((yyvsp[-3]).str)+strlen((yyvsp[0]).str)+2) );
			sprintf((yyval).str, "%s%s%s", (yyvsp[-3]).str, (yyvsp[0]).str, "&");
		//}else{

		//}
	  }
#line 2164 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 699 "iec.y" /* yacc.c:1646  */
    {
        if(expr_postfix == 0){
		/*
            $$.listav = listd_create();
            listd_append($$.listav, alg_getNextPos());
            $$.listaf = listd_create();
            listd_append($$.listaf, alg_getNextPos()+1);
            alg_gen($2.intval, 0 );
            alg_gen(I_GOTO, 0);
			*/
			alg_gen((yyvsp[-1]).intval,(yyvsp[-2]).type<<4 | (yyvsp[0]).type);
			(yyval).type = TY_BYTE;
        }

	  }
#line 2184 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 714 "iec.y" /* yacc.c:1646  */
    {
        (yyval).listav = listd_create();
        (yyval).listaf = listd_create();
	}
#line 2193 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 721 "iec.y" /* yacc.c:1646  */
    {
        //if(expr_postfix == 0)
        //    alg_gen(I_ADD, $1.type<<4 | $3.type );
        (yyval).type = operationResultType((yyvsp[-2]).type,(yyvsp[0]).type);
        if((yyval).type != (yyvsp[-2]).type){
            alg_gen(I_ADD, (1<<15)| ((yyvsp[-2]).type<<12) | ((yyval).type<<8) | ((yyvsp[-2]).type<<4 | (yyvsp[0]).type) );
        }else{
            if((yyval).type != (yyvsp[0]).type){
                alg_gen(I_ADD, (1<<15)| ((yyvsp[-2]).type<<12) | ((yyval).type<<8) | ((yyvsp[-2]).type<<4 | (yyvsp[0]).type) );
            }else{
                alg_gen(I_ADD, ((yyvsp[-2]).type<<4 | (yyvsp[0]).type) );
            }
        }
        }
#line 2212 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 736 "iec.y" /* yacc.c:1646  */
    {/*if(expr_postfix == 0) alg_gen(I_SUB, $1.type<<4 | $3.type );  $$.type = operationResultType($1.type,$3.type);*/
        (yyval).type = operationResultType((yyvsp[-2]).type,(yyvsp[0]).type);
        if((yyval).type != (yyvsp[-2]).type){
            alg_gen(I_SUB, (1<<15)| ((yyvsp[-2]).type<<12) | ((yyval).type<<8) | ((yyvsp[-2]).type<<4 | (yyvsp[0]).type) );
        }else{
            if((yyval).type != (yyvsp[0]).type){
                alg_gen(I_SUB, (1<<15)| ((yyvsp[-2]).type<<12) | ((yyval).type<<8) | ((yyvsp[-2]).type<<4 | (yyvsp[0]).type) );
            }else{
                alg_gen(I_SUB, ((yyvsp[-2]).type<<4 | (yyvsp[0]).type) );
            }
        }

	}
#line 2230 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 753 "iec.y" /* yacc.c:1646  */
    { /*if(expr_postfix == 0) alg_gen(I_MUL, $1.type<<4 | $3.type ); $$.type = operationResultType($1.type,$3.type);  */

	    (yyval).type = operationResultType((yyvsp[-2]).type,(yyvsp[0]).type);
        if((yyval).type != (yyvsp[-2]).type){
            alg_gen(I_MUL, (1<<15)| ((yyvsp[-2]).type<<12) | ((yyval).type<<8) | ((yyvsp[-2]).type<<4 | (yyvsp[0]).type) );
        }else{
            if((yyval).type != (yyvsp[0]).type){
                alg_gen(I_MUL, (1<<15)| ((yyvsp[-2]).type<<12) | ((yyval).type<<8) | ((yyvsp[-2]).type<<4 | (yyvsp[0]).type) );
            }else{
                alg_gen(I_MUL, ((yyvsp[-2]).type<<4 | (yyvsp[0]).type)&0xFF );
            }
        }


	  }
#line 2250 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 768 "iec.y" /* yacc.c:1646  */
    { /*if(expr_postfix == 0) alg_gen(I_DIV, $1.type<<4 | $3.type ); $$.type = operationResultType($1.type,$3.type); */

	  (yyval).type = operationResultType((yyvsp[-2]).type,(yyvsp[0]).type);
        if((yyval).type != (yyvsp[-2]).type){
            alg_gen(I_DIV, (1<<15)| ((yyvsp[-2]).type<<12) | ((yyval).type<<8) | ((yyvsp[-2]).type<<4 | (yyvsp[0]).type) );
        }else{
            if((yyval).type != (yyvsp[0]).type){
                alg_gen(I_DIV, (1<<15)| ((yyvsp[-2]).type<<12) | ((yyval).type<<8) | ((yyvsp[-2]).type<<4 | (yyvsp[0]).type) );
            }else{
                alg_gen(I_DIV, ((yyvsp[-2]).type<<4 | (yyvsp[0]).type) );
            }
        }

    }
#line 2269 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 788 "iec.y" /* yacc.c:1646  */
    {
        if((yyvsp[0]).type == TY_BYTE){
            alg_gen(I_CONST, (yyvsp[0]).intval&0xFF );
        }else{
            //alg_gen(I_CONST, $1.intval>>8 );
            //alg_gen(I_CONST, $1.intval&0xFF );
            alg_gen(I_CONST2, (yyvsp[0]).intval&0xFFFF );
        }
        (yyval).type = (yyvsp[0]).type;
	  }
#line 2284 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 798 "iec.y" /* yacc.c:1646  */
    {
        (yyval).type = TY_REAL;
        float_temp.f = (yyvsp[0]).floatval;
        //printf("Float=%X\n",float_temp.b[3]);
        alg_gen(I_CONST2, ((float_temp.b[3]<<8 & 0xFF00) | (float_temp.b[2]&0xFF))&0xFFFF );
        alg_gen(I_CONST2, ((float_temp.b[1]<<8 & 0xFF00) | (float_temp.b[0]&0xFF))&0xFFFF );
        }
#line 2296 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 806 "iec.y" /* yacc.c:1646  */
    {
        (yyval).type = (yyvsp[-1]).type;
        if(expr_postfix == 0){
		/*
        $$.listaf = $2.listaf;
        $$.listav = $2.listav;
		*/

        }
        (yyval).str = malloc(sizeof(char) * strlen((yyvsp[-1]).str)+1); strcpy((yyval).str, (yyvsp[-1]).str);}
#line 2311 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 817 "iec.y" /* yacc.c:1646  */
    {alg_gen(I_NOT, 0);}
#line 2317 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 818 "iec.y" /* yacc.c:1646  */
    {(yyval).str = malloc(sizeof(char) * 5);
        (yyval).type = sy_getType((yyvsp[0]).str);
            (yyval).str[0] = '\0';
            /*sprintf($$.str,"%s",  $1.str)*/;
            sprintf((yyval).str,"E%d",  22 );
           // if(expr_postfix == 0){

                //alg_gen(I_LOAD, sy_getPos($1.str) );
                alg_gen(I_LOAD, getTypeSize(sy_getType((yyvsp[0]).str))<<8 | sy_getPos((yyvsp[0]).str));
                if(in_evt){
                    alg_gen(I_CONST,0);
                    alg_gen(I_STORE, sy_getPos((yyvsp[0]).str));

                }

         //   }
		}
#line 2339 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 839 "iec.y" /* yacc.c:1646  */
    {(yyval).intval = I_GT;}
#line 2345 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 840 "iec.y" /* yacc.c:1646  */
    {(yyval).intval = I_GE;}
#line 2351 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 841 "iec.y" /* yacc.c:1646  */
    {(yyval).intval = I_LT;}
#line 2357 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 842 "iec.y" /* yacc.c:1646  */
    {(yyval).intval = I_LE;}
#line 2363 "iec.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 843 "iec.y" /* yacc.c:1646  */
    {(yyval).intval = I_EQ;}
#line 2369 "iec.tab.c" /* yacc.c:1646  */
    break;


#line 2373 "iec.tab.c" /* yacc.c:1646  */
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
#line 846 "iec.y" /* yacc.c:1906  */





int yywrap()
{
	return 1;
}

