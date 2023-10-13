#include "main.h"

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
	if (input->parsed_input)
		free_str_ar(input->parsed_input);
	input->parsed_input = NULL;
	if (error->exit_msg)
		free(error->exit_msg);
	error->exit_msg = NULL;
}
