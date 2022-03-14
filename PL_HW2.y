%{
#include<stdio.h>
int yylex();
void yyerror(char *message);
%}

%union {
    int ival;
    float fval;
}

%token<ival> INUMBER
%token<fval> FNUMBER
%token EOL
%type<ival> iexpr
%type<fval> fexpr
%left '+' '-'
%left '*' '/'
%nonassoc UPLUS '(' ')'

%%

first :line

line  : iexpr { printf("%d\n", $1); } EOL line
      | fexpr { printf("%f\n", $1); } EOL line
	  |
	  ;

iexpr : '-' iexpr { $$ = -$2;}
	  | '+' iexpr { $$ = $2 ;}
	  | iexpr '+' iexpr { $$ = $1 + $3 ;}
          | iexpr '-' iexpr { $$ = $1 - $3 ;}
          | iexpr '*' iexpr { $$ = $1 * $3 ;}
          | iexpr '/' iexpr { $$ = $1 / $3 ;}
	  | '(' iexpr ')' { $$ = $2 ;}
	  | INUMBER	{ $$ = $1; }
	  ;

fexpr : '-' fexpr { $$ = -$2;}
	  | '+' fexpr { $$ = $2 ;}
          | fexpr '+' fexpr { $$ = $1 + $3 ;}
          | fexpr '-' fexpr { $$ = $1 - $3 ;}
          | fexpr '*' fexpr { $$ = $1 * $3 ;}
          | fexpr '/' fexpr { $$ = $1 / $3 ;}
          | '(' fexpr ')' { $$ = $2 ;}
	  | FNUMBER	{ $$ = $1; }
	  ;

%%

void yyerror(char *message)
{
    printf("%s\n", message);
}

int main()
{
	yyparse();
	return 0;
}

