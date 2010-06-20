#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patricia.h"
#include "pash.h"

/*
** I am denying myself to write a description for this function!!
*/
void pash_help(void) {
        printf("Availiable pash commands:\n");
        printf("\tcreate");
        printf("\tcreates a new node in the patricia\n");
        printf("\tdelete");
        printf("\tdeletes a node from the trie\n");
        printf("\tsearch");
        printf("\tquery the trie after node information\n");
        printf("\tquit");
        printf("\tplease don't!!\n");
        printf("\t\n");
}

/*
** pash_create_node
**
** overview:
**   get information from command line of the new node it is supposed to create
**   and then call patricia api to create a new node.
**
** input:
**   1. void
**
** output:
**   void
*/
void pash_create_node(void) {
        char ip[16];
        char hostname[40];
        char type[16];
	
        printf("IP:\t");
        scanf("%s", ip);
	
        printf("type (insert host_name or subnet_name): ");
        scanf("%s", type);
	
        printf("Hostname:\t");
        scanf("%s", hostname);
	
	node_t *new_node = NULL;
	new_node = malloc(sizeof(node_t));
	new_node->ip_literal = malloc(sizeof(char)*(strlen(ip)+1));
	new_node->hostname   = malloc(sizeof(char)*(strlen(hostname)+1));
	new_node->other      = malloc(sizeof(char)*(strlen(type)+1));
	
	strcpy(new_node->ip_literal, ip);
	strcpy(new_node->hostname,   hostname);
	strcpy(new_node->other,      type);
	
	convert_ip_lit2numeric(new_node);
	if(insert_on_patricia(new_node) == TRUE)
		printf("node added successfully\n");
	else 	printf("node already on PATRICIA\n");
	
	printf("\n");
	
        return;
}

/*
** pash_search_node
**
** overview:
**   get information from command line and search for a node within the PATRICIA
**
** input:
**   1. void
**
** output:
**   void
*/
void pash_search_node(void) {
        char ip[16];
	patricia_node_t *p;
		
        printf("IP: "); scanf("%s", ip);
        
        node_t *node = malloc(sizeof(node_t));
        node->ip_literal = malloc(sizeof(char)*(strlen(ip)+1));
        strcpy(node->ip_literal, ip);
        
	convert_ip_lit2numeric(node);
	
        printf("will search now\n");
        if(patricia_search(node, &p)) {
		printf("node info:\n");
		printf("\tIP:\t\t%s\n", p->node->ip_literal);
		printf("\thostname:\t%s\n", p->node->hostname);
	}
        else printf("node not found!!\n");
        return;
}

/*
** invoke_pash
**
** overview:
**   this function calls the pash interpreter.
**
** input:
**   1. void
**
** output:
**   void
*/
void invoke_pash(){
	printf("Welcome to PASH (Patricia Shell)\n");
	printf("\n");
        printf("For a list of commands use the \"help\" command\n");
	char command[100];
        while (TRUE) {
                printf("> ");
                scanf("%s", command);
		
                if (!strcmp(command, "help")){
                        pash_help();
                }
                if (!strcmp(command, "search")){
                        pash_search_node();
                }
                if (!strcmp(command, "create")){
                        pash_create_node();
                }
                if (!strcmp(command, "delete")){
                        printf("command not implemented yet\n");;
                }
                if (!strcmp(command, "quit")){
                        break;
                }
		
        }	
	
}