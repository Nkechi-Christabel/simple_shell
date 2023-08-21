#include "shell.h"

void trim_spaces(char *str)
{
    int start = 0, end = strlen(str) - 1, i;
    
    while (isspace(str[start]))
        start++;
    
    while (end > start && isspace(str[end]))
        end--;
    
    for (i = start; i <= end; i++)
        str[i - start] = str[i];
    
    str[end - start + 1] = '\0';
}

void print_error(char *shell_name, int *line, char *command)
{
	char number_str[20];
	intToString((*line), number_str);

	write(STDERR_FILENO, shell_name, strlen(shell_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO,  number_str, strlen(number_str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command, strlen(command));
	write(STDERR_FILENO, ": not found\n", 12);
}

void reverseString(char str[], int length) {
    int start = 0;
    int end = length - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* intToString(int num, char* str) {
    int isNegative = 0;
    int i = 0;

    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    while (num != 0) {
        str[i++] = num % 10 + '0';
        num = num / 10;
    }

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    reverseString(str, i);

    return str;
}

void print_error2(char *shell_name, char *command)
{
	write(STDERR_FILENO, shell_name, strlen(shell_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "0: ", 3);
	write(STDERR_FILENO, "cannot open ", 12);
	write(STDERR_FILENO, command, strlen(command));
	write(STDERR_FILENO, ": No such file\n", 15);
}

/**
 * env_builtin - Print the current environment variables
 * @envp: Array of environment variables
 * @buffer: contains the command
 *
void env_builtin(char *buffer, char **envp)
{
	int i = 0;
	size_t len;

	if (strcmp(buffer, "env") == 0)
	{
		while (envp[i] != NULL)
		{
			len = strlen(envp[i]);

			write(STDOUT_FILENO, envp[i], len);
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
	}
}

**
 * find_path_env - finds the PATH environment variable
 *
 * Return: path or NULL if not found
 *
char *find_path_env(void)
{
	char *path = NULL;
	char **env = environ;

	for (; *env != NULL; env++)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			path = *env + 5;
			break;
		}
	}
	if (path == NULL)
	{
		perror("PATH environment variable not found");
		return (NULL);
	}
	return (strdup(path));
}


**
 * find_executable_path - finds the full executable path for a command
 *
 * @cmd: command to search for
 *
 * Return: full_path or NULL if not found
 *
char *find_executable_path(const char *cmd)
{
	char *path_copy, *dir, *full_path, *abs_path;
	char *path = find_path_env();

	if (path == NULL)
		return (NULL);

	path_copy = strdup(path);
	dir = _strtok(path_copy, ":");
	if (access(cmd, X_OK) == 0)
	{
		abs_path = strdup(cmd);
		if (abs_path == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		free(path_copy);
		return (abs_path);
	}
	while (dir != NULL)
	{
		full_path = (char *)malloc(strlen(dir) + strlen(cmd) + 2);
		if (full_path == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = _strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
>>>>>>> 853449fdb4f8ae7b57d634ab9716bb2e31e58fe5
}*/

