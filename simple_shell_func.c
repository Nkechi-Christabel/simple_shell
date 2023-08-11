#include "shell.h"

/**
 * exit_func - exit the shell when exit is passed
 *
 * @buffer: contains the command
 *
 */
void exit_func(char *buffer)
{
	if (strcmp(buffer, "exit") == 0)
	{
		free(buffer);
		exit(EXIT_SUCCESS);
	}
}

/**
 * env_builtin - Print the current environment variables
 * @envp: Array of environment variables
 * @buffer: contains the command
 */
void env_builtin(char *buffer, char **envp)
{
	int i = 0;
	size_t len;

	if (strcmp(buffer, "env") == 0)
	{
		while (envp[i] != NULL)
		{
			len = strlen(envp[i]);

			write(STDOUT_FILENO, envp[i], len);
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
	}
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
 * find_command_path - finds the command in path
 *
 * @command: command to search for
 *
 * Return: full_path
 */
char *find_command_path(const char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	char *full_path, *abs_path;

	if (access(command, X_OK) == 0)
	{
		abs_path = strdup(command);
		if (abs_path == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		return (abs_path);
	}

	while (dir != NULL)
	{
		full_path = (char *)malloc(strlen(dir) + strlen(command) + 2);

		if (full_path == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
