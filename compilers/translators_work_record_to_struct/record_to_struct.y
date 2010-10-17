/**
 * this is a pascal to C "register"
 *
 * "register" is the pascall "struct" equivalent
 * this is an example of a record declaration:
 *
 * type tipo_liv=record
 *     titulo:integer
 *     autor:string
 * end;
 * var livro:tipo_liv;
 *
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define C_INT "int"
#define C_CHR "char"
#define C_FLT "float"
#define C_CHR_PTR "char *"

struct variable_declaration_s
{
	char *name;
	char *type;
};
typedef struct variable_declaration_s variable_declaration_type;

struct record_s
{
	char *name;
	variable_declaration_type variables[30];
};
typedef struct record_s record_type;

record_type record;

int variable_idx = 0;
variable_declaration_type variables[30];

void usage(void);
void declare_record(char*);
void declare_variable(char *, char*);
%}

%union {
	char  *value_string;
	int   value_int;
	float value_float;
}

%token <value_string> T_RESERVED_WORD
%token <value_string> T_IDENTIFIER
%token <value_string> T_VARIABLE_TYPE
%token <value_int>    T_INTEGER 
%token <value_float>  T_FLOAT
%token <value_string> T_RECORD 
%token T_TYPE
%token T_END
%token T_VAR
%token T_ARRAY
%token T_EOL

%start statement 

%%
statement: record
         | variable_declaration
	 ;

record: T_TYPE T_IDENTIFIER '=' T_RECORD variable_declaration {declare_record($2);}
      ;

variable_declaration: T_IDENTIFIER ':' T_VARIABLE_TYPE ';' variable_declaration {declare_variable($1, $3);}
                    | T_END ';'
                    ;
%%

extern FILE *yyin;


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

void declare_record(char *record_name)
{
	record.name = malloc(sizeof(char) * (strlen(record_name) + 1));
	strcpy(record.name, record_name);

	return;
}

void declare_variable(char *var_name, char *var_type){
	if (!strcmp(var_type, "integer"))
	{
		record.variables[variable_idx].type = malloc(sizeof(char) * (strlen(C_INT) + 1));
		strcpy(record.variables[variable_idx].type, C_INT);
	}
	if (!strcmp(var_type, "string"))
	{
		record.variables[variable_idx].type = malloc(sizeof(char) * (strlen(C_CHR_PTR) + 1));
		strcpy(record.variables[variable_idx].type, C_CHR_PTR);
	}

	record.variables[variable_idx].name = malloc(sizeof(char) * (strlen(var_name) + 1));
	strcpy(record.variables[variable_idx].name, var_name);

	variable_idx++;

	return;
}

int main(int argc, char **argv) 
{
	if ((argc < 5) && ((strcmp("-i", argv[1]) != 0) || (strcmp("-o", argv[3]) != 0)))
		usage();

	if (!strcmp(argv[2], "null"))
		yyin = stdin;
	else 
	{
		char *fname = malloc(sizeof(char) * (strlen(argv[2]) + 1));
		strcpy(fname, argv[2]);
		fname[strlen(argv[2]) + 1] = '\0';

		printf("Opening file %s\n", fname);

		yyin = fopen(fname, "r");

		if (yyin == NULL) 
		{
			printf("Could not open file, using stdin.\n");
			yyin = stdin;
		}
	}

	/* enable bison debug */
	//yydebug = 3;

	int ret = yyparse();
	if (yyin != stdin)
		fclose(yyin);

	int i=0;
	FILE *out = fopen(argv[4], "w+");
	fputs("struct {\n", out);
	for (i=0; i<variable_idx; i++)
	{
		char *buff = malloc(sizeof(char) * (strlen(record.variables[i].type) + strlen(record.variables[i].name) + 5));
		sprintf(buff, "\t%s %s;\n", record.variables[i].type, record.variables[i].name);
		fputs(buff, out);
	}
	char *buff = malloc(sizeof(char) * (strlen(record.name) + 2));
	sprintf(buff, "} %s;\n", record.name);
	fputs(buff, out);
	free(buff);

	fclose(out);

	return ret;
}

int yyerror(const char* errstr) {
	printf("Error: %s \n", errstr);
	return -1;
}
