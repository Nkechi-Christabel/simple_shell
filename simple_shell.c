#include "shell.h"

/**
 * env_builtin - Print the current environment variables
 * @env: Array of environment variables
 */
void env_builtin(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
    }
}

/**
 * main - create a custom shell
 * @env: The environment variables of the current process
 * Return: 0 always (Success)
 */
int main(__attribute__((unused)) int argc, __attribute__((unused))
		char *argv[], char *envp[])
{
	char *buffer = NULL, **args;
	int status, i;
	pid_t pid;

	while (1)
	{
		write(STDOUT_FILENO, ":)$ ", 4);
		fflush(stdout);

		getline_inp(&buffer);
		if (strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(buffer, "env") == 0)
			env_builtin(envp);

		args = tokens(buffer);
		pid = fork();
		if (pid == -1)
		{
			perror("Error creating a child process");
			free(buffer);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execve(args[0], args, NULL);
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error while waiting");
			exit(EXIT_FAILURE);
		}
		for (i = 0; args[i] != NULL; i++)
			free(args[i]);
		free(args);
	}
	free(buffer);
	return (0);
}
