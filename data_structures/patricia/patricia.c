/*
**  patricia.c
**  patricia
**
**  Created by Leonardo Korndorfer on 6/19/10.
**  Copyright 2010. All rights reserved.
**
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "patricia.h"



/*
** global variables declaration
*/
extern patricia_node_t *patricia;



/*
** get_first_different_key
**
** overview:
**   will find the first bit different of key1 from key2
**
** input:
**   1. unsigned long key1 - first key
**   2. unsigned long key2 - duh!
**
** output:
**   first bit different between the two keys
*/
int get_first_different_key (unsigned long key1, unsigned long key2) {
        unsigned long xor = key1 ^ key2;
        
        int i;
        for (i=31; i > 0; i--){
		int bit = BIT(xor, (i));		
                if (bit == 1)
                        break;
        }
        return i;
}

/*
** patricia_search
**
** overview:
**   patricia search will try to find an node. it is also used to find a proper
**   place to put a new node, so it comes with one aditional argument, that is
**   the "last" node.
**
** input:
**   1. node_t *key_node    - node we are looking for
**   2. patricia_node_t **p - this is the reference for the last node to be
**                            walked in. it will return the address.
**
** output:
**   TRUE for success and FALSE for failure
*/
int patricia_search(node_t *key_node, patricia_node_t **p) {
	assert(patricia);
	
	/* variable declariations */
	patricia_node_t *patricia_node_ptr = patricia;
	patricia_node_t *last_node         = NULL;
		
	/*
	** patricia suggests that we check the node->bit_number in order to
	** decide wheather to go left or right. it also says that 
	** and stop when current_node->node->ip_numerical == key_node->ip_numerical
	*/
	
	/* do loop to walk on the tree */
	while (TRUE) {
		/* 
		** if current node has the same ip_numerical as the key_node then
		** we can return TRUE and the object found. no point of going all way long.
		*/
		if (patricia_node_ptr->node->ip_numerical == key_node->ip_numerical) {
			*p = patricia_node_ptr;
			return TRUE;
		}
		
		/*
		** is current node the head? heads are marked with ->head == 1
		** if head we can only go to the left child. if not head we can go
		** both sides.
		*/
		if (!last_node && patricia_node_ptr->head) {
			/* update last_node to next loop */
			last_node = patricia_node_ptr;
			
			patricia_node_ptr = patricia_node_ptr->left_child;
			
			continue;
		}
				
		/*
		** we have to stop walking on the tree when 
		** current_node->bit_number <= last_node->bit_number
		*/
		if (last_node && patricia_node_ptr->bit_number <= last_node->bit_number)
			break;
		
		/* update last_node to next loop */
		last_node = patricia_node_ptr;
		
		/*
		** check key_node->ip_numerical on bit[patricia_node_ptr->bit_number]
		** to decide what side we will go next
		*/
		int bit;
		if ((bit = BIT(key_node->ip_numerical, patricia_node_ptr->bit_number)) == 0)
			patricia_node_ptr = patricia_node_ptr->left_child;
		else
			patricia_node_ptr = patricia_node_ptr->right_child;

		
		
	/* end walking while */
	}
	
	/* p will be always the last_node, not the new one */
	*p = last_node;

	return FALSE;
}

/*
** insert_on_patricia
**
** overview:
**   insert a new node into the patricia tree
**
** input:
**   1. node_t *key_node - node to insert on the patricia
**
** output:
**   TRUE for success and FALSE for failure
*/
/*
** insert a new node into the patricia tree
*/
int insert_on_patricia (node_t *key_node) {
	patricia_node_t *patricia_new_node;
	
	/*
	** first of all we will contruct the new node with some of it information
	** and then decide what to do with it.
	*/
	patricia_new_node = (patricia_node_t *) malloc(sizeof(patricia_node_t));		
	patricia_new_node->parent      = NULL;
	patricia_new_node->left_child  = patricia_new_node;
	patricia_new_node->right_child = NULL;
	patricia_new_node->bit_number  = 0;
	patricia_new_node->head        = 0;
	
	/* copy all struture in memory of key_node to patricia->node */
	patricia_new_node->node = malloc(sizeof(node_t));
	memcpy(patricia_new_node->node, key_node, sizeof(node_t));
	
	
        /*
	** if patricia is NULL we can put the new node into the head without
	** worries.
	*/
	if (!patricia) {
		patricia_new_node->head = 1;
		
		/* set patricia to the new pointer patricia_ptr */
		patricia = patricia_new_node;		
		return TRUE;		
	}
	
	/*
	** if not than we need to walk through the patricia to find where to
	** place our new node. this is done by the patricia_search function
	**
	** if our patricia search returns TRUE we have to free our new node, as
	** our search have found it already on the tree.
	*/
	else {
		patricia_node_t *p;
		patricia_node_t *s;
		
		if (!patricia_search(key_node, &p)) s = p->left_child;
		else {
			free(patricia_new_node->node);
			free(patricia_new_node);
			
			return FALSE;
		}

		/* get new node bit number */
		patricia_new_node->bit_number = get_first_different_key(key_node->ip_numerical, 
									p->node->ip_numerical);
		
		/* walk through the tree in order to get where the new node will be placed */
		while ((s->bit_number > p->bit_number) && 
		       (s->bit_number < patricia_new_node->bit_number)) {
			if (BIT(patricia_new_node->node->ip_numerical, s->bit_number) == 0)
				s = s->left_child;
			else 
				s = s->right_child;
		}
		
		/* adjust links on the new node */
		if (BIT(patricia_new_node->node->ip_numerical, patricia_new_node->bit_number) == 0) {
			patricia_new_node->left_child  = patricia_new_node;
			patricia_new_node->right_child = s;
		}
		else {
			patricia_new_node->left_child  = s;
			patricia_new_node->right_child = patricia_new_node;
		}
		
		/* add new node on patricia */
		if ((p->left_child == s) && (BIT(key_node->ip_numerical,p->bit_number) == 0))
			p->left_child = patricia_new_node;
		else
			p->right_child = patricia_new_node;

		
	}
	return TRUE;
}