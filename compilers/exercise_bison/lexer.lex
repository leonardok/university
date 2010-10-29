%{
#include "grammar.tab.h"
%}

RESERVED_WORD "for"|"do"|"if"|"then"|"else"|"while"|"program"
VARIABLE_TYPE "integer"|"string"|"real"|"boolean"|"character"|"longint"|"shortint"
IDENTIFIER [a-z][_a-z0-9]*
NUMBER [0-9]+
REAL   [0-9]+\.[0-9]*

%option yylineno

%%

{RESERVED_WORD} {return T_RESERVED;}
"var" {return T_VAR;}
":" {return ':';}
";" {return T_TERMINATOR;}
"=" {return '=';}
"(" {return '(';}
")" {return ')';}
"end." {printf("end found \n");return T_END;}
"begin" {return T_BEGIN;}

{VARIABLE_TYPE} {
	yylval.value_string = malloc(sizeof(char) * (yyleng + 1));
	strncpy(yylval.value_string, yytext, yyleng);
	yylval.value_string[yyleng+1] = '\0';
	return T_VARTYPE;
}

{IDENTIFIER} {
	yylval.value_string = malloc(sizeof(char) * (yyleng + 1));
	strncpy(yylval.value_string, yytext, yyleng);
	yylval.value_string[yyleng+1] = '\0';
	return T_IDENTIFIER;
}

":=" {return T_ATTRIBUTION;}

{NUMBER}|{REAL} {
	return T_VALUE;
}


[\n] 	{}
[ \t]+ 	{}
. 	{}

%%
