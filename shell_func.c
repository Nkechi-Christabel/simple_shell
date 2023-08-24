#include "shell.h"

/**
 * exit_func - exit the shell when exit is passed
 *
 * @buffer: contains the command
 * @shell_name: points to the shell name
 * @line: is the line count
 *
 */
void exit_func(char *buffer, char *shell_name, int *line)
{
	if (_strncmp(buffer, "exit", 4) == 0)
	{
		int status, i = 0, isNum = 1;
		char *arg = buffer + 4;

		if (*arg == '\0')
		{
			free(buffer);
			exit(0);
		}
		while (*arg == ' ')
			arg++;
		if (*arg)
		{
			while (arg[i])
			{
				if (arg[i] < '0' || arg[i] > '9')
				{
					isNum = 0;
					break;
				}
				i++;
			}
		}
		if (!isNum)
		{
			print_error3(shell_name, line, arg);
			free(buffer);
			exit(2);
		}
		status = _atoi(arg);
		if (status < 0)
		{
			print_error3(shell_name, line, arg);
			free(buffer);
			exit(2);
		}
		free(buffer);
		exit(status);
	}
}

/**
 * print_error3 - Prints an error message for an invalid exit argument.
 *
 * @command: The invalid argument passed to the exit command
 * @shell_name: points to the shell name
 * @line: is the line count
 */
void print_error3(char *shell_name, int *line, char *command)
{
	char number_str[20];

	intToString((*line), number_str);

	write(STDERR_FILENO, shell_name, _strlen(shell_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO,  number_str, _strlen(number_str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "exit: ", 6);
	write(STDERR_FILENO, "Illegal number: ", 16);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, "\n", 1);
}

/**
 * env_builtin - Print the current environment variables
 *
 * @buffer: contains the command
 * @envp: Array of environment variables
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
 * _getenv- finds a vairable in environment variable
 *
 * @name: variable to search for
 *
 * Return: *env + name_len + 1
 */
char *_getenv(const char *name)
{
	char **env = environ;
	size_t name_len;

	if (name == NULL || env == NULL)
		return (NULL);

	name_len = _strlen(name);
	for (; *env != NULL; env++)
	{
		if (_strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=')
		{
			return (*env + name_len + 1);
		}
	}

	return (NULL);
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
	char *path;

	if (access(cmd, X_OK) == 0)
	{
		abs_path = _strdup(cmd);
		if (abs_path == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		return (abs_path);
	}
	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);
	path_copy = _strdup(path);
	dir = _strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = (char *)malloc(_strlen(dir) + _strlen(cmd) + 2);
		if (full_path == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		_strcpy(full_path, dir);
		_strcat(full_path, "/");
		_strcat(full_path, cmd);
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
