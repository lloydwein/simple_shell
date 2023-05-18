#include "main.h"

/**
 * print_alias - Prints the alias information
 * @alias: The alias structure to be printed
 *
 * Description: This function prints the name and value of an alias in the
 * format "<alias_name>='<alias_value>'\n".
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int length;

	alias_string = malloc(sizeof(char) * (length + 1));
	length = _strlen(alias->name) + _strlen(alias->value) + 4;
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, length);
	free(alias_string);
}
/**
 * set_alias - Sets the value of an alias
 * @alias_name: The name of the alias to be set
 * @alias_value: The value to be assigned to the alias
 *
 * Description: This function sets the value of an alias. It removes any
 * leading or trailing quotes from the alias_value and updates the value of an
 * existing alias or adds a new alias if it doesn't exist.
 */
void set_alias(char *alias_name, char *alias_value)
{
	alias_t *current_alias = aliases;
	int value_length, src_idx, dest_idx;
	char *new_value;

	*alias_value = '\0';
	alias_value++;
	value_length = _strlen(alias_value) - _strspn(alias_value, "'\"");
	new_value = malloc(sizeof(char) * (value_length + 1));
	if (!new_value)
		return;
	for (src_idx = 0, dest_idx = 0; alias_value[src_idx]; src_idx++)
	{
		if (alias_value[src_idx] != '\'' &&
				alias_value[src_idx] != '"')
			new_value[dest_idx++] = alias_value[src_idx];
	}
	new_value[dest_idx] = '\0';
	while (current_alias)
	{
		if (_strcmp(alias_name, current_alias->name) == 0)
		{
			free(current_alias->value);
			current_alias->value = new_value;
			break;
		}
		current_alias = current_alias->next;
	}
	if (!current_alias)
		add_alias_end(&aliases, alias_name, new_value);
}

/**
 * handle_alias_command - Handles alias commands in the shell
 * @args: The arguments passed to the command
 * @top: Unused parameter (for compatibility with shellby main function)
 * Description: This function handles alias commands in the shell. It prints
 * all aliases if no arguments are provided. If an argument matches an alias
 * name, it prints the corresponding alias. If an argument contains a "="
 * character, it sets an alias.
 *
 * Return: 0 on success, -1 on error.
 */
int handle_alias_command(char **args, char __attribute__((__unused__)) **top)
{
	alias_t *current_alias = aliases;
	int index, success = 0;
	char *value;

	if (!args[0])
	{
		while (current_alias)
		{
			print_alias(current_alias);
			current_alias = current_alias->next;
		}
		return (success);
	}
	for (index = 0; args[index]; index++)
	{
		current_alias = aliases;
		value = _strchr(args[index], '=');
		if (!value)
		{
			while (current_alias)
			{
				if (_strcmp(args[index], current_alias->name)
						== 0)
				{
					print_alias(current_alias);
					break;
				}
				current_alias = current_alias->next;
			}
			if (!current_alias)
				success = create_error(args + index, 1);
		}
		else
			set_alias(args[index], value);
	}
	return (success);
}

