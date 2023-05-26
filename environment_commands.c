#include "shell.h"

/**
 * _setEnvironmentVariable - Set an environment variable
 * @name: The name of the environment variable
 * @value: The value to assign to the environment variable
 *
 * This function sets an environment variable with the provided name and value.
 * If the value is NULL, an error message is displayed and the function return
 * SKIP_FORK. It checks if the environment variable already exists, and if not
 * it creates a new environment array with the updated variable.
 * If the environment variable already exists, it replaces its value with the
 * new value.
 * Return: SKIP_FORK if successful, otherwise an error status code.
 */
int _setEnvironmentVariable(const char *name, const char *value)
{
	char **newEnviron;
	char *buffer;
	char *bufferWithValue;
	char *elementPtr;
	int length;

	if (value == NULL)
	{
		write(STDERR_FILENO, "setenv: no value given\n", 23);
		status = 2;
		return (SKIP_FORK);
	}

	buffer = str_concat((char *)name, "=");

	elementPtr = findArrayElement(environ, buffer);

	bufferWithValue = str_concat(buffer, (char *)value);
	free(buffer);
	buffer = bufferWithValue;

	if (elementPtr == NULL)
	{
		length = countListEntries(environ, NULL);
		newEnviron = copyStringArray(environ, length + 1);
		newEnviron[length - 1] = buffer;
		newEnviron[length] = NULL;
		freeStringArray(environ);
		environ = newEnviron;
		return (SKIP_FORK);
	}

	length = countListEntries(environ, (char *)name);
	free(environ[length]);
	environ[length] = buffer;

	status = 0;

	return (SKIP_FORK);
}


/**
 * _unsetEnvironmentVariable - Unset an environment variable
 * @name: The name of the environment variable to unset
 *
 * This function unsets an environment variable with the provided name.
 * It searches for the variable in the environment array and removes it if
 * found. If the variable is not found, an error message is displayed and
 * the function returns SKIP_FORK.
 * Return: SKIP_FORK if successful, otherwise an error status code.
 */
int _unsetEnvironmentVariable(const char *name)
{
	char **env_ptr;
	char *buffer;
	int index;

	buffer = str_concat((char *)name, "=");
	index = countListEntries(environ, buffer);
	free(buffer);

	if (index == -1)
	{
		write(STDERR_FILENO, "unsetenv: variable not found\n", 29);
		status = 2;
		return (SKIP_FORK);
	}

	env_ptr = environ + index;
	free(*env_ptr);
	while (*(env_ptr + 1) != NULL)
	{
		*env_ptr = *(env_ptr + 1);
		env_ptr++;
	}
	*env_ptr = NULL;
	status = 0;

	return (SKIP_FORK);
}

/**
 * change_directory - Changes the current working directory to the specified
 * directory
 * @directory_name: the name of the directory to change to.
 * If the directory name is NULL, it changes to the home directory.
 * If the directory name is "-", it changes to the previous directory.
 * If the directory name is a valid directory path, it changes to that
 * directory
 * Return: Returns 0 on success, -1 on failure.
 */
int change_directory(char *directory_name)
{
	char *home_dir;
	char *prev_dir;
	char old_path_buffer[PATH_MAX];
	char new_path_buffer[PATH_MAX];
	size_t buffer_size = PATH_MAX;
	int status_code;

	getcwd(old_path_buffer, buffer_size);

	if (directory_name == NULL)
	{
		home_dir = findArrayElement(environ, "HOME=");
		if (home_dir == NULL)
		{
			status = 2;
			err_message("cd", directory_name);
			return (-1);
		}

		home_dir += 5;

		status_code = chdir((const char *)home_dir);
		if (status_code != -1)
			_setEnvironmentVariable("PWD",
					(const char *)home_dir);
	}
	else if (str_compare("-", directory_name, MATCH) == TRUE)
	{
		prev_dir = findArrayElement(environ, "OLDPWD=");
		if (prev_dir == NULL)
		{
			status = 2;
			err_message("cd", directory_name);
			return (-1);
		}

		prev_dir += 7;

		status_code = chdir((const char *)prev_dir);
		if (status_code != -1)
		{
			write(STDOUT_FILENO, prev_dir, _strlen(prev_dir));
			write(STDOUT_FILENO, "\n", 1);
			_setEnvironmentVariable("PWD",
					(const char *)prev_dir);
		}
	}
	else if (directory_name != NULL)
	{
		status_code = chdir((const char *)directory_name);
		if (status_code != -1)
			_setEnvironmentVariable("PWD",
					getcwd(new_path_buffer, buffer_size));
	}
	if (status_code == -1)
	{
		status = 2;
		err_message("cd", directory_name);
		return (-1);
	}

	status = 0;
	_setEnvironmentVariable("OLDPWD", (const char *)old_path_buffer);

	return (0);
}

/**
 * handle_alias_command - Handles the 'alias' command.
 * @args: the command argument
 * @to_free: flag indicating whether to free the aliases
 * Return: the staus of the command execution
 */
int handle_alias_command(char **args, int to_free)
{
	static Alias head = {NULL, NULL, NULL};
	char *alias_value_ptr;
	int is_error_free = TRUE;

	if (to_free == TRUE)
		return (deallocateAliases(head.next));

	if (str_compare("alias", *args, MATCH) != TRUE)
		return (isAliasCommand(args, head.next));

	args++;

	if (*args == NULL)
		return (printAliasValue(head.next));

	while (*args != NULL)
	{
		alias_value_ptr = *args;
		while (*alias_value_ptr != '\0' && *alias_value_ptr != '=')
			alias_value_ptr++;

		if (*alias_value_ptr == '\0' || alias_value_ptr == *args)
		{
			if (printAliasValue(*args, &head) == FALSE)
				is_error_free = FALSE;
		}
		else
		{
			*alias_value_ptr = '\0';
			alias_value_ptr++;
			setAliasValue(*args, &head, alias_value_ptr);
			*(alias_value_ptr - 1) = '=';
		}
		args++;
	}

	if (is_error_free == FALSE)
		return (SKIP_FORK);

	status = 0;
	return (SKIP_FORK);
}

/**
 * print_environment - prints  the environment variables
 * Return: the status of the command execution.
 */
int print_environment(void)
{
	char **env_ptr = environ;

	while (*env_ptr != NULL)
	{
		write(STDOUT_FILENO, *env_ptr, _strlen(*env_ptr));
		write(STDOUT_FILENO, "\n", 1);
		env_ptr++;
	}

	status = 0;

	return (SKIP_FORK);
}
