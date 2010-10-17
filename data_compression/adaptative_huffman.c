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

#include "return_codes.h"
#include "adaptative_huffman.h"

/* declaration of the global ahuffman tree */
type_ahuffman_tree *ahuffman_tree;


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


int check_tree_balance(void)
{

	return 1;
}


int get_node_weight(int height, type_ahuffman_tree *node)
{
	return 0;
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
int ahuffman_write_encoded(void)
{
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
		//printf("ahuffman_search - node is null\n");
		return NODE_NOT_FOUND;
	}
	//else
		//printf("ahuffman_search - node is %d\n", node->value);

	int ret;
	if (node->value == c)
		return path;

	if ((ret = ahuffman_search(node->l_child, c,((path << 1) | 0))) != NODE_NOT_FOUND)
	{
		//printf("\tahuffman_search - returned from left child\n");
		return ret;
	}

	if ((ret = ahuffman_search(node->r_child, c,((path << 1) | 1))) != NODE_NOT_FOUND)
	{
		//printf("\tahuffman_search - returned from right child\n");
		return ret;
	}

	//printf("ahuffman_search - exit\n");

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
int ahuffman_add_node(char c)
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

	ahuffman_new_node(c,    1, &new_node);
	ahuffman_new_node(NODE, 1, &root_node);
	
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
	int code = 0;
	int str_size = strlen(s);

	/* this starts the tree with first char */
	ahuffman_begin_tree(s);

	for (i=0; i<=str_size; i++)
	{
		printf("ahuffman_encode - encoding char '%c'\n", s[i]);

		/* if node not found, add it to the tree */
		if ((code = ahuffman_search(ahuffman_tree, s[i], 0xff)) == NODE_NOT_FOUND)
		{
			printf("ahuffman_encode - node not found, adding it\n");
			ahuffman_add_node(s[i]);

			/* get code again */
			code = ahuffman_search(ahuffman_tree, s[i], 0xff);
		}
		increment_counters(code);
		printf("code for %c is %x\n\n", s[i], code);
	}

	return GENERIC_SUCCESS;
}











