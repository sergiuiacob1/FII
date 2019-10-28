%{
    #include <stdio.h>
    #include <string.h>
    #include "./utils.h"
    
    int yylex();
    int yyerror(const char *);
    bool PrgError();
    
    extern FILE* yyin;
    extern char* yytext;
    extern int yylineno;
%}

%union {
    int intVal;
    double doubleVal;
    bool boolVal;
    char strVal[MAX_STRVAL];
    struct variable var;
    Parameter parameter;
};

%token ID ID_VECTOR CONST STRUCT
%token BGIN END
%token VAR_DATA_TYPE FUNCTION_DATA_TYPE
%token INTEGER DOUBLE STRING
%token LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP LS_OP GR_OP DONE
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME 
%token FOR IF ELSE WHILE
%token YELL
%start progr

%type<intVal> INTEGER
%type<var> varop
%type<intVal> data_type VAR_DATA_TYPE FUNCTION_DATA_TYPE function_call
%type<strVal> ID ID_VECTOR STRING param_list_function_call param_declaration_list
%type<strVal> assign_op ADD_ASSIGN AND_ASSIGN MUL_ASSIGN DIV_ASSIGN OR_ASSIGN MOD_ASSIGN SUB_ASSIGN
%type<doubleVal> DOUBLE
%type<parameter> param_function_call
//%type<boolVal> varlogop

%left '=' ADD_ASSIGN AND_ASSIGN MUL_ASSIGN DIV_ASSIGN OR_ASSIGN MOD_ASSIGN SUB_ASSIGN
%left '+' '-'
%left '*' '/' '%'
%left OR_OP
%left AND_OP
%left EQ_OP NE_OP
%left LS_OP LE_OP GR_OP GE_OP
%nonassoc PLSPLS

%%
progr: declarations programInstructions
     ;

declarations: declaration '!'
	        | declaration '!' declarations
	        ;

data_type: VAR_DATA_TYPE {$$ = $1;}
         | FUNCTION_DATA_TYPE {$$ = $1;}
         ;

declaration: variable_declaration
           | function_declaration '{' function_instructions '}' {nrParams = 0;}
           | function_declaration '{' '}' {nrParams = 0;}
           | vector_declaration
           | const_variable_declaration
           | struct_declaration
           ;

struct_declaration: STRUCT ID '{' declarations '}' {AddNewStruct ($2); if (PrgError()) {return -1;}}
                  ;

function_instructions: instructions
                     | declarations
                     | instructions function_instructions
                     | declarations function_instructions 
                     ;

variable_declaration: VAR_DATA_TYPE ID {AddNewVariable($1, $2); if (PrgError()) {return -1;}}

function_declaration: FUNCTION_DATA_TYPE ID '(' param_declaration_list ')' {AddNewFunctionWithParameters ($1, $2); if (PrgError()) {return -1;}}
                    | FUNCTION_DATA_TYPE ID '(' ')' {AddNewFunction ($1, $2); if (PrgError()) {return -1;}}
                    | VAR_DATA_TYPE ID '(' param_declaration_list ')' {AddNewFunctionWithParameters ($1, $2); if (PrgError()) {return -1;}}
                    | VAR_DATA_TYPE ID '(' ')' {AddNewFunction ($1, $2); if (PrgError()) {return -1;}}
                    ;

vector_declaration: VAR_DATA_TYPE ID_VECTOR '[' INTEGER ']' {DeclareVector ($1, $2, $4); if (PrgError()) {return -1;}}

const_variable_declaration: CONST VAR_DATA_TYPE ID '=' INTEGER {AddNewConstant($2, $3, $5); if (PrgError()) {return -1;}}
                          | CONST VAR_DATA_TYPE ID '=' DOUBLE {AddNewConstant($2, $3, $5); if (PrgError()) {return -1;}}
                          | CONST VAR_DATA_TYPE ID '=' STRING {AddNewConstant($2, $3, $5); if (PrgError()) {return -1;}}

param_declaration_list: data_type {parameters[nrParams].dataType = $1; ++nrParams;}
                       | data_type ',' param_declaration_list {parameters[nrParams].dataType = $1; ++nrParams;}
                       ;

programInstructions: BGIN instructions END;
     
instructions : statement '!' 
             | instructions statement '!'
             ;

statement: assignment
         | function_call
         | YELL '(' ID ')' {Yell ($3); if (PrgError()) {return -1;}}
         | YELL '(' STRING ')' {YellString ($3); if (PrgError()) {return -1;}}
         | YELL '(' ID_VECTOR '[' INTEGER ']' ')' {YellVec($3, $5); if (PrgError()) {return -1;}}
         | YELL '(' ID_VECTOR '[' ID ']' ')' {struct variable var = GetVariable ($5); if (var.dataType != INT_t || var.isInitialized == false) {yyerror ("Vector index can only be an initialized integer!!!"); return -1;} YellVec ($3, var.value.intVal); }
         | YELL '(' varop ')' {YellVarOp ($3); if (PrgError()) {return -1;} }
         | control_statement
         | varop
         ;

control_statement: if_statement
                 | for_statement
                 | while_statement
                 ;

while_statement: WHILE '(' varop ')' '{' instructions '}'
               | WHILE '(' varop ')' '{' '}'

for_statement: FOR '(' for_assignments '!' varop '!' varop ')'
             | FOR '(' for_assignments '!' varop '!' for_assignments ')' 
             | FOR '(' for_assignments '!' varop '!' ')'
             | FOR '(' '!' varop '!' varop ')'
             | FOR '(' '!' varop '!' for_assignments ')'
             | FOR '(' '!' varop '!' ')' {/*PANA AICI FARA INSTRUCZTIUNI*/}
             | FOR '(' for_assignments '!' varop '!' varop ')' '{' instructions '}'
             | FOR '(' for_assignments '!' varop '!' for_assignments ')' '{' instructions '}'
             | FOR '(' for_assignments '!' varop '!' ')' '{' instructions '}'
             | FOR '(' '!' varop '!' varop ')' '{' instructions '}'
             | FOR '(' '!' varop '!' for_assignments ')' '{' instructions '}'
             | FOR '(' '!' varop '!' ')' '{' instructions '}'

for_assignments: assignment
               | assignment ',' for_assignments

if_statement: IF varop '{' instructions '}' {}
            | IF varop '{' '}'
            | IF varop '{' instructions '}' ELSE '{' instructions '}'
            | IF varop '{' '}' ELSE '{' instructions '}'
            | IF varop '{' instructions '}' ELSE '{' '}'
            | IF varop '{' '}' ELSE '{' '}'

assignment: ID '=' varop {AssignVarValue ($1, $3); if (PrgError()) {return -1;}}
          | ID assign_op varop {struct variable var1, rezVar; var1 = GetVariable($1); rezVar = $3; rezVar = OperatorFunction (var1, $2, rezVar); AssignVarValue (var1.varName, rezVar);}
          | ID_VECTOR '[' INTEGER ']' '=' varop { AssignVectorValue($1, $3, $6); if (PrgError()) {return -1;} }
          | ID_VECTOR '[' ID ']' '=' varop {struct variable var = GetVariable ($3); if (PrgError()) {return -1;} if (var.dataType != INT_t || var.isInitialized == false) {yyerror ("Vector index can only be an initialized integer!!!"); return -1;} AssignVectorValue ($1, var.value.intVal, $6);}
          ;

assign_op: ADD_ASSIGN {strcpy ($$, $1);}
         | SUB_ASSIGN {strcpy ($$, $1);}
         | MUL_ASSIGN {strcpy ($$, $1);}
         | DIV_ASSIGN {strcpy ($$, $1);}
         | MOD_ASSIGN {strcpy ($$, $1);}
         | AND_ASSIGN {strcpy ($$, $1);}
         | OR_ASSIGN {strcpy ($$, $1);}
         ;

varop: varop '+' varop { $$ = OperatorFunction ($1, "+", $3); if (PrgError()) {return -1;}}
     | varop '-' varop { $$ = OperatorFunction ($1, "-", $3); if (PrgError()) {return -1;}}
     | varop '*' varop { $$ = OperatorFunction ($1, "*", $3); if (PrgError()) {return -1;}}
     | varop '/' varop { $$ = OperatorFunction ($1,"/", $3); if (PrgError()) {return -1;}}
     | varop '%' varop { $$ = OperatorFunction ($1, "%", $3); if (PrgError()) {return -1;}}
     | '(' varop ')' {$$ = $2;}
     | '-' varop %prec '*'  { $$ = $2; $$.value.intVal=-$$.value.intVal; $$.value.doubleVal=-$$.value.doubleVal;}
     | '~' varop %prec "LS_OP" { $$ = $2; if($$.value.boolVal==0){$$.value.boolVal=1;}else{$$.value.boolVal=0;} }
     | varop AND_OP varop {$$ = OperatorFunction ($1, "&&", $3); if (PrgError()) {return -1;}}
     | varop OR_OP varop {$$ = OperatorFunction ($1, "||", $3); if (PrgError()) {return -1;}}
     | varop LE_OP varop { $$ = OperatorFunction ($1, "<=", $3); if (PrgError()) {return -1;}}
     | varop GE_OP varop { $$ = OperatorFunction ($1, ">=", $3); if (PrgError()) {return -1;}}
     | varop EQ_OP varop { $$ = OperatorFunction ($1, "==", $3); if (PrgError()) {return -1;}}
     | varop NE_OP varop { $$ = OperatorFunction ($1, "!=", $3); if (PrgError()) {return -1;}}
     | varop LS_OP varop { $$ = OperatorFunction ($1, "<", $3); if (PrgError()) {return -1;}}
     | varop GR_OP varop { $$ = OperatorFunction ($1, ">", $3); if (PrgError()) {return -1;}}
     | PLSPLS ID { Incr($2); $$= GetVariable($2); }
     | ID PLSPLS { $$=GetVariable($1); Incr($1); }
     | ID {$$ = GetVariable($1); }
     | INTEGER {struct variable tempVar; strcpy (tempVar.varName, "tempVar"); tempVar.value.intVal = $1; tempVar.dataType = INT_t; tempVar.isInitialized = true; $$ = tempVar;}
     | DOUBLE {struct variable tempVar; strcpy (tempVar.varName, "tempVar"); tempVar.value.doubleVal = $1; tempVar.dataType = DOUBLE_t; tempVar.isInitialized = true;  $$ = tempVar;}
     | STRING {struct variable tempVar; tempVar.value.stringVal = (char*)malloc (strlen($1)+1); strcpy (tempVar.varName, "tempVar"); strcpy (tempVar.value.stringVal, $1); tempVar.dataType = STRING_t; tempVar.isInitialized = true;  $$ = tempVar;}
     ;

function_call: ID '(' param_list_function_call ')' {int auxDataType; FunctionCallWithParameters ($1); auxDataType = GetFunction($1).dataType; nrParams = 0; if (PrgError()) {return -1;} $$ = auxDataType;}
             | ID '('')' {} {FunctionCallNoParameters ($1); if (PrgError()) {return -1;} $$ = GetFunction($1).dataType;}
             ;

param_list_function_call: param_function_call {parameters[nrParams] = $1; ++nrParams;}
                        | param_function_call ',' param_list_function_call {parameters[nrParams] = $1; ++nrParams; }
                        ;

param_function_call: ID {struct variable var; var = GetVariable ($1); if (PrgError()) {return -1;} strcpy ($$.parName, $1); $$.dataType = GetVariable ($1).dataType; $$.isFunction = false;}
                   | INTEGER {$$.dataType = INT_t; $$.isFunction = false;}
                   | DOUBLE {$$.dataType = DOUBLE_t; $$.isFunction = false;}
                   | STRING {$$.dataType = STRING_t; $$.isFunction = false;}
                   | function_call {$$.dataType = $1; $$.isFunction = true;}

%%
bool PrgError(){
    if (haveError){
        yyerror(errorMessage);
        return true;
    }
    return false;
}

int yyerror(const char *s){
    printf("eroare: %s la linia: %d\n", s, yylineno);
}

int main(int argc, char** argv){
    yyin=fopen(argv[1],"r");
    yyparse();
} 