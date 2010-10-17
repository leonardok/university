%option noyywrap

%{
%}
     
HIDE 	"<hide>".*"</hide>"

%%

{HIDE}		{}
[ \t\n]+    	{printf("%s", yytext);}
.           	{printf("%s", yytext);}

%%

main(int argc, char **argv )
{
	yyin = fopen( argv[1], "r" );
        yylex();
}
