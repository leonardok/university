#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patricia.h"
#include "pash.h"

/*
 ** global variables declaration
 */
patricia_node_t *patricia;


int main (int argc, const char * argv[]) {
	if (argc < 2) {
		printf("I need a file like einstein.txt to proceed\n");
		return -1;
	}
	
	char *file_name = malloc(strlen(argv[1])*sizeof(char) + 1);
	strcpy(file_name, argv[1]);

	/* parse file, build our base patricia */
	parse_file(file_name);
	
	invoke_pash();
	
	/* will get here only when we are getting out */
	return TRUE;
}
