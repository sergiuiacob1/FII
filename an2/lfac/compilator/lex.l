%{
#include <stdio.h>
#include "utils.h"
#include "y.tab.h"
%}

number 0|[1-9][0-9]*
letter [a-zA-Z_]
varId [_]*{letter}+{number}*

%%
"int"|"float"|"char"|"string" {yylval.intVal = SetDataType (yytext); return DATA_TYPE;}
"void" {return FUNCTION_DATA_TYPE;}
"begin_progr" {return BGIN;}
"end_progr" {return END;}
"+" {return SUM;}
"-" {return MINUS;}
"*" {return TIMES;}
"/" {return FRACTION;}
"<" {return LW;}
"<=" {return LWE;}
"==" {return EQ;}
">=" {return GRE;}
">" {return GR;}
{varId} {if (strcmp (yytext, "yell")==0) {REJECT;} yylval.strVal = (char *)malloc (strlen(yytext) + 1); strcpy (yylval.strVal, yytext); return ID;}
":=" {return ASSIGN;}
{number} {yylval.intVal = atoi(yytext); return INTEGER;}
"yell" {return YELL;}
["][^"]*["] {yylval.strVal = (char *)malloc (strlen(yytext) + 1); strcpy (yylval.strVal, yytext + 1); yylval.strVal [strlen(yylval.strVal) - 1] = 0; return STRING;}
[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
