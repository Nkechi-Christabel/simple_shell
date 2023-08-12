#include "shell.h"

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
	char *buffer = NULL, **args, *command_path;
	int i, pipe = 1;

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
		exit_func(buffer);
		env_builtin(buffer, envp);
		args = tokens(buffer);

		command_path = find_executable_path(args[0]);
		if (command_path == NULL)
		{
			perror("Command not found");
			free(buffer);
			free(args);
			continue;
		}
		call_fork(buffer, args, command_path);
		free(command_path);

		for (i = 0; args[i] != NULL; i++)
			free(args[i]);
		free(args);
	}
	free(buffer);
	return (0);
}
