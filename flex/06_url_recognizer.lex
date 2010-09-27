%option noyywrap

%{
%}
     
URL "http"[s]?":\/\/"[\/\.a-z0-9]*

%%

{URL}		{printf("URL \"%s\" found!\n", yytext);}
[ \t\n]+    	{}
.           	{}

%%

main(int argc, char **argv )
{
	yyin = fopen( argv[1], "r" );
        yylex();
}
