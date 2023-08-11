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
 * find_command_path - finds the command in path
 *
 * @command: command to search for
 *
 * Return: full_path
 */
char *find_command_path(const char *cmd)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	char *full_path, *abs_path;

	if (access(cmd, X_OK) == 0)
	{
		abs_path = strdup(cmd);
		if (abs_path == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		return (abs_path);
	}

	while (dir != NULL)
	{
		full_path = (char *)malloc(strlen(dir) + strlen(cmd) + 2);

		if (full_path == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		sprintf(full_path, "%s/%s", dir, cmd);
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
