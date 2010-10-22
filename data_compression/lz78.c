#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lz78.h"

dictionary_lz78_t dict_lz78[DICT_SIZE];


void dictionary_startup(void)
{
	int i;
	for (i = 0; i < DICT_SIZE; i++)
	{
		dict_lz78[i].times_used = 0;
		dict_lz78[i].word       = NULL;
	}

	return;
}

/* looks up for a sequence on the dictionary */
int dictionary_search(char *c)
{
	printf("dictionary_search - looking for character %s\n", c);
	
	int i;
	for (i = 0; i < DICT_SIZE; i++)
	{
		if (dict_lz78[i].word != NULL)
		{
			if (!strncmp(c, dict_lz78[i].word, strlen(dict_lz78[i].word)))
			{
				return i;
			}
		}
	}

	printf("dictionary_search - not in the dictionary\n");
	return -1;
}

int dictionary_add_entry(char *c)
{
	int i        = 0;
	int str_size = strlen(c);

	printf("dictionary_add_entry - adding %s to the dictionary\n", c);

	while ((dict_lz78[i].word != NULL) && (i < DICT_SIZE)) i++;

	if (i == DICT_SIZE)
		return -1;

	dict_lz78[i].word = malloc(sizeof(char) * (str_size + 1));
	strncpy(dict_lz78[i].word, c, str_size);
	dict_lz78[i].word[str_size] = '\0';

	return i;
}


int main(int argc, char **argv)
{
	char *c;
	int  i;
	int  dict_idx;

	printf("LZ78 algorithm\n");

	dictionary_startup();

	char *string = "compressao de dados usando o algoritmo lz78";
	c = string;
	while (1)
	{
		c++;
		if (*c == '\0')
			break;
		
		dict_idx = dictionary_search(c);
		if (dict_idx == -1)
		{
			char *word = malloc(sizeof(char) * 2);
			word[0] = *c;
			word[1] = '\0';
			dictionary_add_entry(word);
		}
		else
		{
			int word_size = strlen(dict_lz78[dict_idx].word) + 2;
			char *word = malloc(sizeof(char) * word_size);
			word[word_size - 1] = *c;
			word[word_size]     = '\0';
			dictionary_add_entry(word);
		}
	
		i++;
	}
	
}
