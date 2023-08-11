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
	char *buffer = NULL, **args;
	int status, i;
	pid_t pid;
	char *command_path;
	int pipe = 1;

	while (1 && pipe)
	{
		if (isatty(STDIN_FILENO) == 0)
			pipe = 0;

		write(STDOUT_FILENO, ":)$ ", 4);
		fflush(stdout);

		getline_inp(&buffer);
		exit_func(buffer);
		env_builtin(buffer, envp);
		args = tokens(buffer);

		command_path = find_command_path(args[0]);
		if (command_path == NULL)
		{
			perror("Command not found");
			free(buffer);
			free(args);
			continue;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("Error creating a child process");
			free(buffer);
			free(args);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execve(command_path, args, NULL);
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error while waiting");
			free(buffer);
			free(args);
			exit(EXIT_FAILURE);
		}

		free(command_path);

		for (i = 0; args[i] != NULL; i++)
			free(args[i]);
		free(args);
	}
	free(buffer);
	return (0);
}
