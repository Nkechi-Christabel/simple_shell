#include "shell.h"

/**
 * handle_semicolon - handles commands with semi colon ;
 *
 * @buffer: contains the command
 */
void handle_semicolon(char *buffer)
{
	char *command, *trim_cmd;
	size_t len;

	command = strtok(buffer, ";");
	while (command != NULL)
	{
		trim_cmd = command;

		while (*trim_cmd == ' ' || *trim_cmd == '\t' || *trim_cmd == '\n')
			trim_cmd++;
		len = strlen(trim_cmd);

		while (len > 0 && (trim_cmd[len - 1] == ' ' ||
			trim_cmd[len - 1] == '\t' || trim_cmd[len - 1] == '\n'))
		{
			trim_cmd[len - 1] = '\0';
			len--;
		}
		if (len > 0)
		{
			handle_exec(trim_cmd);
		}

		command = strtok(NULL, ";");
	}
}

/**
 * handle_logical_or - handles commands with OR operator ||
 *
 * @cmd: contains the command
 */
void handle_logical_or(char *cmd)
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
			result = handle_exec(pos);
			if (result == 0)
				return;
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
		handle_exec(pos);
}

/**
 * handle_logical_and - handles commands with AND operator &&
 *
 * @cmd: contains the command
 */
void handle_logical_and(char *cmd)
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
			result = handle_exec(pos);
			if (result != 0)
				return;
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
		handle_exec(pos);
}
