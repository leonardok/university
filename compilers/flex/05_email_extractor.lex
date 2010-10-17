%option noyywrap

%{
%}
     
EMAIL [._a-z0-9]*"@"[_a-z0-9]+"."([_a-z0-9][.])?[a-z]{2,3}

%%

{EMAIL}		{printf("Email \"%s\" found!\n", yytext);}
[ \t\n]+    	{}
.           	{}

%%

main(int argc, char **argv )
{
	yyin = fopen( argv[1], "r" );
        yylex();
}
