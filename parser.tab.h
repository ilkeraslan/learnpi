/* A Bison parser, made by GNU Bison 3.5.1.  */

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
    COMPLEX_TYPE_NOPIN = 260,
    INTEGER = 261,
    NAME = 262,
    IF = 263,
    THEN = 264,
    ELSE = 265,
    ENDIF = 266,
    LOOP = 267,
    START = 268,
    UNTIL = 269,
    ENDLOOP = 270,
    ADDITION = 271,
    SUBTRACTION = 272,
    MULTIPLICATION = 273,
    DIVISION = 274,
    MODULUS = 275,
    OR_OPERATION = 276,
    AND_OPERATION = 277,
    NOT_OPERATION = 278,
    OPEN_PARANTHESIS = 279,
    CLOSE_PARANTHESIS = 280,
    OPEN_BRACKET = 281,
    CLOSE_BRACKET = 282,
    OPEN_BRACE = 283,
    CLOSE_BRACE = 284,
    DOT = 285,
    COMMA = 286,
    ASSIGN = 287,
    CMP = 288,
    UMINUS = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 13 "parser.y"

  struct ast *ast;
  struct symbol_list *symbol_list;
  struct value *value;
  int integer;
  int function_id;
  char *str;
  int type;

#line 102 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
