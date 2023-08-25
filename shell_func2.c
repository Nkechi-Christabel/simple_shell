#include "shell.h"


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

	else if (_strcmp(token, "-") == 0)
		dir = *current_dir;
	else if (_strcmp(token, "~") == 0)
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
	*current_dir = _strdup(new_dir);
}

/**
 * handle_comment - checks for #
 *
 * @buffer: checks the command
 */
void handle_comment(char *buffer)
{
	char *comment_start = _strchr(buffer, '#');

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
		if (!_isspace((unsigned char)str[i]))
		{
			found_non_space = 1;
			break;
		}
	}
	return (!found_non_space);
}
