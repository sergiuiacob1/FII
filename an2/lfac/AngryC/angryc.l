%{
#include <stdio.h>
#include "utils.h"
#include "y.tab.h"
%}

number 0|[1-9][0-9]*
letter [a-zA-Z_]
varId [_]*{letter}+{number}*{letter}*

%%
"struct" {return STRUCT;}
"int"|"double"|"char"|"string"|"bool" {yylval.intVal = SetDataType (yytext); return VAR_DATA_TYPE;}
"void" {yylval.intVal = SetDataType (yytext); return FUNCTION_DATA_TYPE;}
"START_ALREADY!" {return BGIN;}
"ARE_WE_DONE_YET?!" {return END;}
"+="		 {strcpy (yylval.strVal, yytext); return(ADD_ASSIGN); }
"-="		 {strcpy (yylval.strVal, yytext); return(SUB_ASSIGN); }
"*="		 {strcpy (yylval.strVal, yytext); return(MUL_ASSIGN); }
"/="		 {strcpy (yylval.strVal, yytext); return(DIV_ASSIGN); }
"%="		 {strcpy (yylval.strVal, yytext); return(MOD_ASSIGN); }
"&="		 {strcpy (yylval.strVal, yytext); return(AND_ASSIGN); }
"|="		 {strcpy (yylval.strVal, yytext); return(OR_ASSIGN); }
"&&"		 {return(AND_OP); }
"||"		 {return(OR_OP); }
"<="		 {return(LE_OP); }
">="		 {return(GE_OP); }
"=="		 {return(EQ_OP); }
"!="		 {return(NE_OP); }
"<"			 {return(LS_OP); }
">"			 {return(GR_OP); }
"++"		 {return(PLSPLS);}
"="			 {return('='); }
"!"			 {return('!'); }
"-"			 {return('-'); }
"+"			 {return('+'); }
"*"			 {return('*'); }
"/"			 {return('/'); }
"%"			 {return('%'); }
"while" {return WHILE;}
"for" {return FOR;}
"if" {return IF;}
"else" {return ELSE;}
{varId} {if (WordIsReserved (yytext)) {REJECT;} strcpy (yylval.strVal, yytext); return ID;}
{varId}[ \t]*\[ {ExtractVectorName(yylval.strVal, yytext); if (WordIsReserved(yylval.strVal)) {REJECT;} yyless (yyleng - 1); return ID_VECTOR; }
{number} {yylval.intVal = atoi(yytext); return INTEGER;}
{number}"."{number} {yylval.doubleVal = atof(yytext); return DOUBLE;}
"const" {return CONST;}
"yell" {return YELL;}
["][^"]*["] {strcpy (yylval.strVal, yytext + 1); yylval.strVal [strlen(yylval.strVal) - 1] = 0; return STRING;}
[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
