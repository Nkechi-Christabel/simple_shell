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
		int status, i = 0, isNum;
		char *arg = buffer + 4;

		while (*arg == ' ')
			arg++;

		if (*arg)
		{
			isNum = 1;
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

		if(!isNum)
		{
			exit_invalid_argument_error(arg);
			free(buffer);
			exit(EXIT_FAILURE);
		}

		status = atoi(arg);
		if (status < 0)
		{
			exit_negative_status_error(status);
			free(buffer);
			exit(EXIT_FAILURE);
		}

		free(buffer);
		exit(status);
	}
}

/**
 * invalid_argument_error - Prints an error message for an invalid exit argument.
 *
 * @arg: The invalid argument passed to the exit command.
 */
void exit_invalid_argument_error(const char *arg)
{
	const char error_message[] = "Invalid exit argument: ";

	write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
	write(STDERR_FILENO, arg, strlen(arg));
	write(STDERR_FILENO, "\n", 1);
}

/**
 * negative_status_error - Prints an error message for a negative exit status.
 *
 * @status: The negative exit status.
 */
void exit_negative_status_error(int status)
{
	const char error_message[] = "Exit status cannot be negative: ";
	char *status_ptr,  status_str[12];
	int status_len = 0, temp_status = status;

	write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
	while (temp_status > 0)
	{
		temp_status /= 10;
		status_len++;
	}

	temp_status = status;
	status_ptr = status_str + status_len;
	*status_ptr = '\0';
	status_ptr--;

	while (temp_status > 0)
	{
		*status_ptr = '0' + (temp_status % 10);
		temp_status /= 10;
		status_ptr--;
	}
	
	write(STDERR_FILENO, status_str, strlen(status_str));
	write(STDERR_FILENO, "\n", 1);
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

