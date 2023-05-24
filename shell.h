#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>


/*constants*/
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 *struct map - a struct that maps a command name to a function 
 *
 *@command_name: name of the command
 *@func: the function that executes the command
 */

typedef struct map
{
	char *command_name;
	void (*func)(char **command);
} function_map;

extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;

/* BATCH COMMAND EXECUTOR */
void non_interactive(void);

/* COMMAND EXECUTOR */
void initializer(char **cmd, int cmd_type);

/* DATA STRUCTURES */
int _strlen(char *s);
void _strcpy(char *source, char *dest);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
unsigned int _strspn(char *s, char *accept);

/* ENVIRONMENT COMMANDS */
void print_environment(char **command_tokens __attribute__((unused)));
void quit_shell(char **command_tokens);

/* FILE UTILITIES */
char *_strchr(char *s, char c);
char *_strtok_r(char *str_to_tokenize, char *delimiter, char **save_ptr);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _atoi(char *s);
void ctrl_c_handler(int signum);

/* MY SHELL */
int main(int argc __attribute__((unused)), char **argv);

/* PATH RESOLUTIONS */
char *_getenv(char *name);
void (*get_func(char *command))(char **);
char *check_path(char *command);
void execute_command(char **tokenized_command, int command_type);
int parse_command(char *command);

/* STRING FUNCTIONS */
int _get_segment_length(char *source_str, char *exclude_str);
void remove_comment(char *input);
void remove_newline(char *str_to_modify);
void print_string(char *string_to_print, int output_stream);
char **tokenizer(char *str_to_tokenize, char *delimiter);

#endif

