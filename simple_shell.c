#include "shell.h"

/**
 * tokens - Tokenize parameters from stdin
 * @buffer: where the tokens are stored
 *
 * Return: Pointer to tokenized parameters
 */
char **tokens(char *buffer)
{
	int argc = 0, i = 0;
	char *copy, *token;
	char **argv = NULL, *delim = " ";

	copy = strdup(buffer);
	token = strtok(buffer, delim);

	while (token)
	{
		token = strtok(NULL, delim);
		argc++;
	}

	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	token = strtok(copy, delim);

	while (token)
	{
		argv[i] = strdup(token);
		if (!argv[i])
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, delim);
		i++;
	}

	argv[argc] = NULL;
	free(copy);

	return (argv);
}


/**
 * main - create a custom shell
 *
 * Return: 0 always (Success)
 */
int main(void)
{
	char *buffer = NULL, **args;
	int status, i;
	pid_t pid;
	char *command_path;

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

char *find_command_path(const char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	char *full_path;

	while (dir != NULL)
	{
		full_path = (char *)malloc(strlen(dir) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return full_path;
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return NULL;
}
