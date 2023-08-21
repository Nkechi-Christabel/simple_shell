#include "shell.h"

/**
 * read_line - reads and split the command in line
 *
 * @fd: contains the commands with new line
 * @line: is where the commands will be split to
 * @buffer_size: contains the size of the command
 *
 * Return: total_read
 */
ssize_t read_line(int fd, char **line, size_t *buffer_size)
{
	ssize_t bytes_read = 0;
	size_t total_read = 0;
	char *buffer = NULL;

	while (1)
	{
		if (total_read >= *buffer_size)
		{
			*buffer_size += 1024;
			buffer = realloc(*line, *buffer_size);
			if (!buffer)
			{
				perror("Memory allocation error");
				free(*line);
				return (-1);
			}
			*line = buffer;
		}

		bytes_read = read(fd, *line + total_read, 1);

		if (bytes_read == -1)
		{
			perror("Error reading from file");
			free(*line);
			return (-1);
		}
		else if (bytes_read == 0)
		{
			(*line)[total_read] = '\0';
			return (total_read);
		}
		total_read += bytes_read;
		if ((*line)[total_read - 1] == '\n')
		{
			(*line)[total_read] = '\0';
			return (total_read);
		}
	}
}
