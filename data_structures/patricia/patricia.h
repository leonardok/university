/*
 *  patricia.h
 *  patricia
 *
 *  Created by Leonardo Korndorfer on 6/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

/* patricia.h */

#ifndef __PATRICIA_H__
#define __PATRICIA_H__

#define MAX_IP_ENTRIES 50
#define TRUE  1
#define FALSE 0

#define BIT(key,bit_index) ((key >> (bit_index)) & 1)

typedef struct _node_t node_t;
struct _node_t {
        unsigned long int ip_numerical;
	
        char *ip_literal;
        char *hostname;
        char *other;
};

typedef struct _patricia_node_t patricia_node_t;
struct _patricia_node_t {
        node_t *node;
	
        unsigned char bit_number;
	unsigned char head;
	
        patricia_node_t *parent;
        patricia_node_t *left_child;
        patricia_node_t *right_child;
};

int patricia_search(node_t *, patricia_node_t **);
void convert_ip_lit2numeric (node_t*);
int  insert_on_patricia (node_t *);

/* patricia_file_parser.c functions */
int parse_file (char *);


#endif /* __PATRICIA_H__ */
