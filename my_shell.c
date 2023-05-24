#include "shell.h"

/**
 * main - The main shell code
 * @argc: Number of arguments passed
 * @argv: Program arguments to be parsed
 * This function implements a shell by applying various utility and helper
 * functions. It handles EOF, prints errors on failure, and executes commands
 * based on user input.
 * Return: 0 on success
 */

int main(int argc __attribute__((unused)), char **argv)
{
	char **commands = NULL;
	char *line = NULL;
	char *custom_name = NULL;
	int status = 0;
	char **curr_cmd = NULL;
	int index, cmd_type = 0;
	size_t line_length = 0;

	signal(SIGINT, ctrl_c_handler);
	custom_name = argv[0];
	while (1)
	{
		non_interactive();

		print(" ($) ", STDOUT_FILENO);
		if (getline(&line, &line_length, stdin) == -1)
		{
			free(line);
			exit(status);
		}

		remove_newline(line);
		remove_comment(line);
		commands = tokenizer(line, ";");
		for (index = 0; commands[index] != NULL; index++)
		{
			curr_cmd = tokenizer(commands[index], " ");
			if (curr_cmd[0] == NULL)
			{
				free(curr_cmd);
				break;
			}
			cmd_type = parse_command(curr_cmd[0]);
			initializer(curr_cmd, cmd_type);
			free(curr_cmd);
		}
		free(commands);
	}
	free(line);
	return (status);
}
