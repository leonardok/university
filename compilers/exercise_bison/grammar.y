%{
#include <stdio.h>
#include "util.h"

extern int yylineno;

int yyerror(const char*);
%}


%union {
	char  *value_string;
	int   value_int;
	float value_float;
}

%token T_VAR
%token T_VARTYPE
%token T_BEGIN
%token T_PROGRAM
%token T_END
%token T_TERMINATOR
%token T_VALUE
%token <value_string> T_IDENTIFIER
%token T_FUNCTION
%token T_ATTRIBUTION
%token T_RESERVED


%start statement

%%
statement: variable_declaration statement
         | variable_attribuition statement
         | variable_use statement
         | other statement
         | T_END
         ;

other: T_RESERVED T_IDENTIFIER T_TERMINATOR {printf("other stuff found!\n");}
     | T_BEGIN
     ;

variable_declaration: T_IDENTIFIER ':' T_VARTYPE T_TERMINATOR 
		      {
			      printf("declaration of %s on line %d\n", $1, yylineno);
			      add_to_matrix($1, yylineno, DECLARATION);
		      }
                    | T_VAR T_IDENTIFIER ':' T_VARTYPE T_TERMINATOR 
		      {
			      printf("declaration of %s on line %d\n", $2, yylineno);
			      add_to_matrix($2, yylineno, DECLARATION);
		      }
                    ;

variable_attribuition: T_IDENTIFIER T_ATTRIBUTION T_VALUE T_TERMINATOR 
		       {
			       printf("attribuition on line %d\n", yylineno);
			       add_to_matrix($1, yylineno, ATTRIBUTION);
		       }
                     | T_IDENTIFIER T_ATTRIBUTION T_IDENTIFIER T_TERMINATOR
		       {
			       printf("attribuition on line %d\n", yylineno);
			       add_to_matrix($1, yylineno, ATTRIBUTION);
		       }
                     ;

variable_use: T_IDENTIFIER '(' T_IDENTIFIER ')' T_TERMINATOR 
	      {
		      printf("function on line %d\n", yylineno);
                      add_to_matrix($3, yylineno, USE_IN_FUNCTION);
	      }
%%


int yyerror(const char* errstr) {
	printf("Error: %s \n", errstr);
	return -1;
}

