#include "main.h"

/**
* _setenv - sets a new environ variable (key=value) pair
* @input: DS
* @error: DS
* Return: error or 0
*/
int _setenv(Shell_commands *input, Error_handler *error)
{
	if (!input->parsed[1] || !input->parsed[2])
	{
		error_printer(input, error, "usage: setenv VARIABLE VALUE");
		return (error->exit_status);
	}
	else
	{
		if (setenv(input->parsed[1], input->parsed[2], 0) == -1)
		{
			error->exit_status = errno;
			return (error->exit_status);
		}
	}
	return (0);
}

/**
* _unsetenv - unset env var if found
* @input: DS
* @error: DS
* Return: error or 0
*/
int _unsetenv(Shell_commands *input, Error_handler *error)
{
	if (!input->parsed[1])
	{
		error_printer(input, error, "usage: unsetenv VARIABLE");
		return (error->exit_status);
	}
	else
	{
		if (unsetenv(input->parsed[1]) == -1)
		{
			error->exit_status = errno;
			return (error->exit_status);
		}
	}
	return (0);
}
