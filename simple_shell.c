#include "shell.h"

/**
 * handle_exec - is a helper function to main
 *
 * @buffer: contains the command
 * @last_status: contains the last exit status
 * @shell_name: points to the shell name
 * @line: is the line count
 * Return: status
 */
int handle_exec(char *buffer, int last_status, char *shell_name, int *line)
{
	char **args, *command_path, *replaced_command;
	int i;
	int status;

	replaced_command = replace_variables(buffer, last_status);
	args = tokens(replaced_command);

	command_path = find_executable_path(args[0]);
	if (command_path == NULL)
	{
		print_error(shell_name, line, args[0]);
		free(buffer);
		free(args);
		free(replaced_command);
		return (127);
	}

	status = call_fork(buffer, args, command_path);
	free(command_path);


	for (i = 0; args[i] != NULL; i++)
		free(args[i]);

	free(args);
	free(replaced_command);

	return (status);
}

/**
 * handle_input - Handles user input and processing commands
 *
 * @current_dir: Current directory
 * @envp: Array of environment variable
 * @aliases: An array of Alias structure
 * @num_aliases: The number of aliases
 * @last_status: contains the last exit status
 * @shell_name: points to the shell name
 *
 * Return: 0
 */
int handle_input(char *current_dir, char *envp[], Alias *aliases,
		int *num_aliases, int last_status, char *shell_name)
{
	char *buffer = NULL;
	int is_interactive = isatty(STDIN_FILENO), line = 0;

	signal(SIGINT, sigint_handler);
	while (1)
	{
		if (is_interactive)
		{
			write(STDOUT_FILENO, ":)$ ", 4);
			fflush(stdout);
		}
		if (getline_inp(&buffer) == -1)
		{
			if (is_interactive)
				write(STDIN_FILENO, "\n", 1);
			break;
		}
		line++;
		if (buffer == NULL || _strcmp(buffer, "") == 0 || buffer[0] == '#'
				|| contains_only_spaces(buffer))
		{
			free(buffer);
			continue;
		}

		if (_strncmp(buffer, "setenv", 6) == 0)
			setenv_builtin(buffer, &envp);
		else
			last_status = handle_input2(buffer, current_dir, envp,
			aliases, num_aliases, last_status, shell_name, &line);

		if (last_status && is_interactive == 0)
			exit(last_status);
	}
	free(buffer);
	return (last_status);
}

/**
 * main - create a custom shell
 * @envp: Array of environment variables
 * @argc: is the number of items in argv
 * @argv: is a N:LL terminated array of strings
 *
 * Return: 0 always (Success)
 */
int main(int argc, char *argv[], char *envp[])
{
	char *current_dir = NULL, *line = NULL, *shell_name = argv[0];
	int last_status = 0, num_aliases = 0, line2 = 1, file_descriptor;
	size_t buffer_size = 0;
	ssize_t read_result;
	Alias aliases[MAX_ALIASES];

	if (argc > 1)
	{
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			print_error2(shell_name, argv[1]);
			return (2);
		}
		while ((read_result = read_line(file_descriptor, &line, &buffer_size)) != -1)
		{
			if (_strlen(line) == 0)
				break;
			line[_strcspn(line, "\n")] = '\0';
			if (read_result == 0 || _isspace((unsigned char)line[0]) || line[0] == '#')
				continue;
			line2++;
			last_status = handle_input2(line, current_dir, envp,
					aliases, &num_aliases, last_status, shell_name, &line2);
		}
		free(line);
		close(file_descriptor);
	}
	else
	{
		last_status = handle_input(current_dir, envp, aliases,
				&num_aliases, last_status, shell_name);
		if (last_status)
			exit(last_status);
	}
	return (0);
}
/**
 * handle_input2 - Handles user input and processing commands
 *
 * @buffer: contains commands
 * @current_dir: Current directory
 * @envp: Array of environment variable
 * @aliases: An array of Alias structure
 * @num_aliases: The number of aliases
 * @last_status: contains the last exit status
 * @shell_name: points to the shell name
 * @line: is the line count
 *
 * Return: last_status
 */
int handle_input2(char *buffer, char *current_dir, char *envp[],
		Alias *aliases, int *num_aliases, int last_status,
		char *shell_name, int *line)
{
	trim_spaces(buffer);
	handle_comment(buffer);
	exit_func(buffer, shell_name, line);
	if (_strncmp(buffer, "setenv", 6) == 0)
		setenv_builtin(buffer, &envp);
	else if (_strncmp(buffer, "env", 3) == 0)
		env_builtin(envp);
	else if (_strncmp(buffer, "unsetenv", 8) == 0)
		unsetenv_builtin(buffer, &envp);
	else if (_strncmp(buffer, "alias", 5) == 0)
		alias_builtin(buffer, aliases, num_aliases);
	else if (_strncmp(buffer, "cd", 2) == 0)
		cd_builtin(buffer, &current_dir);
	else if  (_strstr(buffer, "&&") != NULL)
		last_status = handle_logical_and(buffer, last_status, shell_name, line);
	else if (_strstr(buffer, "||") != NULL)
		last_status = handle_logical_or(buffer, last_status, shell_name, line);
	else if (_strstr(buffer, ";") != NULL)
		last_status = handle_semicolon(buffer, last_status, shell_name, line);
	else
		last_status = handle_exec(buffer, last_status, shell_name, line);

	return (last_status);
}
