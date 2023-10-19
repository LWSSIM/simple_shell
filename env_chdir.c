#include "main.h"

/**
* print_env - print environ variable
* Return: nothing
*/
void print_env(void)
{
	unsigned int i;

	for (i = 0; environ[i]; i++)
	{
		print_to_fd(1, environ[i]);
		write(1, "\n", 1);
	}
}


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
		return (0);
	}
	else
	{
		if (setenv(input->parsed[1], input->parsed[2], 1) == -1)
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
		return (0);
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

/**
* change_dir - handles the CD command
* @input: DS
* @error: DS
*
* Return: int
*/
int change_dir(Shell_commands *input, Error_handler *error)
{
	char *dir_path, *old_dir = _strdup(input->current_dir);

	if (!input->parsed[1] || !_strcmp(input->parsed[1], "~"))
		dir_path = _getenv("HOME");
	else if (!_strcmp(input->parsed[1], "-"))
	{
		dir_path = _getenv("OLDPWD");
		print_to_fd(1, dir_path);
		print_to_fd(1, "\n");
	}
	else if (input->parsed[1])
		dir_path = _strdup(input->parsed[1]);
	if (chdir(dir_path) == -1)
	{
		error->exit_status = errno;
		error_printer(input, error, NULL);
		print_to_fd(2, "cd: ");
		perror(dir_path);
		free(old_dir);
		free(dir_path);
		return (error->exit_status);
	}
	free(dir_path);
	free(input->current_dir);
	input->current_dir = getcwd(NULL, 0);
	if (setenv("PWD", input->current_dir, 1) == -1)
	{
		error->exit_status = errno;
		free(old_dir);
		return (error->exit_status);
	}
	if (setenv("OLDPWD", old_dir, 1) == -1)
	{
		error->exit_status = errno;
		free(old_dir);
		return (error->exit_status);
	}
	free(old_dir);
	return (error->exit_status);
}
