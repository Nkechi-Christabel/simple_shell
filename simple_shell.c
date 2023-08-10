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
	char *token;
	char **argv = NULL;

	token = strtok(buffer, " ");

	while (token)
	{
		token = strtok(NULL, " ");
		argc++;
	}

	argv = malloc(sizeof(char *) * (argc + 1));
	token = strtok(buffer, " ");

	while (token)
	{
		argv[i] = token;
		token = strtok(NULL, " ");
		i++;
	}

	argv[argc] = NULL;

	return (argv);
}


/**
 * main - create a custom shell
 *
 * @argc: is the number of items in argv
 * @argv: is a NULL terminated array of strings
 * @env: contains the environment variables
 *
 */
int main(void)
{
	char *buffer = NULL, **args;
	size_t buffer_size = 0;
	int input, status, i;
	pid_t pid;

	while (1)
	{
		/* prints $  to the terminal*/
		write(STDOUT_FILENO, "NB$ ", 4);

		input = getline(&buffer, &buffer_size, stdin);
		if (input == -1)
		{
			perror("Error in getline");
			free(buffer);
			exit(EXIT_FAILURE);
		}

		if (buffer[input - 1] == '\n')
			buffer[input - 1] = '\0';

		
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
			printf("Executing command: %s\n", args[0]);

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
