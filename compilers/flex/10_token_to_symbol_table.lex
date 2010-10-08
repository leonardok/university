%option noyywrap

%{
#define TRUE  0
#define FALSE 1

typedef struct symbol_table_s symbol_table_t;
struct symbol_table_s
{
	char 		*symbol;
	symbol_table_t 	*next_symbol;
};

void add_symbol_to_table(char *);

symbol_table_t *symbol_table = NULL;
%}
     
INTEGER		[0-9]*
FLOAT		[0-9]*"."[0-9]*
RESERVED_WORD 	"int"|"for"|"do"|"if"|"then"|"else"|"while"
ID		[a-z][a-z0-9]*

%%

{INTEGER}	{printf("integer \"%s\" found!\n", yytext);}
{FLOAT}		{printf("float point \"%s\" found!\n", yytext);}
{RESERVED_WORD}	{printf("reserved word \"%s\" found!\n", yytext);}
{ID}		{printf("identifier \"%s\" found!\n", yytext); add_symbol_to_table(yytext);}
[ \t\n]+    	{}
.           	{}

%%

int symbol_lookup(char *symbol)
{
	symbol_table_t *symbol_ptr = symbol_table;

	while (symbol_ptr != NULL)
	{
		if (!strcmp(symbol_ptr->symbol, symbol))
			return TRUE;

		symbol_ptr = symbol_ptr->next_symbol;
	}
	return FALSE;
}

void add_symbol_to_table(char *symbol)
{
	symbol_table_t *symbol_ptr = symbol_table;

	if (symbol_lookup(symbol) == TRUE)
		return;

	symbol_table_t *new_node = malloc(sizeof(symbol_table_t));

	new_node->symbol = malloc(sizeof(char) * (strlen(symbol)+1));
	strcpy(new_node->symbol, symbol);

	if (symbol_table == NULL)
		symbol_table = new_node;
	else
	{
		while (symbol_ptr->next_symbol != NULL)
			symbol_ptr = symbol_ptr->next_symbol;

		symbol_ptr->next_symbol = new_node;
	}
}

main(int argc, char **argv )
{
	yyin = fopen( argv[1], "r" );
        yylex();

	symbol_table_t *symbol_ptr = symbol_table;
	while (symbol_ptr != NULL)
	{
		printf("Synbol \"%s\" found on table\n", symbol_ptr->symbol);
		symbol_ptr = symbol_ptr->next_symbol;
	}
}
