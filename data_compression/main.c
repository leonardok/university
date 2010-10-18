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
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "return_codes.h"
#include "adaptative_huffman.h"

type_ahuffman_tree *ahuffman_tree;

int *output_file;
long int byte_buffer = 0xFFFFFFFF;
long int global_bytes_written = 0;

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
	printf("\t-f\tencode a string\n");
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
    int *fp;
    char buf[512];

	if (argc < 2 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
		usage();

	printf("this is the adaptative huffman. be welcome!\n");

	/* encode a string */
	if (!strcmp(argv[1], "-e"))
	{
		printf("the string to encode is \"%s\"\n", argv[2]);
		ahuffman_encode(argv[2], strlen(argv[2]));
	}
    else if (!strcmp(argv[1], "-f"))
    {
        printf("encode from file \"%s\"\n", argv[2]);
        output_file = open("./encoded_file.bin", O_WRONLY);

        if ((fp = open(argv[2], O_RDONLY)))
        {
            int bytes_read;
            while ((bytes_read = read(fp, buf, 512)) != EOF)
            {
                ahuffman_encode(buf, bytes_read);
            }
        }
    }


	return GENERIC_SUCCESS;
}

