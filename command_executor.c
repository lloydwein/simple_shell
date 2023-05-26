#include "shell.h"

/**
 * command_manager - Executes commands based on logical operators.
 * @args: the command aruments
 * Return: the status of the command execution
 */
int command_manager(char **args)
{
	char **args_ptr = args;
	int prev_eval = NEITHER;
	int no_err = TRUE;
	char prev_op = 'c';
	char next_op = 'c';
	int what_do;

	while (*args != NULL && prev_eval != EXIT_SHELL)
	{
		while (*args_ptr != NULL && **args_ptr != '&'
		       && **args_ptr != '|')
			args_ptr++;

		if (str_compare(*args_ptr, "||", MATCH) == TRUE)
		{
			*args_ptr = NULL;
			args_ptr++;
			next_op = '|';
		}
		if (str_compare(*args_ptr, "&&", MATCH) == TRUE)
		{
			*args_ptr = NULL;
			args_ptr++;
			next_op = '&';
		}
		if (next_op == 'c')
			break;

		prev_eval = and_or(args, prev_op, prev_eval);
		if (prev_eval == FALSE)
			no_err = FALSE;
		prev_op = next_op;
		args = args_ptr;
	}

	if (next_op == 'c')
	{
		what_do = execute_command(args);

		if (what_do == EXIT_SHELL)
			return (EXIT_SHELL);
	}

	if (no_err == FALSE || what_do == FALSE)
		return (FALSE);

	return (TRUE);
}

/**
 * execute_builtins - executes built-in commands
 * @args: the command arguments
 * Return: the status of the built-in command execution
 */
int execute_builtins(char **args)
{
	char **ptr = args;
	int i;

	while (*ptr != NULL)
	{
		if (**ptr == '#')
		{
			*ptr = NULL;
			break;
		}
		if (str_compare("~", *ptr, MATCH) == TRUE &&
				findArrayElement(environ, "HOME=") != NULL)
		{
			*ptr = _strdup(findArrayElement(environ, "HOME=")
					+ 5);
			continue;
		}
		if (str_compare("~/", *ptr, PREFIX) == TRUE &&
				findArrayElement(environ, "HOME=") != NULL)
		{
			*ptr = str_concat(findArrayElement(environ, "HOME=")
					+ 5, *ptr + 1);
		}
		*ptr = replace_vars(*ptr);

		ptr++;
	}

	if (*args == NULL)
		return (SKIP_FORK);

	i = handle_alias_command(args, FALSE);
	if (i == DO_EXECVE || i == SKIP_FORK)
		return (i);

	if (str_compare("exit", *args, MATCH) == TRUE && args[1] != NULL)
	{
		status = _atoi(args[1]);
		if (status < 0)
		{
			status = 2;
			err_message(args[0], args[1]);
			return (SKIP_FORK);
		}
	}
	if (str_compare("exit", *args, MATCH) == TRUE)
		return (EXIT_SHELL);
	else if (str_compare("setenv", *args, MATCH) == TRUE
			&& args[1] != NULL)
		return (_setEnvironmentVariable(args[1], args[2]));
	else if (str_compare("unsetenv", *args, MATCH) == TRUE
			&& args[1] != NULL)
		return (_unsetEnvironmentVariable(args[1]));
	else if (str_compare("cd", *args, MATCH) == TRUE)
		return (change_directory(args[1]));
	else if (str_compare("env", *args, MATCH) == TRUE)
		return (print_environment());

	return (DO_EXECVE);
}

/**
 * perform_logical_evaluation - Performs logical AND/OR evaluation for
 * command execution
 * @args: the command argumnets
 * @operator: the logical operator ('&' or '|').
 * @last_compare: The result of the previous evaluation.
 * Return: The result of the logical evaluation.
 */
int perform_logical_evaluation(char **args, char operator, int last_compare)
{
	int i;

	if (last_compare == NEITHER)
	{
		i = execute_command(args);
		if (i == EXIT_SHELL)
			return (EXIT_SHELL);
		if (i == TRUE)
			return (TRUE);

		return (FALSE);
	}
	if (last_compare == TRUE && operator == '&')
	{
		i = execute_command(args);
		if (i == EXIT_SHELL)
			return (EXIT_SHELL);
		if (i == TRUE)
			return (TRUE);

		return (FALSE);
	}

	if (last_compare == FALSE && operator == '|')
	{
		i = execute_command(args);
		if (i == EXIT_SHELL)
			return (EXIT_SHELL);
		if (i == TRUE)
			return (TRUE);

		return (FALSE);
	}

	if (last_compare == TRUE && operator == '|')
		return (TRUE);

	return (FALSE);
}

/**
 * check_command - Checks if the command is an alias and returns the
 * corresponding replacement command.
 * @args: the command arguments
 * If the command is not an alias, it returns the original command
 * Return: the replacement command if it is an alias, otherwise the original
 * command.
 */
char *check_command(char **args)
{
	char *command_buf;
	char *full_buf;
	char *path_str = NULL;
	char *path_ptr;
	char *path_tmp;
	char **path_var = NULL;
	char **path_var_ptr;

	if (access(*args, X_OK) == 0)
		return (_strdup(*args));

	if (findArrayElement(environ, "PATH=") != NULL)
		path_str = _strdup(findArrayElement(environ, "PATH=") + 5);

	path_ptr = path_str;

	if (path_str != NULL)
	{
		if (*path_str == ':')
		{
			command_buf = str_concat("./", *args);
			if (access(command_buf, X_OK) == 0)
			{
				free(path_str);
				return (command_buf);
			}
			else
			{
				free(command_buf);
				path_ptr = _strdup(path_str + 1);
				free(path_str);
				path_str = path_ptr;
			}
		}
		while (*path_ptr != '\0')
		{
			if (*path_ptr == ':' && *(path_ptr + 1) == ':')
			{
				*(path_ptr + 1) = '\0';
				path_tmp = (str_concat(path_str, ".:"));
				path_ptr = str_concat(path_tmp, path_ptr + 2);
				free(path_str);
				free(path_tmp);
				path_str = path_ptr;
			}
			path_ptr++;
		}
	}
	if (path_str != NULL)
		path_var = splitString(path_str, ':', NULL);

	path_var_ptr = path_var;

	command_buf = str_concat("/", *args);

	full_buf = _strdup(command_buf);

	if (path_var != NULL)
	{
		while (*path_var_ptr != NULL && access(full_buf, X_OK) != 0)
		{
			free(full_buf);
			full_buf = str_concat(*path_var_ptr, command_buf);
			path_var_ptr++;
		}
	}

	free(command_buf);
	free(path_str);
	free(path_var);

	if (access(full_buf, X_OK) != 0)
	{
		err_message(args[0], NULL);
		free(full_buf);
		return (NULL);
	}

	return (full_buf);
}

/**
 * execute_command - Executes the given command by forking a new process and
 * executing the command in the child process
 * @args: The command arguments.
 * Return: EXIT_SHELL if the command is "exit" and the shell should exit,
 *         TRUE if the command was executed successfully,
 *         FALSE if there was an error executing the command.
 */
int execute_command(char **args)
{
	char *buf_ptr = *args;
	char *command_name;
	pid_t pid;
	int what_do = execute_builtins(args);

	if (what_do == DO_EXECVE)
	{
		command_name = check_command(args);
		if (command_name == NULL)
			return (FALSE);

		pid = fork();
		if (pid == -1)
		{
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			execve(command_name, args, environ);
			exit(EXIT_FAILURE);
		}
		wait(&status);
		free(command_name);
		fflush(stdin);
		if (status != 0)
		status = 2;
	}

	if (str_compare("false", *args, MATCH) == TRUE)
		status = 1;

	if (*args != buf_ptr)
		free(*args);
	args++;

	while (*args != NULL)
	{
		while (*buf_ptr != '\0')
		{
			buf_ptr++;
		}
		buf_ptr++;

		if (*args != buf_ptr)
			free(*args);

		args++;
	}

	if (what_do == EXIT_SHELL)
		return (EXIT_SHELL);

	if (status != 0)
		return (FALSE);

	return (TRUE);
}
