#include "shell.h"


/**
 * tokens - Tokenize parameters from stdin
 * @buffer: where the tokens are stored
 *
 * Return: Pointer to tokenized parameters
 */
char **tokens(char *buffer, char *delim)
{
	char *copy, **argv = NULL;
	int argc = count_tokens(buffer, delim);
	int i = 0, j, token_start, token_length;

	copy = strdup(buffer);

	argv = malloc(sizeof(char *) * (argc + 1));

	if (!argv)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	for (j = 0; j < argc; j++)
	{
		while (copy[i] && strchr(delim, copy[i]) != NULL)
			i++;

		token_start = i;

		while (copy[i] && strchr(delim, copy[i]) == NULL)
			i++;

		token_length = i - token_start;
		argv[j] = malloc(token_length + 1);

		if (!argv[j])
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}

		strncpy(argv[j], copy + token_start, token_length);
		argv[j][token_length] = '\0';
	}

	argv[argc] = NULL;
	free(copy);

	return argv;
}


/**
 * count_tokens - Count the number of tokens in a buffer
 * @buffer: Input buffer
 * @delim: Delimiter string
 *
 * Return: Number of tokens
 */
int count_tokens(char *buffer, char *delim)
{
	int count = 0, i;
	int in_token = 0;

	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (strchr(delim, buffer[i]) != NULL)
		{
			if (in_token)
			{
				in_token = 0;
				count++;
			}
		}

		else
		{
			if (!in_token)
				in_token = 1;
		}
	}

	if (in_token)
		count++;

	return (count);
}
