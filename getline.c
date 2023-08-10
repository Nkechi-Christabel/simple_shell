#include "shell.h"

/**
 * getline_inp - Gets command lines from standard input
 * @buffer: Where inputs are stored
 * @buffer_size: Size of the buffer
 */

void getline_inp(char **buffer)
{
	int input;
	size_t buffer_size = 0;

	input = getline(buffer, &buffer_size, stdin);
	if (input == -1)
	{
		perror("Error in getline");
		exit(EXIT_FAILURE);
	}

	if ((*buffer)[input - 1] == '\n')
		(*buffer)[input - 1] = '\0';

}
