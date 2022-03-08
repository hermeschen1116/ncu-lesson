%option noyywrap

id-num          ^[A-Z][0-9]{9}$
word            ^[A-Z][a-zA-Z]*$
eol             [\n]

%%
{id-num}        { printf("%s\n", yytext); }
{word}          { printf("%s\n", yytext); }
{eol}           { /* do nothing */ }
.               { /* do nothing */ }
%%

int main(int argc, char *argv[])
{
    yylex();
    return(0);
}
