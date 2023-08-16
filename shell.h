#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

extern char **environ;

#define BUFFER_SIZE 1024
#define MAX_ALIASES 50

typedef struct {
    char *name;
    char *value;
}Alias;


ssize_t getline_inp(char **buffer);
void env_builtin(char *buffer, char **envp);
char **tokens(char *buffer);
void exit_func(char *buffer);
int call_fork(char *buffer, char **args, char *command_path);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strtok(char *str, const char *delim);
char *find_path_env(void);
char *find_executable_path(const char *cmd);
void setenv_builtin(char *buffer, char ***envp);
void unsetenv_builtin(char *buffer, char ***envp);
void cd_builtin(char *buffer, char **current_dir);
int handle_exec(char *buffer);
void handle_logical_and(char *cmd);
void handle_logical_or(char *cmd);
void handle_semicolon(char *buffer);
void print_string(const char *str);
void list_aliases(Alias *aliases, int num_aliases);
void create_or_modify_alias(const char *token, Alias *aliases,
		int *num_aliases);

void alias_builtin(char *buffer, Alias *aliases, int *num_aliases);

#endif /* SHELL_H */
