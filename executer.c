#include "main.h"

/**
* exec_process - create new process then execute w/execve
* @error: DS
* @input: input command
*
* Return: int
*/
int exec_process(Shell_commands *input, Error_handler *error)
{
	int status = 0;

	char *cmd_fp = NULL;

	if (built_in_checker(input, error) != -1)
		return (error->exit_status);
	if (input->parsed)
	{
		cmd_fp = _getcom(input->parsed[0]);
		if (cmd_fp)
		{
			status = _fork(cmd_fp, input->parsed);
			if (cmd_fp != input->parsed[0])
				free(cmd_fp);
			error->exit_status = status;
			return (status);
		}
		else
		{
			error_printer(input, error, "not found");
			return (error->exit_status);
		}
	}
	return (0);
}

/**
* _fork - fork and exec a cmd if valid
* @cmd_fp: command full path
* @input: user input
*
* Return: int
*/
int _fork(char *cmd_fp, char **input)
{
	int status;

	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		print_to_fd(2, "./hsh: process creation failed\n");
	}
	else if (pid == 0)
	{
		if (execve(cmd_fp, input, environ) == -1)
		{
			print_to_fd(2, "./hsh: process execution failed\n");
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	return (status);
}

/**
* usr_interupt - handle ctrl^c
* @signal: input signal
*/
void usr_interupt(int signal)
{
	char *buf;

	if (signal == SIGINT) /*ctrl^c check*/
	{
		buf = getcwd(NULL, 0);
		_putchar('\n');
		print_to_fd(1, buf);
		free(buf);
		print_to_fd(1, PROMPT_MSG);
	}
}
