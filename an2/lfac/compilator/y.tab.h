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
    ID = 258,
    BGIN = 259,
    END = 260,
    DATA_TYPE = 261,
    FUNCTION_DATA_TYPE = 262,
    INTEGER = 263,
    STRING = 264,
    ASSIGN = 265,
    SUM = 266,
    FRACTION = 267,
    MINUS = 268,
    TIMES = 269,
    LW = 270,
    LWE = 271,
    EQ = 272,
    GRE = 273,
    GR = 274,
    YELL = 275
  };
#endif
/* Tokens.  */
#define ID 258
#define BGIN 259
#define END 260
#define DATA_TYPE 261
#define FUNCTION_DATA_TYPE 262
#define INTEGER 263
#define STRING 264
#define ASSIGN 265
#define SUM 266
#define FRACTION 267
#define MINUS 268
#define TIMES 269
#define LW 270
#define LWE 271
#define EQ 272
#define GRE 273
#define GR 274
#define YELL 275

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 15 "yacc.y" /* yacc.c:1909  */

    int intVal;
    struct variable var;
    bool boolVal;
    char *strVal;

#line 101 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
