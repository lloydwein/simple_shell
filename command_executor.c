#include "shell.h"

/**
 * initializer - Executes a command based on its type.
 * @cmd: The command to be executed.
 * @cmd_type: The type of the command.
 *
 * This function initializes and executes a command. If the command type is
 * either EXTERNAL_COMMAND or PATH_COMMAND, it forks a new process and executes
 * the command in the child process. The parent process waits for the child
 * process to complete and retrieves the exit status.
 * If the command type is not EXTERNAL_COMMAND or PATH_COMMAND, it executes the
 * command directly in the current process.
 * Return: void
 */
void initializer(char **cmd, int cmd_type)
{
	pid_t child_pid;
	int status;

	if (cmd_type == EXTERNAL_COMMAND || cmd_type == PATH_COMMAND)
	{
		child_pid = fork();
		if (child_pid == 0)
			execute_command(cmd, cmd_type);
		else
		{
			waitpid(child_pid, &status, 0);
			status >>= 8;
		}
	}
	else
		execute_command(cmd, cmd_type);
}
