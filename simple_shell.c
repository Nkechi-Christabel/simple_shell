#include "shell.h"

/**
 * tokens - Tokenize parameters from stdin
 * @buffer: where the tokens are stored
 *
 * Return: Pointer to tokenized parameters
 */
char **tokens(char *buffer)
{
	int argc = 0, i = 0;
	char *copy, *token;
	char **argv = NULL, *delim = " ";

	copy = strdup(buffer);
	token = strtok(buffer, delim);

	while (token)
	{
		token = strtok(NULL, delim);
		argc++;
	}

	argv = malloc(sizeof(char *) * (argc + 1));
	token = strtok(copy, delim);

	while (token)
	{
		argv[i] = strdup(token);
		token = strtok(NULL, delim);
		i++;
	}

	argv[argc] = NULL;
	free(copy);

	return (argv);
}


/**
 * main - create a custom shell
 *
 * Return: 0 always (Success)
 */
int main(void)
{
	char *buffer = NULL, **args;
	size_t buffer_size = 0;
	int status, i;
	pid_t pid;

	while (1)
	{
		write(STDOUT_FILENO, ":)$ ", 4);
		getline_inp(buffer, &buffer_size);

		args = tokens(buffer);
		pid = fork();
		if (pid == -1)
		{
			perror("Error creating a child process");
			free(buffer);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execve(args[0], args, NULL);
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error while waiting");
			exit(EXIT_FAILURE);
		}
		for (i = 0; args[i] != NULL; i++)
			free(args[i]);
		free(args);
	}
	free(buffer);
	return (0);
}
