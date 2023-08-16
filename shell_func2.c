#include "shell.h"

/**
 * call_fork - calls the fork function
 *
 * @buffer: contains the command
 * @args: tokenized buffer
 * @command_path: contains the path
 *
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
		exit(EXIT_FAILURE);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("Error while waiting");
		free(buffer);
		free(command_path);
		free(args);
		exit(EXIT_FAILURE);
	}
	return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

/**
 * setenv_builtin - Set or modify an environment variable
 * @buffer: contains the command
 * @envp: Pointer to array of environment variables
 */
void setenv_builtin(char *buffer, char ***envp)
{
	char *token, *var_name, *var_value;

	token = _strtok(buffer, " ");
	token = _strtok(NULL, " ");

	if (token == NULL)
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 30);
		return;
	}

	var_name = token;
	token = _strtok(NULL, " ");

	if (token == NULL)
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 30);
		return;
	}

	var_value = token;

	if (setenv(var_name, var_value, 1) == -1)
		perror("setenv");
	else
		*envp = environ;
}

/**
 * unsetenv_builtin - Unset an environment variable
 * @buffer: contains the command
 * @envp: Pointer to array of environment variables
 */
void unsetenv_builtin(char *buffer, char ***envp)
{
	char *token;

	token = _strtok(buffer, " ");
	token = _strtok(NULL, " ");

	if (token == NULL)
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 25);
		return;
	}

	if (unsetenv(token) == -1)
		perror("unsetenv");
	else
		*envp = environ;
}

/**
 * replace_variables - Handles command '$' and "$$"
 * @command: The command line to check
 * @status: Keeps track of the exit status
 *
 * Return: The expanded variable
 */
char *replace_variables_$(const char *command, int status) {
    char *result = NULL;
    const char *ptr = command;
    size_t len = 0;
    char var_name[256]; // Maximum variable name length

    while (*ptr) {
        if (*ptr == '$') {
            if (*(ptr + 1) == '?') {
                char status_str[16];
                snprintf(status_str, sizeof(status_str), "%d", status);
                size_t status_len = strlen(status_str);
                result = realloc(result, len + status_len + 1);
                if (!result) {
                    perror("Memory allocation failed");
                    exit(EXIT_FAILURE);
                }
                strcpy(result + len, status_str);
                len += status_len;
                ptr += 2; // Skip past the '$?' sequence
                continue;
            } else if (*(ptr + 1) == '$') {
                // Replace $$ with the current process ID
                char pid_str[16];
                snprintf(pid_str, sizeof(pid_str), "%d", getpid());
                size_t pid_len = strlen(pid_str);
                result = realloc(result, len + pid_len + 1);
                if (!result) {
                    perror("Memory allocation failed");
                    exit(EXIT_FAILURE);
                }
                strcpy(result + len, pid_str);
                len += pid_len;
                ptr += 2;
                continue;
            }
        }

        result = realloc(result, len + 2);
        if (!result) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        result[len++] = *ptr++;
    }

    result = realloc(result, len + 1);
    if (!result) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    result[len] = '\0';

    return result;
}

