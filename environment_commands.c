#include "shell.h"

/**
 * print_environment - prints the current environment
 * @command_tokens: command entered
 *
 * Return: void
 */
void print_environment(char **command_tokens __attribute__((unused)))
{
	int index;

	for (index = 0; environ[index] != NULL; index++)
	{
		print_string(environ[index], STDOUT_FILENO);
		print_string("\n", STDOUT_FILENO);
	}
}

/**
 * quit_shell - Exit the shell
 * @command_tokens: Command tokens entered
 *
 * Return: void
 */
void quit_shell(char **command_tokens)
{
	char *line = NULL;
	char **commands = NULL;
	int num_tokens = 0, args;

	for (; command_tokens[num_tokens] != NULL; num_tokens++)
		;

	if (num_tokens == 1)
	{
		free(command_tokens);
		free(line);
		free(commands);
		exit(status);
	}
	else if (num_tokens == 2)
	{
		args = _atoi(command_tokens[1]);

		if (args == -1)
		{
			print_string(shell_name, STDERR_FILENO);
			print_string(": 1: exit: Illegal number: ",
					STDERR_FILENO);
			print_string(command_tokens[1], STDERR_FILENO);
			print_string("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(line);
			free(command_tokens);
			free(commands);
			exit(args);
		}
	}
	else
	{
		print_string("$: exit doesn't take more than one argument\n",
				STDERR_FILENO);
	}
}
