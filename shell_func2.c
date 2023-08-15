#include "shell.h"

/**
 * call_fork - calls the fork function
 *
 * @buffer: contains the command
 * @args: tokenized buffer
 * @command_path: contains the path
 *
 */

int call_fork(char *buffer, char **args, char *command_path)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error creating a child process");
		free(buffer);
		free(command_path);
		free(args);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(command_path, args, NULL);
		perror("Error executing command");
		free(buffer);
		free(command_path);
		free(args);
		exit(EXIT_FAILURE);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("Error while waiting");
		free(buffer);
		free(command_path);
		free(args);
		exit(EXIT_FAILURE);
	}
	return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

/**
 * setenv_builtin - Set or modify an environment variable
 * @buffer: contains the command
 * @envp: Pointer to array of environment variables
 */
void setenv_builtin(char *buffer, char ***envp)
{
	char *token, *var_name, *var_value;

	token = _strtok(buffer, " ");
	token = _strtok(NULL, " ");

	if (token == NULL)
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 30);
		return;
	}

	var_name = token;
	token = _strtok(NULL, " ");

	if (token == NULL)
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 30);
		return;
	}

	var_value = token;

	if (setenv(var_name, var_value, 1) == -1)
		perror("setenv");
	else
		*envp = environ;
}

/**
 * unsetenv_builtin - Unset an environment variable
 * @buffer: contains the command
 * @envp: Pointer to array of environment variables
 */
void unsetenv_builtin(char *buffer, char ***envp)
{
	char *token;

	token = _strtok(buffer, " ");
	token = _strtok(NULL, " ");

	if (token == NULL)
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 25);
		return;
	}

	if (unsetenv(token) == -1)
		perror("unsetenv");
	else
		*envp = environ;
}

