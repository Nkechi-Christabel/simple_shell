#include "shell.h"

/**
 * trim_spaces - trim spaces in a string
 *
 * @str: contains the string
 *
 */
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

/**
 * print_error - prints error
 *
 * @shell_name: contains the shell name
 * @line: contains the no of lines
 * @command: contains the command name
 */
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

/**
 * reverseString - reverses a string
 *
 * @str: contains the string
 * @length: contains the lenght of the string
 */
void reverseString(char str[], int length)
{
	int start = 0;
	int end = length - 1;

	while (start < end)
	{
		char temp = str[start];

		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}
/**
 * intToString - converts int into string
 *
 * @str: contains the string
 * @num: contains the lenght
 *
 * Return: string
 */
char *intToString(int num, char *str)
{
	int isNegative = 0;
	int i = 0;

	if (num < 0)
	{
		isNegative = 1;
		num = -num;
	}

	while (num != 0)
	{
		str[i++] = num % 10 + '0';
		num = num / 10;
	}

	if (isNegative)
	{
		str[i++] = '-';
	}

	str[i] = '\0';

	reverseString(str, i);

	return (str);
}

/**
 * print_error2 - prints error
 *
 * @shell_name: contains the shell name
 * @command: contains the command name
 */
void print_error2(char *shell_name, char *command)
{
	write(STDERR_FILENO, shell_name, strlen(shell_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "0: ", 3);
	write(STDERR_FILENO, "cannot open ", 12);
	write(STDERR_FILENO, command, strlen(command));
	write(STDERR_FILENO, ": No such file\n", 15);
}
