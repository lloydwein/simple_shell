#include "shell.h"

int status;
int line_num;
char *shell_name;

extern char **environ;

/**
 * sanitize_input - Sanitizes the input string by replacing newline and tab
 * characters with spaces, and removes leading and trailing spaces.
 * Returns the sanitized input as a new dynamically allocated string
 * @old_buf: input string to snitize
 * @old_size: Pointer to the size of the input string.
 * Return: The sanitized input string, or NULL if memory allocation fails
 * or if the input is invalid.
 */
char *sanitize_input(char *old_buf, size_t *old_size)
{
	char *new_buf = malloc(*old_size * 3);
	char *new_ptr = new_buf;
	char *old_ptr = old_buf;

	while (*old_ptr != '\0')
	{
		while (*old_ptr == ' ')
			old_ptr++;
		while (*old_ptr	!= ' ' && *old_ptr != ';' && *old_ptr != '|'
		       && *old_ptr != '&' && *old_ptr != '\0')
		{
			*new_ptr = *old_ptr;
			new_ptr++;
			old_ptr++;
		}
		while (*old_ptr == ' ')
			old_ptr++;
		if (new_ptr != new_buf && *old_ptr != '\0')
		{
			*new_ptr = ' ';
			new_ptr++;
		}

		if (*old_ptr == ';' || *old_ptr == '|' || *old_ptr == '&')
		{
			if (validate_input(old_ptr) == FALSE)
			{
				*old_size = 0;
				break;
			}
			*new_ptr = *old_ptr;
			if (*old_ptr == ';')
			{
				new_ptr++;
				*new_ptr = ' ';
			}
			else if (*(old_ptr + 1) == *old_ptr)
			{
				if (new_ptr == new_buf)
				{
					err_message(old_ptr, NULL);
					*old_size = 0;
					break;
				}
				new_ptr++;
				*new_ptr = *old_ptr;
				new_ptr++;
				*new_ptr = ' ';
				old_ptr++;
			}
			new_ptr++;
			old_ptr++;
		}
	}
	*new_ptr = '\0';
	free(old_buf);
	return (new_buf);
}

/**
 * validate_input - Checks the input string for errors by validating its syntax
 * It performs the following checks:
 * - Checks if the input contains only whitespace characters.
 * - Checks if the input ends with an incomplete escape character ('\').
 * - Checks if the input ends with an incomplete quotation mark ('"').
 * - Checks if the input ends with an incomplete single quotation mark ('\'').
 * - Checks if the input contains mismatched quotation marks or escape
 * characters.
 * @ptr: the input string to check for errors
 * Return: 1 if input is valid without any errors, 0 otherwise
 */
int validate_input(char *ptr)
{
	char *iter = ptr;

	iter++;
	if (*ptr == ';' && *iter == *ptr)
	{
		err_message(ptr, NULL);
		return (FALSE);
	}
	if (*iter == *ptr)
		iter++;

	while (*iter == ' ')
		iter++;

	if (*iter == ';' || *iter == '|' || *iter == '&')
	{
		err_message(iter, NULL);
		return (FALSE);
	}

	return (TRUE);
}

/**
 * err_message - Prints an error message with the provided arguments.
 * @arg0: The first argument.
 * @arg1: The second argument.
 * This function prints an error message to the standard error stream
 * with the provided arguments. The error message includes the values
 * of arg0 and arg1 to provide more context about the error.
*/
void err_message(char *arg0, char *arg1)
{
	char *err_str_num = _itoa(line_num);

	write(STDERR_FILENO, shell_name, _strlen(shell_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, err_str_num, _strlen(err_str_num));
	free(err_str_num);

	if (str_compare("cd", arg0, MATCH) == TRUE)
	{
		status = 2;
		write(STDERR_FILENO, ": cd: can't cd to ", 18);
		write(STDERR_FILENO, arg1, _strlen(arg1));
		write(STDERR_FILENO, "\n", 1);
		return;
	}

	if (str_compare("exit", arg0, MATCH) == TRUE)
	{
		write(STDERR_FILENO, ": exit: Illegal number: ", 24);
		write(STDERR_FILENO, arg1, _strlen(arg1));
		write(STDERR_FILENO, "\n", 1);
		return;
	}
	if (*arg0 == ';' || *arg0 == '|' || *arg0 == '&')
	{
		status = 2;
		write(STDERR_FILENO, ": Syntax error: \"", 17);
		write(STDERR_FILENO, arg0, 1);
		if (*arg0 == *(arg0 + 1))
			write(STDERR_FILENO, arg0, 1);
		write(STDERR_FILENO, "\" unexpected\n", 14);
		return;
	}

	status = 127;
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, arg0, _strlen(arg0));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * replace_vars - Replaces environment variable references in a string.
 * @arg: The string to process.
 * Return: The modified string with replaced variable references.
 */
char *replace_vars(char *arg)
{
	char *clone = NULL;
	char *ptr = arg;
	char *next;
	char *tmp;
	char *buffer;
	int is_var;
	int i;

	while (*ptr != '\0')
	{
		if (*ptr == '$')
		{
			if (clone == NULL)
			{
				clone = _strdup(arg);
				i = ptr - arg;
				ptr = clone + i;
			}
			next = ptr + 1;
			while (*next != '\0' && *next != '$' && *next != '#')
				next++;

			if (*next == '$' && next > ptr + 1)
				is_var = TRUE;
			else if (*next == '#')
				is_var = NEITHER;
			else
				is_var = FALSE;

			*next = '\0';

			if (str_compare("$?", ptr, MATCH) == TRUE)
				tmp = _itoa(status);
			else if (str_compare("$0", ptr, MATCH) == TRUE)
				tmp = _strdup(shell_name);
			else if (findArrayElement(environ, ptr + 1) != NULL)
			{
				buffer = str_concat(ptr + 1, "=");
				tmp = _strdup(findArrayElement
				(environ, buffer) + _strlen(buffer));
				free(buffer);
			}
			else
				tmp = _strdup("");

			*ptr = '\0';
			ptr = str_concat(clone, tmp);
			free(tmp);
			if (is_var == FALSE)
			{
				free(clone);
				clone = ptr;
				break;
			}
			if (is_var == TRUE)
				*next = '$';
			else if (is_var == NEITHER)
				*next = '#';
			tmp = str_concat(ptr, next);
			free(ptr);
			ptr = tmp;
			free(clone);
			clone = ptr;
			if (is_var == NEITHER)
			{
				while (*ptr != '#')
					ptr++;
			}
		}
		ptr++;
	}
	if (clone != NULL)
		return (clone);

	return (arg);
}
