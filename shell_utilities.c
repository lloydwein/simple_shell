#include "shell.h"

/**
 * _getenv - Get the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * This function searches for the environment variable with the given name
 * and returns its value. It iterates over the environment variables and
 * compares each name with the provided name until a match is found. If a match
 * is found, it returns the value associated with the variable. If no match is
 * found, it returns NULL.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *_getenv(char *name)
{
	char **env_var;
	char *var_pair;
	char *name_copy;

	for (env_var = environ; *env_var != NULL; env_var++)
	{
		for (var_pair = *env_var, name_copy = name;
				*var_pair == *name_copy; var_pair++, name_copy++)
