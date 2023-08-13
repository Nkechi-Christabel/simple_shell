#include "shell.h"

/**
 * exit_func - exit the shell when exit is passed
 *
 * @buffer: contains the command
 *
 */
void exit_func(char *buffer)
{
	if (strncmp(buffer, "exit", 4) == 0)
	{
		int status;
		char *arg = buffer + 4;

		status = atoi(arg);

		free(buffer);
		exit(status);
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
 * find_path_env - finds the PATH environment variable
 *
 * Return: path or NULL if not found
 */
char *find_path_env(void)
{
	char *path = NULL;
	char **env = environ;

	for (; *env != NULL; env++)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			path = *env + 5;
			break;
		}
	}
	if (path == NULL)
	{
		perror("PATH environment variable not found");
		return (NULL);
	}
	return (strdup(path));
}


/**
 * find_executable_path - finds the full executable path for a command
 *
 * @cmd: command to search for
 *
 * Return: full_path or NULL if not found
 */
char *find_executable_path(const char *cmd)
{
	char *path_copy, *dir, *full_path, *abs_path;
	char *path = find_path_env();

	if (path == NULL)
		return (NULL);

	path_copy = strdup(path);
	dir = _strtok(path_copy, ":");
	if (access(cmd, X_OK) == 0)
	{
		abs_path = strdup(cmd);
		if (abs_path == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		free(path_copy);
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
		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = _strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * cd_builtin - Handles the "cd" command
 * @buffer: Input buffer to extract command and argument
 * @current_dir: The current directory
 */
void cd_builtin(char *buffer, char **current_dir)
{
	char *token, *dir, *new_dir = NULL;
	size_t max_len = 1024;

	new_dir = (char *)malloc(max_len);

	if (new_dir == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = _strtok(buffer, " ");
	token = _strtok(NULL, " ");

	if (token == NULL || token[0] == '\0' || strcmp(token, "-") == 0)
		dir = *current_dir;
	else
		dir = token;

	if (chdir(dir) == -1)
	{
		perror("cd");
		free(new_dir);
		return;
	}

	if (getcwd(new_dir, max_len) == NULL)
	{
		perror("getcwd");
		free(new_dir);
		return;
	}

	free(*current_dir);
	*current_dir = new_dir;
}
