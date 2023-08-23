#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * _strncmp - compare two strings up to a specified number of characters
 * @str1: the first string
 * @str2: the second string
 * @n: the maximum number of characters to compare
 *
 * Return: an integer less than, equal to, or greater than zero if str1 is found,
 * respectively, to be less than, to match, or be greater than str2.
 */

int _strncmp(const char *str1, const char *str2, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		if (str1[i] != str2[i])
			return ((int)(str1[i] - str2[i]));
	}

        if (str1[i] == '\0')
		return 0;

	return 0;
}
