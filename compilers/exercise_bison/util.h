#ifndef __UTIL_H__
#define __UTIL_H__

enum
{
	DECLARATION,
	ATTRIBUTION,
	USE_IN_FUNCTION
} use;

typedef struct symbol_matrix_s symbol_matrix_t;
struct symbol_matrix_s
{
	char *var_name;
	int  declaration_line;
	int  attribuition_line;
	int  use_line;

	symbol_matrix_t *next;
};

void add_to_matrix(char *, int, int);
void usage(void);

#endif
