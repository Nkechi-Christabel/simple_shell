#include "shell.h"

/**
 * _strpbrk - function searches for the first character in the str string
 * that matches any character from the accept string
 *
 * @str: contains the string
 * @accept: contains string to be searched for
 *
 * Return: (char *)str
 */
char *_strpbrk(const char *str, const char *accept)
{
	while (*str != '\0')
	{
		if (_strchr(accept, *str) != NULL)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

/**
 * _isspace - checks for space
 * @c: contains the string
 *
 * Return: ture or false
 */
int _isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' ||
			c == '\f' || c == '\r');
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
