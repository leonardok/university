/*
 *  patricia_file_parser.c
 *  patricia
 *
 *  Created by Leonardo Korndorfer on 6/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "patricia.h"

extern patricia_node_t *patricia;

/*
** convert_ip_lit2numeric
**
** overview:
**   this function convert an IP in literal form (char*) to the numerical
**   form (long int).
**
** input:
**   1. node_t *
**
** output:
**   void
*/
void convert_ip_lit2numeric (node_t *node) {
        char c;
        char number[4];
        int  i, j = 0;
        int  ip_field_ptr = 0;
        int  ip[4];
	
        for (i=0; i<=strlen(node->ip_literal); i++) {
                c = node->ip_literal[i];
		
                if (c != '.' && c != '\0') number[j++] = c;
                else {
                        number[j] = '\0';
                        ip[ip_field_ptr] = (int) atoi(number);
                        if (ip_field_ptr != 0) {
                                node->ip_numerical = node->ip_numerical << (8);
                                node->ip_numerical = node->ip_numerical | ip[ip_field_ptr];
                        }
                        else
                                node->ip_numerical = ip[ip_field_ptr];
			
                        j = 0;
                        ip_field_ptr++;
                }
        }
}

/*
** convert_ip_lit2numeric
**
** overview:
**   this function will parse config files in order to build a simple PATRICIA
**   from the data found in file.
**
** input:
**   1. char *file_name
**
** output:
**   how manny nodes were created
*/
int parse_file (char *file_name) {
        int list_entry_counter = 0;
        int fp;
        char word[50];
	node_t *new_node;
	
        /* open file */
        if(!(fp = open(file_name, O_RDONLY))){
		printf("file could not be readed\n");
		exit(-1);
	}
	
        int i=0;
        int word_count = 0;
        while (read(fp, &word[i++], 1) > 0) {
                if (word[i-1] == ' ' || word[i-1] == '\n') {
                        /* end string */
                        word[i-1] = '\0';
                        word_count++;
			
                        switch (word_count % 3) {
                                case 0:
					new_node->hostname = malloc(sizeof(char) * strlen(word) + 1);
					strcpy(new_node->hostname, word);
					
                                        /* 
					** reset word count, create patricia_node and loose the new_node ref.
					*/
                                        word_count = 0;
					insert_on_patricia(new_node);
					
					new_node = NULL;
					
                                        break;
                                case 1:
					new_node             = malloc(sizeof(node_t));
					new_node->ip_literal = malloc(sizeof(char) * strlen(word) + 1);
					strcpy(new_node->ip_literal, word);
					
                                        convert_ip_lit2numeric(new_node);
                                        break;
					
                                case 2:
					new_node->other = malloc(sizeof(char) * strlen(word) + 1);
					strcpy(new_node->other, word);
					break;
                        }
                        i = 0;
			
			
                }
        }
	
        return list_entry_counter;
}
