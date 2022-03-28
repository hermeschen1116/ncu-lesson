%{
#include "y.tab.h"

%}
%option yylineno

id		[A-Z]{1}
fnum	([0-9]+\.[0-9]+)
inum	[1-9][0-9]*
op		[\+/\*\-\%]

%%
"print"	{yylval.pt=yylineno;return PRINT;}
{fnum}	{yylval.fval=atof(yytext);return FNUMBER;}
{inum}	{yylval.ival=atoi(yytext);return INUMBER;}
"int"	{yylval.pt=yylineno;return IDCL;}
"float"	{yylval.pt=yylineno;return FDCL;}
{id}	{yylval.ids.name=yytext[0];yylval.ids.pt=yylineno;return ID;}
{op}	{yylval.pt=yylineno;return OP;}
"="		{yylval.pt=yylineno;return EQU;}
";"		{return EN;}
[ \t\n]	{}
.		{return yytext[0]; }

%%
