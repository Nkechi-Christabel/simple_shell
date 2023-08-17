#include "shell.h"

/**
 * handle_exec - is a helper function to main
 *
 * @buffer: contains the command
 * @last_status: contains the last exit status
 * Return: status
 */
int handle_exec(char *buffer, int last_status)
{
	char **args, *command_path, *replaced_command;
	int i;
	int status;

	replaced_command = replace_variables(buffer, last_status);
	args = tokens(replaced_command);

	command_path = find_executable_path(args[0]);
	if (command_path == NULL)
	{
		perror("Command not found");
		free(buffer);
		free(args);
		free(replaced_command);
		return (-1);
	}

	status = call_fork(buffer, args, command_path);
	free(command_path);

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);

	free(args);
	free(replaced_command);

	return (status);
}

/**
 * handle_input - Handles user input and processing commands
 *
 * @current_dir: Current directory
 * @envp: Array of environment variable
 * Return: 0
 */
int handle_input(char *current_dir, char *envp[])
{
	char *buffer = NULL;
	int pipe = 1, num_aliases = 0, last_status = 0;
	Alias aliases[MAX_ALIASES];

	while (1 && pipe)
	{
		if (isatty(STDIN_FILENO) == 0)
			pipe = 0;
		write(STDOUT_FILENO, ":)$ ", 4);
		fflush(stdout);
		if (getline_inp(&buffer) == -1)
		{
			write(STDOUT_FILENO, "\n", 2);
			break;
		}
		if (buffer == NULL || strcmp(buffer, "") == 0)
		{
			free(buffer);
			continue;
		}
		else
		{
			exit_func(buffer);
			env_builtin(buffer, envp);
			if (strncmp(buffer, "setenv", 6) == 0)
				setenv_builtin(buffer, &envp);
			else if (strncmp(buffer, "unsetenv", 8) == 0)
				unsetenv_builtin(buffer, &envp);
			else if (strncmp(buffer, "alias", 5) == 0)
				alias_builtin(buffer, aliases, &num_aliases);
			else if (strncmp(buffer, "cd", 2) == 0)
				cd_builtin(buffer, &current_dir);
			else if  (strstr(buffer, "&&") != NULL)
				handle_logical_and(buffer, last_status);
			else if (strstr(buffer, "||") != NULL)
				handle_logical_or(buffer, last_status);
			else if (strstr(buffer, ";") != NULL)
				handle_semicolon(buffer, last_status);
			else
				last_status = handle_exec(buffer, last_status);
		}
	}
	free(buffer);
	return (0);
}

/**
 * main - create a custom shell
 * @envp: Array of environment variables
 * @argc: is the number of items in argv
 * @argv: is a N:LL terminated array of strings
 *
 * Return: 0 always (Success)
 */
int main(__attribute__((unused)) int argc, __attribute__((unused))
		char *argv[], char *envp[])
{
	char *home_dir = "/home/username", *current_dir = NULL;

	current_dir = strdup(home_dir);

	if (current_dir == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}

	handle_input(current_dir, envp);

	free(current_dir);
	return (0);
}
