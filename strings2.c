#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

char *_strchr(const char *str, int ch)
{
	while (*str != '\0')
	{
		if (*str == ch)
		{
			return ((char *)str);
		}
		str++;
	}

	if (ch == '\0')
	{
		return ((char *)str);
	}
    
	return (NULL);
}

char *_strndup(const char *str, size_t n)
{
	size_t length = strlen(str), i;
	char *new_str;

	if (length > n)
		length = n;
    
	new_str = (char *)malloc(length + 1);
	if (new_str == NULL)
		return (NULL);
    
	for (i = 0; i < length; i++)
	{
		new_str[i] = str[i];
	}
	new_str[length] = '\0';

	return (new_str);
}

size_t _strcspn(const char *str, const char *reject)
{
	size_t count = 0;

	while (str[count] != '\0')
	{
		if (strchr(reject, str[count]) != NULL)
			break;
		count++;
	}
	return (count);
}
