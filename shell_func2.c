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
		exit(127);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("Error while waiting");
		free(buffer);
		free(command_path);
		free(args);
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1);
}

/**
 * cd_builtin - Handles the "cd" command
 * @buffer: Input buffer to extract command and argument
 * @current_dir: The current directory
 */
void cd_builtin(char *buffer, char **current_dir)
{
	char *token, *dir, *new_dir = NULL;

	new_dir = (char *)malloc(BUFFER_SIZE);

	if (new_dir == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = _strtok(buffer, " ");
	token = _strtok(NULL, " ");
	
	if (token == NULL || token[0] == '\0')
		dir = _getenv("HOME");

	else if (strcmp(token, "-") == 0)
		dir = *current_dir;
	else if (strcmp(token, "~") == 0)
		dir = _getenv("HOME");
	else
		dir = token;

	if (chdir(dir) == -1)
	{
		perror("cd");
		free(new_dir);
		return;
	}

	if (getcwd(new_dir, BUFFER_SIZE) == NULL)
	{
		perror("getcwd");
		free(new_dir);
		return;
	}
	*current_dir = new_dir;
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
