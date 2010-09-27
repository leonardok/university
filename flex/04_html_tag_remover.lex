%option noyywrap

%{
%}
     
HTML_TAGS "<"[/a-z0-9]*">"

%%

{HTML_TAGS}	{}
.           	{printf("%s", yytext);}

%%

main(int argc, char **argv )
{
	yyin = fopen( argv[1], "r" );
        yylex();
}
