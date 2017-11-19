#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "options.h"
#include "checkascii.h"
#include "cipher.h"

int main(int argc, char *argv[])
{
	char *input_name = 0;
	char *output_name = 0;
	char *key = 0;
	char *mode = 0;
	char *key_lenght = 0;

	unsigned char opt_mode = 0;

	readopt(argc, argv, &input_name, &output_name, &key, &mode, &key_lenght);
	opt_mode = checkopt(&input_name, &output_name, &key, &mode, &key_lenght);
	printf("opt_mode : %d\n", opt_mode);
	if ( opt_mode == 0 )
	{
		xor_cipher(&input_name, &key, &output_name);
	}
	return 0;
}
