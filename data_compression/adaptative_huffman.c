/**
 * @file   adaptative_huffman.c
 * @Author Leonardo Korndorfer (leokorndorfer@gmail.com)
 * @date   September, 2010
 *
 * @brief  This file include functions for the adaptative huffman
 *
 * This implementation of huffman use the ASCII code for the chars.
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
	type_ahuffman_tree *root_node, *nyt_node, *new_node;

	printf("Enter - ahuffman_begin_tree\n");

	/* create new node with first char */
	ahuffman_new_node(NODE, 1, root_node);
	ahuffman_new_node(s[0], 1, new_node);
	ahuffman_new_node(NYT,  0, nyt_node);

	/* construct tree */
	root_node->l_child = new_node;
	root_node->r_child = nyt_node;

	new_node->parent = root_node;
	nyt_node->parent = root_node;

	ahuffman_tree = root_node;

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
int ahuffman_new_node(char c, int times, type_ahuffman_tree *node)
{
	printf("Enter - ahuffman_new_node\n");

	node = malloc(sizeof(node));
	node->parent  = NULL;
	node->l_child = NULL;
	node->r_child = NULL;
	node->value = c;
	node->times = times;

	printf("Exit- ahuffman_new_node\n");

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
	int str_size = strlen(s);

	/* this starts the tree with first char */
	ahuffman_begin_tree(s);

	for (i=1; i<str_size; i++)
	{
		if (s[i])
		{}
	}

	return GENERIC_SUCCESS;
}











