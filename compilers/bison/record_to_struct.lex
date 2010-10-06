
%{
#include "record_to_struct.tab.h"
%}

RESERVED_WORD 	"for"|"do"|"if"|"then"|"else"|"while"
VARIABLE_TYPE	"integer"|"string"|"real"|"boolean"|"character"|"longint"|"shortint"
IDENTIFIER 	[a-z][_a-z0-9]*

%%

{RESERVED_WORD} {return T_RESERVED_WORD;}
"type"		{return T_TYPE;}
"record"	{return T_RECORD;}
"var"		{return T_VAR;}
"array" 	{return T_ARRAY;}
":"		{return ':';}
";"		{return ';';}
"="		{return '=';}
"end"		{return T_END;}
{VARIABLE_TYPE} {
		yylval.value_string = malloc(sizeof(char) * (yyleng + 1)); 
		strncpy(yylval.value_string, yytext, yyleng);
		yylval.value_string[yyleng+1] = '\0';
		return T_VARIABLE_TYPE;
		}
{IDENTIFIER}	{
		yylval.value_string = malloc(sizeof(char) * (yyleng + 1)); 
		strncpy(yylval.value_string, yytext, yyleng);
		yylval.value_string[yyleng+1] = '\0';
		return T_IDENTIFIER;
		}
[\n]		{}
[ \t]+	 	{}
. 		{}

%%
