#include "shell.h"

/**
 * replace_variables - Handles command '$' and "$$"
 * @command: The command line to check
 * @status: Keeps track of the exit status
 *
 * Return: The expanded variable
 */
char *replace_variables(const char *command, int status)
{
	char *result = NULL;
	const char *ptr = command;
	size_t len = 0;

	while (*ptr)
	{
		if (*ptr == '$')
		{
			if (*(ptr + 1) == '?')
			{
				result = replace_exit_status(result, &len, status);
				ptr += 2;
				continue;
			}
			else if (*(ptr + 1) == '$')
			{
				result = replace_process_id(result, &len);
				ptr += 2;
				continue;
			}
		}

		result = realloc(result, len + 2);
		if (!result)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		result[len++] = *ptr++;
	}

	result = finalize_result(result, len);
	return (result);
}

/**
 * replace_exit_status - Replaces "$?" with the exit status
 * @result: The result string being constructed
 * @len: Pointer to the length of the result string
 * @status: The exit status to be replaced
 *
 * Return: Pointer to the updated result string
 */
char *replace_exit_status(char *result, size_t *len, int status)
{
	int num_digits = 1, temp_status = status, i;

	 while (temp_status >= 10)
	 {
		 temp_status /= 10;
		 num_digits++;
	 }

	 result = realloc(result, *len + num_digits + 1);

	 if (!result)
	 {
		 perror("Memory allocation failed");
		 exit(EXIT_FAILURE);
	 }

	 temp_status = status;

	 for (i = num_digits - 1; i >= 0; i--)
	 {
		 result[*len + i] = '0' + (temp_status % 10);
		 temp_status /= 10;
	 }

	 *len += num_digits;

	 return (result);
}

/**
 * replace_process_id - Replaces "$$" with the current process ID
 * @result: The result string being constructed
 * @len: Pointer to the length of the result string
 *
 * Return: Pointer to the updated result string
 */
char *replace_process_id(char *result, size_t *len)
{
	    int pid = getpid(), num_digits = 1, temp_pid = pid, i;

	    while (temp_pid >= 10)
	    {
		    temp_pid /= 10;
		    num_digits++;
	    }

	    result = realloc(result, *len + num_digits + 1);
	    if (!result)
	    {
		    perror("Memory allocation failed");
		    exit(EXIT_FAILURE);
	    }

	    temp_pid = pid;

	    for (i = num_digits - 1; i >= 0; i--)
	    {
		    result[*len + i] = '0' + (temp_pid % 10);
		    temp_pid /= 10;
	    }

	    *len += num_digits;
	    return (result);
}

/**
 * finalize_result - Finalizes the result string by adding null-termination
 * @result: The result string to be finalized
 * @len: The length of the result string
 *
 * Return: Pointer to the finalized result string
 */
char *finalize_result(char *result, size_t len)
{
	result = realloc(result, len + 1);

	if (!result)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	result[len] = '\0';
	return (result);
}

