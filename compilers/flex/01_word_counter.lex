%option noyywrap

%{
#include <math.h>

int word = 0;
%}
     
WORD     [a-z0-9]*

%%

{WORD}		{word++; printf("Word \"%s\" found!\n", yytext);}
[ \t\n]+    	{}
.           	{}

%%

main(int argc, char **argv )
{
	yyin = fopen( argv[1], "r" );
        yylex();

	printf("\n");
	printf("word count is %d\n", word);
}
