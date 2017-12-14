#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool checkkey(char **key)
{
	char ascii_c = 0;
	for ( unsigned char i = 0; i < strlen(*key); ++i )
	{
		ascii_c = (char)*(*key+i);
		if (!((ascii_c >= 65 && ascii_c <= 90)||(ascii_c >= 97 && ascii_c <= 122)||(ascii_c >= 44 && ascii_c <= 46 )||(ascii_c == 58)||(ascii_c == 63)||(ascii_c == 95)||(ascii_c == 123)||(ascii_c == 125)||(ascii_c >= 48 && ascii_c <= 57)))
		{
			return false;
		}
	}
	return true;
}

// 
bool checkmessage(char **input_name, unsigned int i_key, unsigned int l_key)
{
	//printf("%s\n", *input_name);
	FILE *input_file;
	input_file = fopen(*input_name, "r");
	int c = 0;
	//printf("%u %u\n", i_key, l_key);
	fseek(input_file, i_key, SEEK_SET);
	while ( (c = fgetc(input_file)) != EOF )
	{
		if ( !((c >= 65&& c <= 90)||(c >= 97 && c <= 122)||(c == 32)||(c == 33||c == 34||c == 39||c == 40||c == 41||c == 59)||(c >= 44 && c <= 46)||(c == 58||c == 63||c == 95||c == 123||c == 125)||(c == 192||c == 194||c == 196||c == 224||c == 226||c == 228||c == 199||c == 131||c == 200||c == 201||c == 202||c == 203||c == 232||c == 233||c == 234||c == 235||c == 206||c == 207||c == 238||c == 239||c == 217||c == 219||c == 249||c == 251||c == 212||c == 214||c == 244||c == 246) || c == 10 ))
		{
			fclose(input_file);
			return false;
		}
		fseek(input_file, l_key-1, SEEK_CUR);
	}
	fclose(input_file);
	return true;
}
