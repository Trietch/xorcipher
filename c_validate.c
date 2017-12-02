#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "cipher.h"
#include "checkascii.h"

void get_c_key(char **c_key, char **key_lenght, char **input_name, bool print_result)
{
	char *output_name = "IO/temp";
	char key[] = "";
	FILE *c_key_file;
	c_key_file = fopen("c_key", "r");
	unsigned int alphabet[71] = {44,45,46,48,49,50,51,52,53,54,55,56,57,58,63,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,95,90,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,125};
	unsigned char index = 0;
	unsigned char key_n = 0;
	for ( int i = 0; i < atoi(*key_lenght); ++i )
	{
		if ( i > 0 )
		{
			index = atoi(*key_lenght)-i;
		}
		key_n = 0;
		for (int j = 0; j < 71; ++j )
		{
			key[0] = alphabet[j];
			xor_cipher(input_name, key, &output_name);
			if ( checkmessage(&output_name, i, atoi(*key_lenght)) == true )
			{
				key_n++;
				if ( key_n > 1)
				{
					c_key[i] = realloc(c_key[i], key_n*sizeof(char));
				}
				c_key[index][key_n-1] = alphabet[j];
			}
		}
		fseek(c_key_file, 0, SEEK_SET);
	}
	fclose(c_key_file);
	if ( print_result == true )
	{
		for ( int i = 0; i < atoi(*key_lenght); ++i )
		{
			printf("[");
			for ( int j = 0; j < strlen(c_key[i]); ++j )
			{
				printf("%c", c_key[i][j]);
			}
			printf("]");
		}
		printf("\n");
	}
}

void combination_arrays(char **key_lenght, int n, int *cursor, char **key_list, char **c_key)
{	
	char *temp = NULL;
	temp = malloc(atoi(*key_lenght)*sizeof(char*));
	
	unsigned int cursor_in_cursor = atoi(*key_lenght)-1; // LuL
	for ( int i = 0; i < n; ++i )
	{
		temp = malloc(atoi(*key_lenght)*sizeof(char*));
		for ( int j = 0; j < atoi(*key_lenght); ++j )
		{
			temp[j] = c_key[j][cursor[j]];
			key_list[i][j] = c_key[j][cursor[j]];
		}
		
		strcpy(key_list[i], temp);
		free(temp);

		cursor[cursor_in_cursor]++;
		while ( i < n-1 && cursor[cursor_in_cursor] == strlen(c_key[cursor_in_cursor]) )
		{
			cursor[cursor_in_cursor] = 0;
			cursor_in_cursor--;
			cursor[cursor_in_cursor]++;
		}
		cursor_in_cursor = atoi(*key_lenght)-1;
	}
	free(temp);
}

char** c_validate(char **input_name, char **key_lenght, char **key_list, unsigned int *key_list_n, bool print_result)
{
	/*
	 * Liste les caracteres possibles pour la clé
	 */

	char **c_key = NULL;
	c_key = (char**)calloc(atoi(*key_lenght),sizeof(char*));
	for ( int i = 0; i < atoi(*key_lenght); ++i )
	{
		c_key[i] = (char*)calloc(1,sizeof(char));
	}

	get_c_key(c_key, key_lenght, input_name, print_result);

	/*
	 *	Combinaison des clés avec les caracteres possibles
	 */

	unsigned int n = 1;
	for ( int i = 0; i < atoi(*key_lenght); ++i )
	{
		n = n*(int)strlen(c_key[i]);
	}
	int *cursor = NULL;
	cursor = calloc(atoi(*key_lenght), sizeof(int));
	
	key_list = malloc(n*sizeof(char**));
	for ( int i = 0; i < n; ++i )
	{
		key_list[i] = malloc(atoi(*key_lenght)*sizeof(char*));
	}

	combination_arrays(key_lenght, n, cursor, key_list, c_key);
	/*	
	for ( int i = 0; i < n; ++i )
	{
		printf("%s ", key_list[i]);
	}
	printf("\n");
	*/	
	for ( int i = 0; i < atoi(*key_lenght); ++i )
	{
		free(c_key[i]);
	}
	free(c_key);
	
	free(cursor);

	*key_list_n = n;
	return key_list;
}
