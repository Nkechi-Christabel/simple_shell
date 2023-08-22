#include "shell.h"

/**
 * handle_semicolon - handles commands with semi colon ;
 *
 * @last_status: contains the last exit status
 * @buffer: contains the command
 * @shell_name: points to the shell name
 * @line: is the line count
 *
 *  Return: status
 */
int handle_semicolon(char *buffer, int last_status, char *shell_name,
		int *line)
{
	char *command, *trim_cmd;
	size_t len;
	int status;

	command = buffer;
	while (*command != '\0')
	{
		char *semicolon = strstr(command, ";");

		if (semicolon != NULL)
		{
			*semicolon = '\0';
			trim_cmd = command;
		}
		else
			trim_cmd = command;

		while (*trim_cmd == ' ' || *trim_cmd == '\t' || *trim_cmd == '\n')
			trim_cmd++;

		len = strlen(trim_cmd);

		while (len > 0 && (trim_cmd[len - 1] == ' ' || trim_cmd[len - 1] == '\t' || trim_cmd[len - 1] == '\n'))
		{
			trim_cmd[len - 1] = '\0';
			len--;
		}
		if (len > 0)
		{
			status = handle_exec(trim_cmd, last_status, shell_name, line);
		}
		if (semicolon != NULL)
		{
			command = semicolon + 1;
		}
		else
			break;
	}

	return (status);
}

/**
 * handle_logical_or - handles commands with OR operator ||
 *
 * @last_status: contains the last exit status
 * @cmd: contains the command
 * @shell_name: points to the shell name
 * @line: is the line count
 * Return: result
 */
int handle_logical_or(char *cmd, int last_status, char *shell_name, int *line)
{
	char *or_token = "||";
	char *pos = cmd, *next_cmd;
	size_t len;
	int result;

	while ((next_cmd = strstr(pos, or_token)) != NULL)
	{
		*next_cmd = '\0';

		while (*pos == ' ' || *pos == '\t' || *pos == '\n')
			pos++;
		len = strlen(pos);
		while (len > 0 && (pos[len - 1] == ' ' || pos[len - 1] == '\t' ||
				pos[len - 1] == '\n'))
		{
			pos[len - 1] = '\0';
			len--;
		}

		if (len > 0)
		{
			result = handle_exec(pos, last_status, shell_name, line);
			if (result == 0)
				return (result);
		}
		pos = next_cmd + strlen(or_token);
	}
	while (*pos == ' ' || *pos == '\t' || *pos == '\n')
		pos++;
	len = strlen(pos);
	while (len > 0 && (pos[len - 1] == ' ' || pos[len - 1] == '\t' ||
			pos[len - 1] == '\n'))
	{
		pos[len - 1] = '\0';
		len--;
	}
	if (len > 0)
		result = handle_exec(pos, last_status, shell_name, line);
	return (result);

}

/**
 * handle_logical_and - handles commands with AND operator &&
 *
 * @last_status: contains the last exit status
 * @cmd: contains the command
 * @shell_name: points to the shell name
 * @line: is the line count
 *
 * Return: result
 */
int handle_logical_and(char *cmd, int last_status, char *shell_name, int *line)
{
	char *and_token = "&&";
	char *pos = cmd, *next_cmd;
	size_t len;
	int result;

	while ((next_cmd = strstr(pos, and_token)) != NULL)
	{
		*next_cmd = '\0';
		while (*pos == ' ' || *pos == '\t' || *pos == '\n')
			pos++;
		len = strlen(pos);
		while (len > 0 && (pos[len - 1] == ' ' || pos[len - 1] == '\t' ||
				pos[len - 1] == '\n'))
		{
			pos[len - 1] = '\0';
			len--;
		}
		if (len > 0)
		{
			result = handle_exec(pos, last_status, shell_name, line);
			if (result != 0)
				return (result);
		}
		pos = next_cmd + strlen(and_token);
	}
	while (*pos == ' ' || *pos == '\t' || *pos == '\n')
		pos++;
	len = strlen(pos);
	while (len > 0 && (pos[len - 1] == ' ' || pos[len - 1] == '\t' ||
			pos[len - 1] == '\n'))
	{
		pos[len - 1] = '\0';
		len--;
	}
	if (len > 0)
		result = handle_exec(pos, last_status, shell_name, line);
	return (result);
}
