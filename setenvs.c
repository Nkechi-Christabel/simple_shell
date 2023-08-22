
#include "shell.h"

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

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
		return (-1);

	if (!overwrite && getenv(name) != NULL)
		return (0);

	len = strlen(name) + strlen(value) + 2;

	new_var = (char *)malloc(len);

	if (new_var == NULL)
		return (-1);

	strcpy(new_var, name);
	strcat(new_var, "=");
	strcat(new_var, value);

	result = putenv(new_var);

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
	char **env, **new_env;
	int new_idx;
	size_t count = 0;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
		return -1;

	for (env = environ; *env != NULL; ++env)
		if (strncmp(*env, name, strlen(name)) != 0 || (*env)[strlen(name)] != '=')
			++count;
	new_env = (char **)malloc((count + 1) * sizeof(char *));

	if (new_env == NULL)
		return -1;

	new_idx = 0;

	for (env = environ; *env != NULL; ++env)
		if (strncmp(*env, name, strlen(name)) != 0 || (*env)[strlen(name)] != '=')
			new_env[new_idx++] = *env;

	new_env[new_idx] = NULL;
	environ = new_env;

	return (0);
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
