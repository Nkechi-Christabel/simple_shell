#include "shell.h"

/**
 * call_fork - calls the fork function
 *
 * @buffer: contains the command
 * @args: tokenized buffer
 * @command_path: contains the path
 *
 * Return: WEXITSTATUS(status)
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
		_exit(EXIT_FAILURE);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("Error while waiting");
		free(buffer);
		free(command_path);
		free(args);
		exit(EXIT_FAILURE);
	}
	return (WIFEXITED(status) ? WEXITSTATUS(status) : -1);
}

/**
 * handle_comment - checks for #
 *
 * @buffer: checks the command
 */
void handle_comment(char *buffer)
{
	char *comment_start = strchr(buffer, '#');

	if (comment_start != NULL)
		*comment_start = '\0';
}
/**
 * contains_only_spaces - checks for space
 *
 * @str: contains string
 * Return: !found_non_space;
 */
int contains_only_spaces(const char *str)
{
	int found_non_space = 0, i;

	for (i = 0; str[i]; i++)
	{
		if (!isspace((unsigned char)str[i]))
		{
			found_non_space = 1;
			break;
		}
	}
	return (!found_non_space);
}
