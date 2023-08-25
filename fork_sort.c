#include "shell.h"

#define MAX_LINES 1000

char *output_lines[MAX_LINES];


int compare_lines(const void *a, const void *b)
{
	const char *line1 = *(const char **)a;
	const char *line2 = *(const char **)b;

	return (strcasecmp(line1, line2));
}

/**
 * call_fork - calls the fork function
 *
 * @buffer: contains the command
 * @args: tokenized buffer
 * @command_path: contains the path
 *
 * Return: WEXITSTATUS(status)
 */
int call_fork(char *buffer, char **args, char *command_path)
{
	pid_t pid;
	int status, pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("Error creating a pipe");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error creating a child process");
		free(buffer);
		free(command_path);
		free(args);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		child_process(pipe_fd, buffer, command_path, args);
	else
		parent_process(pipe_fd, buffer, command_path, args, pid, &status);

	return(0);
}

void child_process(int pipe_fd[], char *buffer, char *command_path, char **args)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);

	execve(command_path, args, NULL);
	perror("Error executing command");
	free_resources(buffer, command_path, args);
	exit(127);
}

void parent_process(int pipe_fd[], char *buffer, char *command_path, char **args, pid_t pid, int *status)
{
	char *line = NULL;
	size_t line_size = 0;
	ssize_t read_result;
	int num_lines = 0, i;
	char *output_lines[MAX_LINES];
	FILE *pipe_stream;

	close(pipe_fd[1]);
	pipe_stream = fdopen(pipe_fd[0], "r");

	while ((read_result = getline(&line, &line_size, pipe_stream)) != -1)
	{
		if (num_lines < MAX_LINES)
			output_lines[num_lines++] = strdup(line);
	}
	fclose(pipe_stream);
	free(line);

	qsort(output_lines, num_lines, sizeof(char *), compare_lines);

	for (i = 0; i < num_lines; i++)
	{
		write(STDOUT_FILENO, output_lines[i], strlen(output_lines[i]));
		free(output_lines[i]);
	}

	if (waitpid(pid, status, 0) == -1)
	{
		perror("Error while waiting");
		free_resources(buffer, command_path, args);
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(*status))
		exit(WEXITSTATUS(*status));
	else
		exit(-1);
}

void free_resources(char *buffer, char *command_path, char **args)
{
	int i;

	free(buffer);
	free(command_path);

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);

	free(args);
}
