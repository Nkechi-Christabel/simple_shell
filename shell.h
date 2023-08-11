#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void getline_inp(char **buffer);
void env_builtin(char *buffer, char **envp);
char **tokens(char *buffer);
char *find_command_path(const char *command);
void exit_func(char *buffer);
void call_fork(char *buffer, char **args, char *command_path);

#endif /* SHELL_H */
