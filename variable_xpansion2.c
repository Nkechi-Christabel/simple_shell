#include "shell.h"

/**
 * echo_path - Replace other variables in the command
 *
 * @result: will stored the value of the command
 * @len: lenght of the command
 * @var_name_start: contains the command
 *
 * Return: result
 */
char *echo_path(char *result, size_t *len, const char *var_name_start)
{
	char *var_name;
	const char *var_name_end, *var_value;
	size_t var_name_length;
	char **env = environ;

	var_name_end = var_name_start;
	while (is_valid_variable_character(*var_name_end))
		var_name_end++;

	var_name_length = var_name_end - var_name_start;
	var_name = _strndup(var_name_start, var_name_length);

	for (; *env != NULL; env++)
	{
		if (_strncmp(*env, var_name, var_name_length) == 0 &&
				(*env)[var_name_length] == '=')
		{
			var_value = *env + var_name_length + 1;
			break;
		}
	}
	if (var_value != NULL)
		result = append_string(result, var_value, len);

	free(var_name);
	return (result);
}

/**
 * is_valid_variable_character - checks if character is valid
 *
 * @c: contains the char to be check
 * Return: return one of the conditions bellow
 */
int is_valid_variable_character(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
		    (c >= '0' && c <= '9') || c == '_');
}

/**
 * append_string - Append a string to the result buffer
 *
 * @result: accepts the string
 * @str: contains the string
 * @len: size of the string
 *
 * Return: result
 */
char *append_string(char *result, const char *str, size_t *len)
{
	size_t str_len = _strlen(str);

	result = realloc(result, *len + str_len + 1);
	if (!result)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	_strcpy(result + *len, str);
	*len += str_len;
	return (result);
}
/**
 * get_variable_name_length - Get the length of a variable name
 *
 * @var_name_start: contains the variable name
 *
 * Return: var_name_end - var_name_start
 */
size_t get_variable_name_length(const char *var_name_start)
{
	const char *var_name_end = var_name_start;

	while (is_valid_variable_character(*var_name_end))
	{
		var_name_end++;
	}

	return (var_name_end - var_name_start);
}
