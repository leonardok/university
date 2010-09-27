%option noyywrap

%{
%}
     
INTEGER		[0-9]*
FLOAT		[0-9]*"."[0-9]*
RESERVED_WORD 	"int"|"for"|"do"|"if"|"then"|"else"|"while"
ID		[a-z][a-z0-9]*

%%

{INTEGER}	{printf("integer \"%s\" found!\n", yytext);}
{FLOAT}		{printf("float point \"%s\" found!\n", yytext);}
{RESERVED_WORD}	{printf("reserved word \"%s\" found!\n", yytext);}
{ID}		{printf("identifier \"%s\" found!\n", yytext);}
[ \t\n]+    	{}
.           	{}

%%

main(int argc, char **argv )
{
	yyin = fopen( argv[1], "r" );
        yylex();
}
