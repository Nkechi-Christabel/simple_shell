#include "shell.h"

/**
 * exit_func - exit the shell when exit is passed
 *
 * @buffer: contains the command
 *
 */
void exit_func(char *buffer)
{
	if (strncmp(buffer, "exit", 4) == 0)
	{
		int status, i = 0, isNum;
		char *arg = buffer + 4;

		while (*arg == ' ')
			arg++;

		if (*arg)
		{
			isNum = 1;
			while (arg[i])
			{
				if (arg[i] < '0' || arg[i] > '9')
				{
					isNum = 0;
					break;
				}
				i++;
			}
		}

		if(!isNum)
		{
			exit_invalid_argument_error(arg);
			free(buffer);
			exit(EXIT_FAILURE);
		}

		status = atoi(arg);
		if (status < 0)
		{
			exit_negative_status_error(status);
			free(buffer);
			exit(EXIT_FAILURE);
		}

		free(buffer);
		exit(status);
	}
}

/**
 * invalid_argument_error - Prints an error message for an invalid exit argument.
 *
 * @arg: The invalid argument passed to the exit command.
 */
void exit_invalid_argument_error(const char *arg)
{
	const char error_message[] = "Invalid exit argument: ";

	write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
	write(STDERR_FILENO, arg, strlen(arg));
	write(STDERR_FILENO, "\n", 1);
}

/**
 * negative_status_error - Prints an error message for a negative exit status.
 *
 * @status: The negative exit status.
 */
void exit_negative_status_error(int status)
{
	const char error_message[] = "Exit status cannot be negative: ";
	char *status_ptr,  status_str[12];
	int status_len = 0, temp_status = status;

	write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
	while (temp_status > 0)
	{
		temp_status /= 10;
		status_len++;
	}

	temp_status = status;
	status_ptr = status_str + status_len;
	*status_ptr = '\0';
	status_ptr--;

	while (temp_status > 0)
	{
		*status_ptr = '0' + (temp_status % 10);
		temp_status /= 10;
		status_ptr--;
	}
	
	write(STDERR_FILENO, status_str, strlen(status_str));
	write(STDERR_FILENO, "\n", 1);
}


