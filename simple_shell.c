#include "shell.h"

/**
 * main - create a custom shell
 *
 * @argc: is the number of items in argv
 * @argv: is a NULL terminated array of strings
 * @env: contains the environment variables
 *
 */
int main(void)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	int input;
	pid_t pid;
	int status;
	char *args[1024];
	char *token;
	int arg_count = 0;

	while (1)
	{
		/*char *token;*/
		/* prints $  to the terminal*/
		write(STDOUT_FILENO, "$ ", 2);

		input = getline(&buffer, &buffer_size, stdin);
		if (input == -1)
		{
			perror("Error in getline");
			free(buffer);
			exit(EXIT_FAILURE);
		}

		if (buffer[input - 1] == '\n')
			buffer[input - 1] = '\0';

		token = strtok(buffer, " ");
		while (token != NULL && arg_count < 1023)
		{
			args[arg_count] = token;
			arg_count++;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;

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
	}

	free(buffer);
	return (0);
}
