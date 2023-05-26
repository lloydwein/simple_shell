#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <signal.h>

#define FALSE 0
#define TRUE 1
#define NEITHER 2
#define MATCH 3
#define PREFIX 4
#define EXIT_SHELL 5
#define SKIP_FORK 6
#define DO_EXECVE 7

/**
 * struct Alias - lists of alias
 * @name: name of alias
 * @value: value for each name
 * @next: points to next node
 */
typedef struct Alias
{
	char *name;
	char *value;
	struct Alias *next;
} Alias;

/* ALIAS */
int deallocateAliases(Alias *ptr_alias);
int isAliasCommand(char **args, Alias *alias_list);
int displayAliases(Alias *alias_list);
int printAliasValue(char *arg, Alias *alias_ptr);
int setAliasValue(char *aliasName, Alias *aliasList, char *newValue);

/* COMMAND_EXECUTOR */
int command_manager(char **args);
int execute_builtins(char **args);
int perform_logical_evaluation(char **args, char operator, int last_compare);
char *check_command(char **args);
int execute_command(char **args);

/* DATA_STRUCTURES */
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
char *str_concat(char *s1, char *s2);
int str_compare(char *s1, char *s2, int pref_or_match);

/* ENVIRONMENT_COMMANDS */
int _setEnvironmentVariable(const char *name, const char *value);
int _unsetEnvironmentVariable(const char *name);
int change_directory(char *directory_name);
int handle_alias_command(char **args, int to_free);
int print_environment(void);

/* FILE_UTILITIES */
char *_itoa(int n);
int _atoi(char *s);

/* GROUP_HANDLING */
char *findArrayElement(char **array, char *elementName);
char **splitString(char *stringToSplit, char delimiter, char **nextSubstring);
int countListEntries(char **list, char *entry);
char **copyStringArray(char **oldArray, int newSize);
int freeStringArray(char **array);

/* INPUT_UTILITY */
char *sanitize_input(char *old_buf, size_t *old_size);
int validate_input(char *ptr);
void err_message(char *arg0, char *arg1);
char *replace_vars(char *arg);

/* MY_SHELL */
int main(__attribute__((unused))int ac, char **av);

#endif
