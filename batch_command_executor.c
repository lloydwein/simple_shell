#include "shell.h"

/**
 * non_interactive - Process non-interactive commands.
 *
 * This function reads commands from stdin in non-interactive mode and executes
 * them. It removes newline characters and comments from the input commands,
 * tokenizes them, and executes each command using the initializer function.
 * The function exits with the appropriate status after processing all commands
 */
void non_interactive(void)
{
	char **commands = NULL;
	char **curr_cmd;
	char *line = NULL;
	size_t line_length = 0;
	int status = 0;
	int index, cmd_type = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&line, &line_length, stdin) != -1)
		{
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
		exit(status);
	}
}
