#include "shell.h"

/**
 * _strtok - Acts like strtok function by breaking strings into word
 * @str: The string to tokenize
 * @delim: The delimiter or separator
 *
 * Return: Each 
 */
char *_strtok(char *str, const char *delim)
{
	char *start, *end;
	static char *token = NULL;

	if (str != NULL)
		token = str;
	else if (token == NULL)
		return NULL;

	start = token;
	end = strpbrk(start, delim);

	if (end != NULL)
	{
		*end = '\0';
		token = end + 1;
	}
	else
		token = NULL;

	return start;
}

/**
 * tokens - Tokenize parameters from stdin
 * @buffer: where the tokens are stored
 *
 * Return: Pointer to tokenized parameters
 */
char **tokens(char *buffer)
{
	int argc = 0, i = 0;
	char *copy, *token, **argv = NULL, *delim = " ";

	copy = strdup(buffer);
	token = _strtok(buffer, delim);

	while (token)
	{
		token = _strtok(NULL, delim);
		argc++;
	}

	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	token = _strtok(copy, delim);

	while (token)
	{
		argv[i] = strdup(token);
		if (!argv[i])
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		token = _strtok(NULL, delim);
		i++;
	}

	argv[argc] = NULL;
	free(copy);

	return (argv);
}

