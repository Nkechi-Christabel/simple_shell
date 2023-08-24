
#include "shell.h"

/**
 * _putenv - Sets a new or modify an environment variable
 * @str: The name of the environment variable to set or modify
 *
 * Return: 0 if successful or -1 if not
 */

int _putenv(const char *str)
{
	char *env_str = strdup(str), *equal_sign;
	int result;

	if (env_str == NULL)
	{
		perror("Memory allocation error");
		return (-1);
	}

	equal_sign = _strchr(env_str, '=');

	if (equal_sign == NULL)
	{
		free(env_str);
		return (-1);
	}

	*equal_sign = '\0';

	result = _setenv(env_str, equal_sign + 1, 1);

	free(env_str);
	return (result);
}

/**
 * _setenv - Set or modify an environment variable
 * @name: Name of the environment variable
 * @value: Value to be assigned to the environment variable
 * @overwrite: Flag indicating whether to overwrite an existing variable
 *
 * Return: A new "name=value" string and adding it to the environment.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	size_t len;
	char *new_var;
	int result;

	if (name == NULL || name[0] == '\0' || _strchr(name, '=') != NULL)
		return (-1);

	if (!overwrite && _getenv(name) != NULL)
		return (0);

	len = _strlen(name) + _strlen(value) + 2;

	new_var = (char *)malloc(len);

	if (new_var == NULL)
		return (-1);

	_strcpy(new_var, name);
	_strcat(new_var, "=");
	_strcat(new_var, value);

	result = putenv(new_var);

	free(new_var);
	return (result);
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

	if (_setenv(var_name, var_value, 1) == -1)
		perror("setenv");
	else
		*envp = environ;
}

/**
 * _unsetenv - Unset an environment variable
 * @name: Name of the environment variable to unset
 *
 * Return: 0 always (Success)
 */
int _unsetenv(const char *name)
{
	int index = -1;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(name, environ[i], _strlen(name)) == 0 &&
				environ[i][_strlen(name)] == '=')
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		for (i = index; environ[i] != NULL; i++)
			environ[i] = environ[i + 1];
		return (0);
	}
	return (-1);
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

	if (_unsetenv(token) == -1)
		perror("unsetenv");
	else
		*envp = environ;
}
