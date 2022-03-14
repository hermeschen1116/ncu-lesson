%{
#include "exam2_1.tab.h"
%}

FLOAT ([0-9]+\.[0-9]+)

%%

[0-9]+ { yylval.ival=atoi(yytext);return INUMBER; }
{FLOAT} {yylval.fval=atof(yytext);return FNUMBER; }
[\n] {return EOL;}
[\t] {}
. { return yytext[0]; }

%%
