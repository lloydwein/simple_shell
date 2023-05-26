#include "shell.h"

/**
 * deallocateAliases - free alias
 * @ptr_alias: pointer to head of linked list
 * Return: 1 on success
 */
int deallocateAliases(Alias *ptr_alias)
{
	Alias *tmp_alias;

	while (ptr_alias != NULL)
	{
		tmp_alias = ptr_alias;
		ptr_alias = ptr_alias->next;
		free(tmp_alias->name);
		free(tmp_alias->value);
		free(tmp_alias);
	}

	return (1);
}

/**
 * isAliasCommand - checks if it's an alias command
 * @args: Arguments
 * @alias_list: Pointer to the head of the alias list
 *
 * This function checks if the given arguments correspond to an alias command
 * by comparing them with the names of aliases in the given alias list.
 * If a match is found, it replaces the arguments with the corresponding alias
 * value
 * Return: 1 if it's an alias command, 0 otherwise
 */
int isAliasCommand(char **args, Alias *alias_list)
{
	while (alias_list != NULL)
	{
		if (str_compare(*args, alias_list->name, MATCH) == TRUE)
		{
			*args = _strdup(alias_list->value);
			return (1);
		}
		alias_list = alias_list->next;
	}
	return (0);
}

/**
 * displayAliases - Display aliases
 * @alias_list: Pointer to the head of the alias list
 * This function prints the names and values of all aliases in the given alias
 * list
 * Return: SKIP_FORK
 */
int displayAliases(Alias *alias_list)
{
	while (alias_list != NULL)
	{
		write(STDOUT_FILENO, alias_list->name,
				_strlen(alias_list->name));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, alias_list->value,
				_strlen(alias_list->value));
		write(STDOUT_FILENO, "\n", 1);
		alias_list = alias_list->next;
	}
	return (SKIP_FORK);
}

/**
 * printAliasValue - Print alias value
 * @arg: Argument
 * @alias_ptr: Pointer to the head of the alias list
 *
 * This function prints the value of the specified alias in the given alias
 * list. If the alias is found, it prints the alias name, followed by "=", and
 * then the alias value. If the alias is not found, it prints an error message
 * Return: TRUE if the alias is found and printed, FALSE otherwise
 */
int printAliasValue(char *arg, Alias *alias_ptr)
{
	while (alias_ptr != NULL)
	{
		fflush(stdin);
		if (str_compare(arg, alias_ptr->name, MATCH) == TRUE)
		{
			write(STDOUT_FILENO, arg, _strlen(arg));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, alias_ptr->value,
					_strlen(alias_ptr->value));
			write(STDOUT_FILENO, "\n", 1);
			return (TRUE);
		}
		alias_ptr = alias_ptr->next;
	}

	write(STDERR_FILENO, "alias: ", 7);
	write(STDERR_FILENO, arg, _strlen(arg));
	write(STDERR_FILENO, " not found\n", 11);

	return (FALSE);
}

/**
 * setAliasValue - Set alias value
 * @aliasName: Alias name
 * @aliasList: Pointer to the head of the alias list
 * @newValue: New value to set for the alias
 * This function sets the value of the specified alias in the given alias list.
 * If the alias exists, its value is updated with the new value.
 * If the alias doesn't exist, a new alias is created with the specified name
 * and value.
 * Return: TRUE if the alias value is set successfully, FALSE otherwise
 */
int setAliasValue(char *aliasName, Alias *aliasList, char *newValue)
{
	while (aliasList->next != NULL &&
			str_compare(aliasList->name, aliasName, MATCH) != TRUE)
	{
		aliasList = aliasList->next;
	}

	if (str_compare(aliasList->name, aliasName, MATCH) == TRUE)
	{
		free(aliasList->value);
	}
	else
	{
		aliasList->next = malloc(sizeof(Alias));
		aliasList = aliasList->next;
		if (aliasList == NULL)
			exit(EXIT_FAILURE);

		aliasList->name = malloc(_strlen(aliasName) + 1);
		_strcpy(aliasList->name, aliasName);
		aliasList->next = NULL;
	}
	aliasList->value = malloc(_strlen(newValue) + 1);
	_strcpy(aliasList->value, newValue);

	return (TRUE);
}
