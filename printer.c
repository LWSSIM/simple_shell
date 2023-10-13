#include "main.h"

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
* print_number - convert number to str & print it to fd
* @fd: file descriptor
* @x: number
*
* Return: int
*/
int print_number(int fd, int x)
{
	char buff;

	if (x >= 10)
		return (print_number(fd, x / 10) + print_number(fd, x % 10));
	buff = '0' + x;
	return (write(fd, &buff, 1));
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

/**
* error_printer - prints appropriate error
* @input: DS
* @error: DS
* @msg: error message
*/
void error_printer(Shell_commands *input, Error_handler *error, char *msg)
{
	print_to_fd(2, input->args[0]);
	print_to_fd(2, ": ");
	print_number(2, input->loop_counter);
	print_to_fd(2, ": ");
	if (!_strcmp(msg, "cannot open "))
	{
		print_to_fd(2, msg);
		print_to_fd(2, input->args[1]);
		error->exit_status = 2;
	}
	else if (!_strcmp(msg, "not found"))
	{
		print_to_fd(2, input->parsed[0]);
		print_to_fd(2, ": ");
		print_to_fd(2, msg);
		error->exit_status = 127;
	}
	else if (!_strcmp(msg, "exit: Illegal number: "))
	{
		print_to_fd(2, msg);
		print_to_fd(2, input->parsed[1]);
		error->exit_status = 2;
	}
	print_to_fd(2, "\n");
}

