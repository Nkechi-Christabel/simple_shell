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
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;

#define BUFFER_SIZE 1024
#define MAX_ALIASES 50
#define HISTORY_SIZE 10

/**
 * struct Alias - Typedef structure for alias
 *
 * @name: name of alias
 * @value: value of alias
 * Alias - is the typedef name
 */
typedef struct Alias
{
	char *name;
	char *value;
} Alias;

ssize_t getline_inp(char **buffer);
void env_builtin(char *buffer, char **envp);
char **tokens(char *buffer);
void exit_func(char *buffer, char *shell_name, int *line);
int call_fork(char *buffer, char **args, char *command_path);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
size_t read_buffer(char *buffer, size_t *buffer_pos, size_t *buffer_size,
		FILE *stream);
char *_strtok(char *str, const char *delim);
char *find_executable_path(const char *cmd);
void setenv_builtin(char *buffer, char ***envp);
void unsetenv_builtin(char *buffer, char ***envp);
void cd_builtin(char *buffer, char **current_dir);
int handle_exec(char *buffer, int last_status, char *shell_name, int *line);
int handle_logical_and(char *cmd, int last_status, char *shell_name,
		int *line);

int handle_logical_or(char *cmd, int last_status, char *shell_name, int *line);
int handle_semicolon(char *buffer, int last_status, char *shell_name,
		int *line);

void print_string(const char *str);
void list_aliases(Alias *aliases, int num_aliases);
void create_or_modify_alias(const char *token, Alias *aliases,
		int *num_aliases);
void alias_builtin(char *buffer, Alias *aliases, int *num_aliases);
void free_aliases(Alias *aliases, int num_aliases);
char *replace_variables(const char *command, int last_status);
char *replace_exit_status(char *result, size_t *len, int status);
char *replace_process_id(char *result, size_t *len);
char *finalize_result(char *result, size_t len);

int is_valid_variable_character(char c);
char *append_string(char *result, const char *str, size_t *len);
char *echo_path(char *result, size_t *len, const char *var_name_start);
size_t get_variable_name_length(const char *var_name_start);
void handle_comment(char *buffer);
int handle_input2(char *buffer, char *current_dir, char *envp[],
		Alias *aliases, int *num_aliases, int last_status,
		char *shell_name, int *line2);

int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
int contains_only_spaces(const char *str);
void trim_spaces(char *str);
void print_error(char *shell_name, int *line, char *command);
void print_error2(char *shell_name, char *command);
void reverseString(char str[], int length);
char *intToString(int num, char *str);
void sigint_handler(int signum);
void print_error3(char *shell_name, int *line, char *command);
ssize_t read_line(int fd, char **line, size_t *buffer_size);
char *_getenv(const char *name);

int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
char *_strcat(char *dest, const char *src);
char *_strstr(const char *haystack, const char *needle);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);
char *_strchr(const char *str, int ch);
char *_strndup(const char *str, size_t n);
size_t _strcspn(const char *str, const char *reject);
char *_strpbrk(const char *str, const char *accept);
int _isspace(char c);
int _atoi(char *s);
int _strncmp(const char *str1, const char *str2, size_t n);

#endif /* SHELL_H */
