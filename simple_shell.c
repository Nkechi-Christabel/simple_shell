#include "shell.h"

/**
 * handle_exec - is a helper function to main
 *
 * @buffer: contains the command
 */
void handle_exec(char *buffer)
{
	char **args, *command_path;
	int i;

	args = tokens(buffer);

	command_path = find_executable_path(args[0]);
	if (command_path == NULL)
	{
		perror("Command not found");
		free(buffer);
		free(args);
		return;
	}

	call_fork(buffer, args, command_path);
	free(command_path);

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);
	free(args);
}
/**
 * handle_input - Handles user input and processing commands
 * @buffer: contains the input
 * @current_dir: Current directory
 * @envp: Array of environment variable
 * Return: 0
 */

int handle_input(char *buffer, char *current_dir, char *envp[])
{
	char *command, *trim_cmd;
	size_t len;


	command = strtok(buffer, ";");
	while (command != NULL)
	{
		trim_cmd = command;
		while (*trim_cmd == ' ' || *trim_cmd == '\t' || *trim_cmd == '\n')
			trim_cmd++;
		len = strlen(trim_cmd);
		while (len > 0 && (trim_cmd[len - 1] == ' ' ||
			trim_cmd[len - 1] == '\t' || trim_cmd[len - 1] == '\n'))
		{
			trim_cmd[len - 1] = '\0';
			len--;
		}
		if (len > 0)
		{
			exit_func(trim_cmd);
			env_builtin(trim_cmd, envp);

			if (strncmp(trim_cmd, "setenv", 6) == 0)
				setenv_builtin(trim_cmd, &envp);
			else if (strncmp(trim_cmd, "unsetenv", 8) == 0)
				unsetenv_builtin(trim_cmd, &envp);
			else if (strncmp(trim_cmd, "cd", 2) == 0)
				cd_builtin(trim_cmd, &current_dir);
			else
				handle_exec(trim_cmd);
		}
		command = strtok(NULL, ";");
	}
	return (0);
}

/**
 * main - create a custom shell
 * @envp: Array of environment variables
 * @argc: is the number of items in argv
 * @argv: is a NULL terminated array of strings
 *
 * Return: 0 always (Success)
 */
int main(__attribute__((unused)) int argc, __attribute__((unused))
		char *argv[], char *envp[])
{
	char *home_dir = "/home/username", *current_dir = NULL;
	char *buffer = NULL;
	int pipe = 1;

	current_dir = strdup(home_dir);
	current_dir = strdup(home_dir);

	if (current_dir == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}

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
		handle_input(buffer, current_dir, envp);
	}
	free(buffer);
	free(current_dir);
	return (0);
}
