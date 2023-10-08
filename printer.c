#include "main.h"

/**
* exit_routine - exits shell normally
* @input: DS
* @error: DS
*/
void exit_routine(Shell_commands *input, Error_handler *error)
{
	int exit_status = 0;

	if (input->fd > 3)
		close(input->fd);

	if (!_strcmp(input->parsed_input[0], "exit"))
	{
		if (!input->parsed_input[1])
		{
			free_shell(input, error);
			exit(exit_status);
		}
		else
		{
			exit_status = atoi(input->parsed_input[1]);
			free_shell(input, error);
			exit(exit_status);
		}
	}
	if (error->exit_status)
	{
		exit_status = error->exit_status;
		/*print_error(input, error);*/
		free_shell(input, error);
		exit(exit_status);
	}
}

/**
* print_to_fd - print msg to fd
* @str: msg
* @fd: file descriptor number
* Return: nb written chars
*/
int print_to_fd(int fd, char *str)
{
	return (write(fd, str, _strlen(str)));
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

/**
* print_env - print environ variable
* Return: nothing
*/
void print_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		print_to_fd(1, environ[i]);
		write(1, "\n", 1);
	}
}

