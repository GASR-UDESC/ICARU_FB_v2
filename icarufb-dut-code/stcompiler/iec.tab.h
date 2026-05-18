/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
