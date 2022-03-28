%{
#include <stdio.h>
#include <string.h>

int tables[26];

int yylex();
void yyerror(const char *msg);
void fail(int f);
int check_type(char c);
int set_type(char c, int v);
%}

%union {
	int pt;
	int ival;
	float fval;
	struct numexp {
		int type;
	} numexp;
	struct ids {
		char name;
		int pt;
	} ids;
}

%type <numexp> numexp
%token <ival> INUMBER
%token <fval> FNUMBER
%token <pt> PRINT VAR EN EQU OP
%token <ids> ID
%left OP

%%
s	: line {};
		
line	: expr EN line {}
	| ;
		
expr	: VAR ID EQU numexp {
	if (set_type($2.name, $4.type) == 0) {
		fail($2.pt);
		YYABORT;
	}}
	| PRINT ID {
	switch(check_type($2.name)) {
		case 0 :
			fail($2.pt);
			YYABORT;
			break;
		case 1 : 
			printf("%c type is int.\n", $2.name);
			break;
		case 2 : 
			printf("%c type is float.\n", $2.name);
	}};
		
numexp	: INUMBER { $$.type = 1; }
	| FNUMBER { $$.type = 2; }
	| ID { 
	int id_type = check_type($1.name);
	if (id_type != 0) $$.type = id_type; 
	else {
		fail($1.pt);
		YYABORT;
	}}
	| numexp OP numexp {
	if ( $1.type == $3.type ) $$.type = $1.type;
	else {
		printf("Type error. ");
		fail($2);
		YYABORT;
	}};

%%

void yyerror (const char *message) {
    printf("Syntax Error\n");
}

//檢查變數型態
int check_type(char c) {			
	return tables[c-'A'];
}

//設定變數型態
int set_type(char c, int v) {
	if(tables[c-'A'] == 0) {
		tables[c-'A'] = v;
		return 1;
	} else {
		printf("Id %c redeclaration. ", c);
		return 0;
	}
}

//輸出錯誤位置
void fail(int f) {
	printf("Error at line %d.\n", f);
}

int main() {
	for(int i = 0; i < 26; i++) tables[i] = 0;
    	yyparse();
    	return 0;
}