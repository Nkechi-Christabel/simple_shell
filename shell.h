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
int handle_exec(char *buffer, int last_status);
void handle_logical_and(char *cmd, int last_status);
void handle_logical_or(char *cmd, int last_status);
void handle_semicolon(char *buffer, int last_status);
void print_string(const char *str);
void list_aliases(Alias *aliases, int num_aliases);
void create_or_modify_alias(const char *token, Alias *aliases,
		int *num_aliases);
void alias_builtin(char *buffer, Alias *aliases, int *num_aliases);
char *replace_variables(const char *command, int last_status);
char *replace_exit_status(char *result, size_t *len, int status);
char *replace_process_id(char *result, size_t *len);
char *finalize_result(char *result, size_t len);

int is_valid_variable_character(char c);
char *append_string(char *result, const char *str, size_t *len);
char *echo_path(char *result, size_t *len, const char *var_name_start);
size_t get_variable_name_length(const char *var_name_start);
void handle_comment(char *buffer);

#endif /* SHELL_H */
