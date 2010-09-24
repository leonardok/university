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
void usage(void)
{
	printf("USAGE:\n");
	printf("\t-e\tencode a string\n");
	printf("\t-d\tencode a bitstream\n");
	exit(0);
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
int main(int argc, char **argv)
{
	if (argc < 2 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
		usage();

	/* encode a string */
	if (!strcmp(argv[1], "-e"))
	{
		ahuffman_encode(argv[2]);
	}

    printf("this is the adaptative huffman. be welcome!\n");
	printf("the string to encode is ");

	

	return GENERIC_SUCCESS;
}

