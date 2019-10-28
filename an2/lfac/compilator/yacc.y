%{
    #include <stdio.h>
    #include <string.h>
    #include "./utils.h"
    
    int yylex();
    int yyerror(char *);
    bool PrgError();
    
    extern FILE* yyin;
    extern char* yytext;
    extern int yylineno;
%}

%union {
    int intVal;
    struct variable var;
    bool boolVal;
    char *strVal;
};

%token ID
%token BGIN END
%token DATA_TYPE FUNCTION_DATA_TYPE
%token INTEGER STRING
%token ASSIGN
%token SUM FRACTION MINUS TIMES LW LWE EQ GRE GR
%token YELL
%start progr

%type<intVal> INTEGER
%type<var> varop
%type<intVal> DATA_TYPE
%type<strVal> ID STRING
//%type<boolVal> varlogop

%left SUM FRACTION MINUS TIMES LW LWE EQ GRE GR

%%
progr: declarations programInstructions
     ;

declarations :  declaration ';'
	   | declaration ';' declarations
	   ;
declaration : DATA_TYPE ID {AddNewVariable($1, $2); if (PrgError()) {return -1;}}
           | function_declaration
           ;

function_declaration: FUNCTION_DATA_TYPE ID '(' paramList ')'
                    | DATA_TYPE ID '(' paramList ')'
                    | FUNCTION_DATA_TYPE ID "()"
                    | DATA_TYPE ID "()"

paramList : declaration
            | declaration ',' paramList 
            ;

programInstructions : BGIN instructions END  
     ;
     
instructions :  statement ';' 
     | instructions statement ';'
     ;

statement: ID ASSIGN ID
         | ID ASSIGN INTEGER {CheckAssign ($1, $3); if (PrgError ()) {return -1;} AssignValue ($1, $3);}
         | ID '(' functionCall ')'
         | ID ASSIGN varop {AssignVarValue ($1, $3);}
         | YELL '(' ID ')' {Yell ($3); if (PrgError()) {return -1;}}
         | YELL '(' STRING ')' {YellString ($3); if (PrgError()) {return -1;}}
         ;

varop: ID SUM ID { $$ = OperatorFunction ($1, "+", $3); if (PrgError()) {return -1;}}
     | ID MINUS ID { $$ = OperatorFunction ($1, "-", $3); if (PrgError()) {return -1;}}
     | ID TIMES ID { $$ = OperatorFunction ($1, "*", $3); if (PrgError()) {return -1;}}
     | ID FRACTION ID { $$ = OperatorFunction ($1,"/", $3); if (PrgError()) {return -1;}}
     ;
       
//varlogop: ID LW ID {  $$ = LogicOperatorFunction ($1, "<", $3) if (PrgError()) {return -1;}}
//		;
functionCall : INTEGER
           | functionCall ',' INTEGER
           ;
%%
bool PrgError(){
    /*if (haveErorr){
        yyerror(errorMessage);
        return true;
    }*/
    return false;
}

int yyerror(char * s){
    printf("eroare: %s la linia: %d\n", s, yylineno);
}

int main(int argc, char** argv){
    yyin=fopen(argv[1],"r");
    yyparse();
} 