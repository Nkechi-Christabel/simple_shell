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
	if (!argv)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	token = strtok(copy, delim);

	while (token)
	{
		argv[i] = strdup(token);
		if (!argv[i])
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
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
	int status, i;
	pid_t pid;

	while (1)
	{
		write(STDOUT_FILENO, ":)$ ", 4);
		fflush(stdout);

		getline_inp(&buffer);
		if (strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
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
