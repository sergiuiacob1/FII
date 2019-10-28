%%
[a-z]/[!]+ {BEGIN CUV;}
[a-zA-Z][a-zA-Z]+ {if (yyleng%2 == 1 && yytext[yyleng - 1] != 'a' && yytext[yyleng - 2] != 'a') BEGIN CUV;}
<CUV><CUV> {BEGIN CUV;}
<CUV><NR> {BEGIN NR;}
<NR> {}


({cuvant}/[!]+)* {if (yytext[yyleng - 1] != 'a' && yytext[yyleng - 2] != 'a') fprintf (yyout, "%s\n", yytext;)}
cuvant [a-zA-Z]([a-zA-Z][a-zA-Z])+
numar 1[0-9]{1,3}|2000
%%