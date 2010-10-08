%option noyywrap

%{
%}
     
WORD     [a-z0-9]*
NUMBER   [0-9]*

%%

{NUMBER}	{printf("Number \"%s\" found!\n", yytext);}
{WORD}		{}
[ \t\n]+    	{}
.           	{}

%%

main(int argc, char **argv )
{
	yyin = fopen( argv[1], "r" );
        yylex();
}
