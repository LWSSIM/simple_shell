#include "main.h"

/**
* exit_routine - exits shell normally
* @input: DS
* @error: DS
* Return: 1 if failure else exit with status
*/
int exit_routine(Shell_commands *input, Error_handler *error)
{
	int exit_status = error->exit_status;

	if (input->fd > 3 && input->file)
	{
		close(input->fd);
		fclose(input->file);
	}
	if (!_strcmp(input->parsed[0], "exit"))
	{
		if (!input->parsed[1])
		{
			free_shell(input, error);
			exit(exit_status);
		}
		else if (input->parsed[1][0] == '-')
		{/*fix error print*/
			error_printer(input, error, "exit: Illegal number: ");
			return (error->exit_status);
		}
		else if (!_isdigit(input->parsed[1][0]))
		{
			error_printer(input, error, "exit: Illegal number: ");
			return (error->exit_status);
		}
		else
		{
			exit_status = atoi(input->parsed[1]);
			free_shell(input, error);
			exit(exit_status);
		}
	}
	if (error->exit_status)
	{
		free_shell(input, error);
		exit(exit_status);
	}
	return (1);
}

/**
 * free_str_ar - free str array
 * @ar: array of strings
 */
void free_str_ar(char **ar)
{
	int index;

	if (!ar)
		return;
	for (index = 0; ar[index]; index++)
	{
		free(ar[index]);
		ar[index] = NULL;
	}
	free(ar);
	ar = NULL;
}

/**
 * free_shell - free Shell_commands DS
 * @input: pointer to DS
 * @error: pointer to DS
 */
void free_shell(Shell_commands *input, Error_handler *error)
{
	if (input->lineptr)
		free(input->lineptr);
	input->lineptr = NULL;
	if (input->parsed)
		free_str_ar(input->parsed);
	input->parsed = NULL;
	if (error->exit_msg)
		free(error->exit_msg);
	error->exit_msg = NULL;
}
