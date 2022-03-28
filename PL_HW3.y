%{
#include<stdio.h>
#include<string.h>

int yylex();
void yyerror(const char *msg);
void fail(int f);
int check_type(char c);
int set_type(char c,int v);
int tables[26];

%}

%union {
	int ival;
	int pt;
	float fval;
	struct numexp{
		int type;
	}numexp;
	struct ids{
		char name;
		int pt;
	}ids;
}
%type <numexp> numexp
%token<ival> INUMBER
%token<fval> FNUMBER
%token<pt> PRINT IDCL FDCL EN EQU OP
%token<ids> ID
%left OP

%%
s		:line			{}
		;
		
line	:expr EN line	{}
		|
		;
		
expr	:dcl			{}
		|ID EQU numexp	{
			int id_type = check_type($1.name);
			if ( id_type == 0 ) {
				fail($1.pt);
				YYABORT;
			}
			if ( $3.type != id_type ) {
				printf("Type error. ");
				fail($1.pt);
				YYABORT;
			}
		}
		|PRINT ID {
			switch(check_type($2.name)) {
				case -1 : 
					printf("%c type is int.\n", $2.name);
					break;
				case 1 : 
					printf("%c type is float.\n", $2.name);
					break;
				case 0 :
					fail($2.pt);
					YYABORT;
			}
		}
		;
		
dcl		: IDCL ID {
			if (set_type($2.name, -1) == 0) {
				fail($2.pt);
				YYABORT;
			}}
		| FDCL ID {
			if (set_type($2.name, 1) == 0) {
				fail($2.pt);
				YYABORT;
			}}
		;
		
numexp	: INUMBER { $$.type = -1; }
	| FNUMBER { $$.type = 1; }
	| ID { 
		if (check_type($1.name) != 0 ) $$.type = check_type($1.name); 
		else {
			fail($1.pt);
			YYABORT;
		}
	}
	| numexp OP numexp {
		if ( $1.type == $3.type ) $$.type = $1.type;
		else {
			printf("Type error. ");
			fail($2);
			YYABORT;
		}
	};

%%
void yyerror (const char *message)
{
    printf("Syntax Error\n");
}
int check_type(char c){//檢查變數型態
	if(tables[c-'A']!=0){
		return tables[c-'A'];
	}else{
		printf("Id %c undefined. ",c);
		return 0;
	}
	
}
int set_type(char c,int v){//設定變數型態
	if(tables[c-'A']==0){
		tables[c-'A']=v;
		return 1;
	}else{
		printf("Id %c redeclaration. ",c);
		return 0;
	}
}

void fail(int f){//輸出錯誤位置
	printf("Error at line %d.\n",f);
}

int main() {
	for(int i=0;i<26;i++){tables[i]=0;}
    yyparse();
    return(0);
}