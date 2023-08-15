#include "shell.h"

/**
 * print_string - Prints string to standard output
 * @str: The string to print
 */

void print_string(const char *str)
{
	size_t len = strlen(str);

	write(STDOUT_FILENO, str, len);
}

/**
 * list_aliases - Prints aliases
 * @aliases: An array of alias structure to be printed
 * @num_aliases: The number of aliases
 */
void list_aliases(Alias *aliases, int num_aliases)
{
	int i;

	for (i = 0; i < num_aliases; i++)
	{
		print_string(aliases[i].name);
		print_string("='");
		print_string(aliases[i].value);
		print_string("'\n");
	}
}

/**
 * create_or_modify_alias - Handles creating new aliases and modifying
 * existing aliases.
 * @token: Broken words or Tokenized string
 * @aliases: An array of Alias structure
 * @num_aliases: The number of aliases
 */
void create_or_modify_alias(const char *token, Alias *aliases,
		int *num_aliases)
{
	char *equal_sign = strchr(token, '=');
	const char *max_reached;
	int i, alias_index;

	if (equal_sign != NULL)
	{
		if (*num_aliases >= MAX_ALIASES)
		{
			max_reached = "Max number of aliases reached\n";
			print_string(max_reached);
			return;
		}

		alias_index = -1;

		for (i = 0; i < *num_aliases; i++)
		{
			if (strncmp(aliases[i].name, token, equal_sign - token) == 0)
			{
				alias_index = i;
				break;
			}
		}

		if (alias_index == -1)
		{
			aliases[*num_aliases].name = strndup(token, equal_sign - token);
			aliases[*num_aliases].value = strdup(equal_sign + 1);
			(*num_aliases)++;
		}
		else
		{
			free(aliases[alias_index].value);
			aliases[alias_index].value = strdup(equal_sign + 1);
		}
	}
}

/**
 * alias_builtin - Handles the "alias" command
 * @buffer: Input buffer to extract command and arguments
 * @aliases: An array of Alias structure
 * @num_aliases: The number of aliases
 */
void alias_builtin(char *buffer, Alias *aliases, int *num_aliases)
{
	char *token;

	token = _strtok(buffer, " ");
	token = _strtok(NULL, " ");

	if (token == NULL)
		list_aliases(aliases, *num_aliases);
	else
	{
		while (token != NULL)
		{
			create_or_modify_alias(token, aliases, num_aliases);
			token = _strtok(NULL, " ");
		}
	}
}
