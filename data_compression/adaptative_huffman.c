/**
 * @file   adaptative_huffman.c
 * @Author Leonardo Korndorfer (leokorndorfer@gmail.com)
 * @date   September, 2010
 *
 * @brief  This file include functions for the adaptative huffman
 *
 * This implementation of huffman use the ASCII code for the chars.
 * 
 * TODO		1. add log lib from operational_systems/schedsim_round_robin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "return_codes.h"
#include "adaptative_huffman.h"

/* declaration of the global ahuffman tree */
extern type_ahuffman_tree *ahuffman_tree;
extern long int byte_buffer;


/**
 * TODO write this header
 *
 * @name    Example API Actions
 * @brief   Example actions available.
 * @ingroup example
 *
 * This API provides certain actions as an example.
 *
 * @param [in] repeat  Number of times to do nothing.
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 * Example Usage:
 * @code
 *    example_nada(3); // Do nothing 3 times.
 * @endcode
 */
int ahuffman_begin_tree(char *s)
{
	type_ahuffman_tree *nyt_node;

	printf("Enter - ahuffman_begin_tree\n");

	/* create new node with first char */
	ahuffman_new_node(NYT,  0, &nyt_node);

	/* construct tree */
	ahuffman_tree = nyt_node;

	printf("Exit - ahuffman_begin_tree\n");

	return GENERIC_SUCCESS;
}


/**
 * TODO write this header
 *
 * @name    Example API Actions
 * @brief   Example actions available.
 * @ingroup example
 *
 * This API provides certain actions as an example.
 *
 * @param [in] repeat  Number of times to do nothing.
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 * Example Usage:
 * @code
 *    example_nada(3); // Do nothing 3 times.
 * @endcode
 */
int ahuffman_rotate_tree(void)
{
	return GENERIC_SUCCESS;
}


/**
 * @name    exchange_node
 * @brief   Exchange two nodes
 *
 * This function will do the following steps:
 *     1. get parent of node_a
 *     2. get parent of node_b
 *     3. check if parents are the same, if they are just change parent child pointers
 *        and return.
 *     4. check weather the nodes to be exchanged are left or right child of parents
 *     5. change parent_a child to node_b and parent_b to node_a
 *     6. change node pointers.
 *
 * @param [in] type_ahuffman_tree  Node 'a' to be exchanged
 * @param [in] type_ahuffman_tree  Node 'b' to be exchanged
 *
 * @retval GENERIC_SUCCESS  Successfully did nothing.
 * @retval GENERIC_FAIL     Oops, did something.
 */
int exchange_nodes(type_ahuffman_tree **node_a, type_ahuffman_tree **node_b)
{
	type_ahuffman_tree *parent_a  = (*node_a)->parent;
	type_ahuffman_tree *parent_b  = (*node_b)->parent;
	
	if (parent_a == parent_b)
	{
		type_ahuffman_tree *node_tmp = parent_a->r_child;
		
		parent_a->r_child = parent_a->l_child;
		parent_a->l_child = node_tmp;
		
		return NODE_CHANGED;
	}
	
	if (parent_a->l_child == *node_a)
		parent_a->l_child = *node_b;
	else 
		parent_a->r_child = *node_b;
	
	if (parent_b->l_child == *node_b)
		parent_b->l_child = *node_a;
	else 
		parent_b->r_child = *node_a;
	
	(*node_b)->parent = parent_a;
	(*node_a)->parent = parent_b;

    log_write("exchange_nodes - changed \'%c\' by \'%c\'", 1, LOG_DEBUG, 
            (*node_a)->value, (*node_b)->value);
	
	return NODE_CHANGED;
}


int check_recursive(type_ahuffman_tree *node_to_check, 
		    type_ahuffman_tree *node_ptr, 
		    int node_depth, int depth_we_are)
{
    int ret;
	/* we are not interested in exchanging nodes deeper than we are */
	if (!node_ptr || (depth_we_are >= node_depth) || (node_ptr->value == NYT))
		return TREE_BALANCED;
	
	ret = check_recursive(node_to_check, node_ptr->l_child, node_depth, depth_we_are+1);
    if (ret == NODE_CHANGED)
        return NODE_CHANGED;

	log_write("check_recursive - check node %c weight %x AND pivot node %c weight %x",
			1, LOG_DEBUG,
			node_to_check->value, node_to_check->weight,
			node_ptr->value, node_ptr->weight);

	if ((node_ptr->weight < (node_to_check->weight + 1)) 
			&& (node_to_check->parent != node_ptr))
	{
		log_write("check_recursive - have to change", 1, LOG_DEBUG);
		return exchange_nodes(&node_to_check, &node_ptr);
	}

	ret = check_recursive(node_to_check, node_ptr->r_child, node_depth, depth_we_are+1);
    if (ret == NODE_CHANGED)
        return NODE_CHANGED;
	
	return GENERIC_SUCCESS;
}


/**
 * @name    check_node_balance
 * @brief   Check balance for last node.
 *
 * This function will check if the last node to be updated is respecting the
 * huffman tree properties.
 *
 * @param [in] void
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 */
int check_node_balance(type_ahuffman_tree *node)
{
	type_ahuffman_tree *node_ptr = node;
	int node_depth = 0;
	
	/* get node deph */
	while (node_ptr != ahuffman_tree)
	{
		node_depth++;
		node_ptr = node_ptr->parent;
	}
	
	check_recursive(node, ahuffman_tree, node_depth, 0);
	
	return GENERIC_SUCCESS;
}


int check_tree_balance(type_ahuffman_tree *node)
{
	if (node)
	{
		check_tree_balance(node->l_child);
		check_tree_balance(node->r_child);
		
		check_node_balance(node);
	}
	
	return GENERIC_SUCCESS;
}


/**
 * TODO write this header
 *
 * @name    Example API Actions
 * @brief   Example actions available.
 * @ingroup example
 *
 * This API provides certain actions as an example.
 *
 * @param [in] repeat  Number of times to do nothing.
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 * Example Usage:
 * @code
 *    example_nada(3); // Do nothing 3 times.
 * @endcode
 */
int ahuffman_new_node(char c, int weight, type_ahuffman_tree **new_node)
{
	//printf("ahuffman_new_node - new node is %d\n", c);

	type_ahuffman_tree *node = *new_node;

	node = malloc(sizeof(type_ahuffman_tree));
	node->parent  = NULL;
	node->l_child = NULL;
	node->r_child = NULL;
	node->value  = c;
	node->weight = weight;
	
	*new_node = node;

	//printf("Exit- ahuffman_new_node\n");

	return GENERIC_SUCCESS;
}


/**
 * TODO write this header
 *
 * @name    Example API Actions
 * @brief   Example actions available.
 * @ingroup example
 *
 * Buffer is a long int, with the first 4 bytes filled with 0xFF.
 * 1. Get the position of the 0xFFFFFFFF in the buffer_long_int
 * 2. Get the code size and check if it will overflow the 4 bytes of an int
 *    1.a. if it overflow, write the byte on the file and store the rest in
 *         a new buffer.
 *    1.b. if doesnt overflow write code into the byte and wait for next
 * 
 * 
 *
 * @param [in] repeat  Number of times to do nothing.
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 */
int ahuffman_write_encoded_to_file(int code, int *fp)
{
    long int tmp_buffer  = byte_buffer;
    int tmp_code         = code;
    int buffer_used_bits = 0;

    log_write("get buffer size - %x", 1, LOG_INFO, (byte_buffer & 0xFFFFFFFF));
    while (tmp_buffer != 0xFFFFFFFF)
    {
        tmp_buffer >>= 1;
        buffer_used_bits++;
        //log_write("buffer_used_bits++", 1, LOG_INFO);
    }

    log_write("ahuffman_write_encoded_to_file - used %d of the buffer",
            0, LOG_INFO, buffer_used_bits);
    log_write("ahuffman_write_encoded_to_file - code is %x",
            0, LOG_INFO, byte_buffer);
    while (tmp_code != 0xFF)
    {
        if (buffer_used_bits >= 31)
        {
            //write into the file
            //write_buffer((int) (byte_buffer & 0xFFFFFFFF));
            printf("ahuffman_write_encoded_to_file - buffer print \'%lx\'\n",
                    (byte_buffer & 0xFFFFFFFF)); 

            byte_buffer = 0xFFFFFFFF;
            buffer_used_bits = 0;
            continue;
        }
        byte_buffer = ((byte_buffer << 1) | ((tmp_code & 1)));
        buffer_used_bits++;
        
        tmp_code >>= 1;
    }
    
	return GENERIC_SUCCESS;
}


/**
 * @name    ahuffman_search
 * @brief   Search for a node
 *
 * This function will search for a node and return its path if found. If not 
 * found, return a negative number defined in return codes.
 *
 * @param [in] node Node where to begin the search
 * @param [in] c    The searched character
 * @param [in] path Path untill here. This is for the recursiveness
 *
 * @retval NODE_NOT_FOUND  Return not found if do not find :-)
 * @retval Node Path       Return the node path if finds it
 *
 * TODO
 * it seems that if the path is "0000" a wrong thing will happen. it will return
 * 0 as the path for the found node.
 *
 */
int ahuffman_search(type_ahuffman_tree *node, char c, int path)
{
	//printf("ahuffman_search - enter\n");

	if (!node)
	{
		log_write("ahuffman_search - node is null", 2, LOG_DEBUG);
		return NODE_NOT_FOUND;
	}
	//else
		//printf("ahuffman_search - node is %d\n", node->value);

	int ret;
	if (node->value == c)
		return path;

	if ((ret = ahuffman_search(node->l_child, c, path)) != NODE_NOT_FOUND)
	{
		log_write("ahuffman_search - returned from loeft child", 2, LOG_DEBUG);
		return ((ret <<= 1) | 0);
	}

	if ((ret = ahuffman_search(node->r_child, c, path)) != NODE_NOT_FOUND)
	{
		log_write("ahuffman_search - returned from right child", 2, LOG_DEBUG);
		return ((ret <<= 1) | 1);
	}

	log_write("ahuffman_search - exit", 2, LOG_DEBUG);


	return NODE_NOT_FOUND;
}


/**
 * TODO write this header
 *
 * @name    Example API Actions
 * @brief   Example actions available.
 * @ingroup example
 *
 * This API provides certain actions as an example.
 *
 * @param [in] repeat  Number of times to do nothing.
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 * Example Usage:
 * @code
 *    example_nada(3); // Do nothing 3 times.
 * @endcode
 */
int ahuffman_add_node(char c, type_ahuffman_tree **new_node_ptr)
{
	type_ahuffman_tree *new_node  = NULL;
	type_ahuffman_tree *nyt_node  = NULL;
	type_ahuffman_tree *root_node = NULL;
	type_ahuffman_tree *parent_node = NULL;

	int path      = 0;
	int path_size = 0;


	/**
	 * the algorithm says that we add a new node besides
	 * NYT, adding a new root for both
	 */
	path = (ahuffman_search(ahuffman_tree, NYT, 0xFF));
	//printf("\tahuffman_add_node - path for NYT is %x\n", path);

	/* if this is true is that the tree has no members yet */
	if (path == 0xFF)
	{
		//printf("\tahuffman_add_node - adding first element\n");
		nyt_node = ahuffman_tree;

		ahuffman_new_node(c,    0, &new_node);
		ahuffman_new_node(NODE, 0, &root_node);

		root_node->l_child = nyt_node;
		root_node->r_child = new_node;

		nyt_node->parent = root_node;
		new_node->parent = root_node;

		ahuffman_tree = root_node;
		*new_node_ptr = new_node;

		return GENERIC_SUCCESS;
	}

	/* point NYT node to tree root */
	nyt_node = ahuffman_tree;

	/* walk on the tree to find the real NYT, according to path */
	while (path && (path != 0xFF))
	{
		//printf("\tahuffman_add_node - path bit is %x\n", (path & 1));

		if ((path & 1) == 0)
			nyt_node = nyt_node->l_child;
		else
			nyt_node = nyt_node->r_child;

		path >>= 1;
		path_size++;
	}

	ahuffman_new_node(c,    0, &new_node);
	ahuffman_new_node(NODE, 0, &root_node);
	
	parent_node = nyt_node->parent;

	if (parent_node->l_child == nyt_node)
	{
		//printf("\tahuffman_add_node - root will be placed at left\n");
		parent_node->l_child = root_node;
	}
	else
	{
		//printf("\tahuffman_add_node - root will be placed at left\n");
		parent_node->r_child = root_node;
	}

	root_node->parent  = parent_node;
	root_node->l_child = nyt_node;
	root_node->r_child = new_node;
	//printf("\tahuffman_add_node - new node is %d\n", new_node->value);

	nyt_node->parent = root_node;
	new_node->parent = root_node;
	
	*new_node_ptr = new_node;

	return GENERIC_SUCCESS;
}


/**
 * TODO write this header
 *
 * @name    Example API Actions
 * @brief   Example actions available.
 * @ingroup example
 *
 * This API provides certain actions as an example.
 *
 * @param [in] repeat  Number of times to do nothing.
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 * Example Usage:
 * @code
 *    example_nada(3); // Do nothing 3 times.
 * @endcode
 */
void increment_counters(int path)
{
	type_ahuffman_tree *node = ahuffman_tree;

	while (path && (path != 0xFF))
	{
		node->weight++;
		if ((path & 1) == 0)
			node = node->l_child;
		else
			node = node->r_child;

		path >>= 1;
	}
	node->weight++;
}


/**
 * TODO write this header
 *
 * @name    Example API Actions
 * @brief   Example actions available.
 * @ingroup example
 *
 * This API provides certain actions as an example.
 *
 * @param [in] repeat  Number of times to do nothing.
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 * Example Usage:
 * @code
 *    example_nada(3); // Do nothing 3 times.
 * @endcode
 */
int ahuffman_encode(char *s)
{
	int i;
	long int code = 0;
	int str_size = strlen(s);

	/* this starts the tree with first char */
	ahuffman_begin_tree(s);

	for (i=0; i<=str_size; i++)
	{
		log_write("ahuffman_encode - encoding char '%c'", 0, LOG_INFO, s[i]);

		/* if node not found, add it to the tree */
		if ((code = ahuffman_search(ahuffman_tree, s[i], 0xff)) == NODE_NOT_FOUND)
		{
			log_write("ahuffman_encode - node not found, adding it", 0, LOG_INFO);
			type_ahuffman_tree *new_node;

            code = ahuffman_search(ahuffman_tree, NYT, 0xff);
            ahuffman_write_encoded_to_file(code, NULL);

			ahuffman_add_node(s[i], &new_node);
			
			/* if we have added a node we need to check if this node
			 * is respecting the huffman tree */
			check_node_balance(new_node);
		}
		
		/* check if the huffman tree properties are been respected */
		check_tree_balance(ahuffman_tree);

		/* get code again */
		code = ahuffman_search(ahuffman_tree, s[i], 0xff);
        ahuffman_write_encoded_to_file(code, NULL); 
		
		increment_counters(code);
		log_write("code for %c is %x", 0, LOG_INFO, s[i], code);
	}

	return GENERIC_SUCCESS;
}











