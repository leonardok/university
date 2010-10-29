#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "util.h"

extern FILE *yyin;
symbol_matrix_t symbol_matrix = {NULL, -1, -1, -1, NULL};

void usage(void)
{
	printf("\n");
	printf("You need to give input and an output files\n");
	printf("USAGE:\n");
	printf("\trecord_to_struct -i <input_file> -o <output_file>\n");
	printf("\n");
	printf("\t-i\timput file\n");
	printf("\t-o\toutput file\n");
	printf("\tfor stdin input use \"-i null\"");
	printf("\n");

	exit(0);
}

symbol_matrix_t* search_variable(char *variable)
{
	symbol_matrix_t *symbol_matrix_ptr = &symbol_matrix;
	while (symbol_matrix_ptr && symbol_matrix_ptr->var_name)
	{
		if (!strcmp(symbol_matrix_ptr->var_name, variable))
			return symbol_matrix_ptr;

		symbol_matrix_ptr = symbol_matrix_ptr->next;
	}
}

symbol_matrix_t* get_last_entry(void)
{
	symbol_matrix_t *symbol_matrix_ptr = &symbol_matrix;
	while (symbol_matrix_ptr->next != NULL)
		symbol_matrix_ptr = symbol_matrix_ptr->next;

	return symbol_matrix_ptr;
}

void add_to_matrix(char *variable, int line, int kind_of_use)
{
	printf("adding variable \"%s\" into the matrix\n", variable);
	/* 
	 * first variable to be added into the matrix. it must be a
	 * variable declaration, if not, we are trying to use a non
	 * existent variable. an syntax error must be throw.
	 */
	if ((!(symbol_matrix.var_name)) && (kind_of_use == DECLARATION))
	{
		printf("matrix is empty. add first element\n");
		(&symbol_matrix)->var_name = malloc(sizeof(char)*(strlen(variable)+1));
		strncpy(symbol_matrix.var_name, variable, strlen(variable));
		symbol_matrix.var_name[strlen(variable)] = '\0';

		printf("declared %s\n\n", symbol_matrix.var_name);

		symbol_matrix.declaration_line = line;
		return;
	}
	else if (!symbol_matrix.var_name)
	{
		printf("ERROR: trying to use a non declared variable\n");
		return;
	}


	/*
	 * add the variable to the list if kind_of_use is declaration
	 * if kind_of_use is declaration and variable is found throw error
	 */
	symbol_matrix_t *var_matrix_ptr = NULL;

	if (!(var_matrix_ptr = search_variable(variable)))
	{
		printf("variable does not exist yet\n");
		if (kind_of_use != DECLARATION)
		{
			printf("ERROR: trying to use a non declared variable\n");
			return;
		}

		var_matrix_ptr = malloc(sizeof(symbol_matrix_t));
		var_matrix_ptr->var_name = malloc(sizeof(char)*(strlen(variable)+1));

		strncpy(var_matrix_ptr->var_name, variable, strlen(variable));
		//var_matrix_ptr->var_name[strlen(variable)] = '\0';
		printf("declared %s\n\n", var_matrix_ptr->var_name);

		var_matrix_ptr->attribuition_line = -1;
		var_matrix_ptr->use_line          = -1;
		var_matrix_ptr->next              = NULL;
		symbol_matrix.declaration_line = line;

		symbol_matrix_t *var_parent = get_last_entry();
		var_parent->next = var_matrix_ptr;
		return;
	}
	else if (var_matrix_ptr && (kind_of_use == DECLARATION))
	{
		printf("ERROR: redeclaration of %s\n", variable);
		return;
	}

	switch (kind_of_use)
	{
		case ATTRIBUTION:
			printf("caught attrib on variable %s in line %d\n", 
					variable, line);
			var_matrix_ptr->attribuition_line = line;
			break;
		case USE_IN_FUNCTION:
			printf("caught use of variable %s in line %d\n", 
					variable, line);
			var_matrix_ptr->use_line = line;
			break;
	}

	return;
}


void show_matrix(void)
{
	printf("\n\nVariables that contain \"-1\" means was not used.\n");

	printf("+----------+-------------+--------+-----+\n");
	printf("| VARIABLE | DECLARATION | ATTRIB | USE |\n");

	symbol_matrix_t *symbol_matrix_ptr = &symbol_matrix;
	while (symbol_matrix_ptr)
	{
		printf("| %8s | %11d | %6d | %3d |\n", 
				symbol_matrix_ptr->var_name, 
				symbol_matrix_ptr->declaration_line,
				symbol_matrix_ptr->attribuition_line,
				symbol_matrix_ptr->use_line);
		printf("+----------+-------------+--------+-----+\n");

		symbol_matrix_ptr = symbol_matrix_ptr->next;
	}
}

int main(int argc, char **argv)
{
	if (!argv[1])
		yyin = stdin;
	else
	{
		printf("will get from file %s\n", argv[1]);
		char *fname = malloc(sizeof(char) * (strlen(argv[1]) + 1));
		strcpy(fname, argv[1]);
		fname[strlen(argv[1]) + 1] = '\0';

		printf("Opening file %s\n", fname);

		yyin = fopen(fname, "r");

		if (yyin == NULL)
		{
			printf("Could not open file, using stdin.\n");
			yyin = stdin;
		}
	}

	int ret = yyparse();
	if (yyin != stdin)
		fclose(yyin);

	show_matrix();

	return ret;
}

