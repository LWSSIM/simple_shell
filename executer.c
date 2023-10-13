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

	if (!built_in_checker(input, error))
		return (0);
	if (input->parsed_input)
	{
		cmd_fp = _getcom(input->parsed_input[0]);
		if (cmd_fp)
		{
			status = _fork(cmd_fp, input->parsed_input);
			free(cmd_fp);
			return (status);
		}
		else
		{
			error_printer(input, error, "not found");
			return (error->exit_status);
		}
	}
	return (1);
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
	}
	return (status);
}

/**
* usr_interupt - handle ctrl^c
* @signal: input signal
*/
void usr_interupt(int signal)
{
	if (signal == SIGINT) /*ctrl^c check*/
	{
		_putchar('\n');
		print_to_fd(1, PROMPT_MSG);
	}
}
