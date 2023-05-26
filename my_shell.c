#include "shell.h"

/**
 * main - entry point of terminal
 * @ac: args count
 * @av: args value
 * Return: success or failure
 */
int main(__attribute__((unused))int ac, char **av)
{
	int bytes_read;
	int is_separated = FALSE;
	int i;
	size_t buf_size = 1;
	char *buf = NULL;
	char *buf_ptr;
	char *buf_tmp;
	char **args = NULL;

	shell_name = _strdup(*av);
	environ = copyStringArray(environ, list_len(environ, NULL));
	signal(SIGINT, SIG_IGN);
	buf = malloc(1);
	if (buf == NULL)
		exit(EXIT_FAILURE);

	while (1)
	{
		if (is_separated == FALSE)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(STDOUT_FILENO, "my_shell$ ", 10);

			bytes_read = getline(&buf, &buf_size, stdin);

			if (bytes_read == -1)
				break;
			if (bytes_read == 1)
			{
				line_num++;
				continue;
			}
			buf[bytes_read - 1] = '\0';
			buf = sanitize_input(buf, &buf_size);
			if (buf_size == 0)
			{
				line_num++;
				continue;
			}
			buf_ptr = buf;
		}
		else
			buf_ptr = buf_tmp;

		buf_tmp = NULL;
		args = splitString(buf_ptr, ' ', &buf_tmp);
		if (buf_tmp != NULL)
			is_separated = TRUE;
		else
			is_separated = FALSE;

		i = command_manager(args);

		free(args);

		if (is_separated == FALSE)
			line_num++;

		if (i == EXIT_SHELL)
			break;
	}
	free(buf);
	handle_alias_command(NULL, TRUE);
	freeStringArray(environ);
	free(shell_name);

	return (status % 256);
}
