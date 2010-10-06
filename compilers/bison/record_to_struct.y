/**
 * this is a pascal to C "register"
 *
 * "register" is the pascall "struct" equivalent
 * this is an example of a record declaration:
 *
 * type tipo_liv=record
 *     titulo:integer
 *     autor:string
 * end;
 * var livro:tipo_liv;
 *
 */

%{
#include <stdio.h>

	void declare_variable(char *, char*);
%}

%union {
	char  *value_string;
	int   value_int;
	float value_float;
}

%token <value_string> T_RESERVED_WORD
%token <value_string> T_IDENTIFIER
%token <value_string> T_VARIABLE_TYPE
%token <value_int>    T_INTEGER 
%token <value_float>  T_FLOAT
%token T_TYPE
%token T_END
%token T_RECORD 
%token T_VAR
%token T_ARRAY
%token T_EOL

%start statement 

%%
statement: record
         | variable_declaration
	 ;

record: T_TYPE T_IDENTIFIER '=' T_RECORD variable_declaration

variable_declaration: T_IDENTIFIER ':' T_VARIABLE_TYPE ';' {declare_variable($1, $3);} variable_declaration 
                    | T_END ';'
                    ;
%%

void declare_variable(char *a, char *b){
	printf("\nfound variable declaration with %s and %s\n", a, b);
	return;
}

int main() {
	yydebug = 3;
	printf("> ");
	return yyparse();
}

int yyerror(const char* errstr) {
	printf("Error: %s \n", errstr);
	return -1;
}
