%{

%}
%start CUV NR
%%
["][a-z]/[!]+ {BEGIN CUV;}
["][a-zA-Z][a-zA-Z]+[!]+ {if (yyleng%2 == 1 && yytext[yyleng - 1] != 'a' && yytext[yyleng - 2] != 'a') BEGIN CUV;}
(1[0-9]{0,3}|2000)[!]+ {BEGIN NR; REJECT;}

<CUV>([a-zA-Z][a-zA-Z])*[!]+ {BEGIN 0;}
<CUV>([a-zA-Z][a-zA-Z])+/aa {BEGIN 0;}
<CUV>(1[0-9]{0,3}|2000) {REJECT;}
<CUV>[0-9]+ {BEGIN 0;}
<CUV>["] {fprintf (yyout, "\"%s\"\n", yytext); BEGIN 0;}

<NR>(1[0-9]{0,3}|2000) {REJECT;}
<NR>[0-9]* {BEGIN 0;}
<NR>([a-zA-Z][a-zA-Z])*[!]+ {BEGIN 0;}
<NR>([a-zA-Z][a-zA-Z])+/aa {BEGIN 0;}
<NR>["] {fprintf (yyout, "\"%s\"\n", yytext); BEGIN 0;}

[1-9]+[0-9]*/"0" {printf ("%s0\n", yytext);}
%%

int main(int argc, void *argv[]){
    FILE *g, *out;
    g = fopen ("input.txt", "r");
    yyin = g;

    out = fopen ("out.txt", "w");

    if (!g)
        printf ("Eroare la creare fisier!");
    else
        yyout = out;
    
    yylex();
}