#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

extern char **environ;

void getline_inp(char **buffer);
void env_builtin(char *buffer, char **envp);
char **tokens(char *buffer, char *delim);
char *find_command_path(const char *cmd);
void exit_func(char *buffer);
void call_fork(char *buffer, char **args, char *command_path);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int count_tokens(char *buffer, char *delim);

#endif /* SHELL_H */
