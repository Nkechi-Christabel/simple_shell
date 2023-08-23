#include "shell.h"

/**
 * sigint_handler - handles CTRL+D
 *
 * @signum: helps sigint_handler
 */
void sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n:)$ ", 5);
}
/**
 * getline_inp - Gets command lines from standard input
 * @buffer: Where inputs are stored
 *
 * Return: input
 */

ssize_t getline_inp(char **buffer)
{
	ssize_t input;
	size_t buffer_size = 0;

	input = _getline(buffer, &buffer_size, stdin);
	if (input == -1)
	{
		return (-1);
	}

	if ((*buffer)[input - 1] == '\n')
		(*buffer)[input - 1] = '\0';

	return (input);

}

/**
 * _getline - performs the getline function
 *
 * @lineptr: contains the buffer
 * @n: buffer lenght
 * @stream: stdin is passed
 *
 * Return: pos if success and -1 if failed
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[BUFFER_SIZE];
	static size_t buffer_pos, buffer_size;
	size_t pos = 0;
	char c, *new_ptr;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);
	if (*lineptr == NULL || *n == 0)
	{
		*n = BUFFER_SIZE;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	while (1)
	{
		if (read_buffer(buffer, &buffer_pos, &buffer_size, stream) == 0)
		{
			if (pos == 0)
				return (-1);
			break;
		}
		c = buffer[buffer_pos++];
		(*lineptr)[pos++] = c;
		if (c == '\n')
			break;
		if (pos + 1 >= *n)
		{
			*n *= 2;
			new_ptr = (char *)realloc(*lineptr, *n);
			if (new_ptr == NULL)
			{
				free(*lineptr);
				return (-1);
			}
			*lineptr = new_ptr;
		}
	}
	(*lineptr)[pos] = '\0';
	return (pos);
}

/**
 * read_buffer - reads the buffer
 *
 * @buffer: points to buffer in _getline
 * @buffer_pos: points to buffer_pos in _getline
 * @buffer_size: buffer size
 * @stream: stdin is passed
 *
 * Return: buffer_size if success and 0 if failed
 */
size_t read_buffer(char *buffer, size_t *buffer_pos, size_t *buffer_size,
		FILE *stream)
{
	if (*buffer_pos >= *buffer_size)
	{
		*buffer_size = read(fileno(stream), buffer, BUFFER_SIZE);
		*buffer_pos = 0;
		if (*buffer_size <= 0)
		{
			return (0);
		}
	}
	return (*buffer_size - *buffer_pos);
}
