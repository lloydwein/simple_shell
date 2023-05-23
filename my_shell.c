#include "shell.h"
/**
 * process_input - process the input line
 * @line: input line to process
 * @shell_name: shell name
 * @status: shell status
 */
void process_input(char *line, char *shell_name, int *status)
{
	char **commands = NULL;
	int command_type;

	remove_newline(line);
	remove_comment(line);
	commands = tokenizer(line, ";");

	for (int index = 0; commands[index] != NULL; index++)
	{
		char **tokenized_command = tokenizer(commands[index], " ");

		if (tokenized_command[0] == NULL)
		{
			free(tokenized_command);
			break;
		}
		command_type = parse_command(tokenized_command[0]);
		initializer(tokenized_command, command_type);
		free(tokenized_command);
	}

	free(commands);
}
/**
 * main - the main shell code
 * @argc: number of arguments passed
 * @argv: program arguments to be parsed
 *
 * applies the functions in utils and helpers
 * implements EOF
 * Prints error on Failure
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *line = NULL;
	char *shell_name = NULL;
	int status = 0;
	size_t line_buffer_size = 0;

	signal(SIGINT, ctrl_c_handler);
	shell_name = argv[0];

	while (1)
	{
		non_interactive();
		print_string(" ($) ", STDOUT_FILENO);

		if (getline(&line, &line_buffer_size, stdin) == -1)
		{
			free(line);
			exit(status);
		}
		process_input(line, shell_name, &status);

		free(line);
	}
	return (status);
}
