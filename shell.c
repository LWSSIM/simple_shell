#include "main.h"
/**
* inter - run interactive mode
* @input: DS
* @error: DS
* Return: status
*/
int inter(Shell_commands *input, Error_handler *error)
{
	ssize_t chars_read;
	size_t n = 0;
	int stat = 0;
	char delimiter[] = " \n\t";

	signal(SIGINT, usr_interupt);
	do {
		++input->loop_counter;
		print_to_fd(1, input->current_dir);
		print_to_fd(1, PROMPT_MSG);
		chars_read = _getline(&input->lineptr, &n, stdin);
		if (chars_read == EOF) /*escape if EOF||-1*/
		{
			write(1, "\n", 1);
			free_shell(input, error);
			free(input->current_dir);
			return (stat);
		}
		if (check_space(input->lineptr, chars_read))
		{
			input->parsed = get_token(input->lineptr, delimiter);
			stat = exec_process(input, error); /*create and execute new process*/
			free_shell(input, error);
		}
	} while (chars_read != EOF);
	return (stat);
}

/**
* non_inter - run non_interactive mode
* @input: DS
* @error: DS
* Return: status
*/
int non_inter(Shell_commands *input, Error_handler *error)
{
	ssize_t chars_read;
	size_t n = 0;
	int stat = 0;

	char delimiter[] = " \n\t";


	do {
		++input->loop_counter;
		if (!input->file)
			chars_read = _getline(&input->lineptr, &n, stdin);
		else
			chars_read = _getline(&input->lineptr, &n, input->file);
		if (chars_read == EOF) /*escape if EOF||-1*/
		{
			free_shell(input, error);
			free(input->current_dir);
			break;
		}
		if (check_space(input->lineptr, chars_read))
		{
			input->parsed = get_token(input->lineptr, delimiter);
			stat = exec_process(input, error); /*create and execute new process*/
			free_shell(input, error);
		}
	} while (chars_read != EOF);
	if (input->file)
		fclose(input->file);

	return (stat);
}

/**
* Shell_loop - Main REPL shell loop
* @input: DS
* @error: DS
*
* Return: status
*/
int Shell_loop(Shell_commands *input, Error_handler *error)
{
	int status = 0;

	while (1)
	{
		if (!isatty(0) || input->arg_count > 1)
		{
			status = non_inter(input, error);
			return (status);
		}
		else
		{
			status = inter(input, error);
			return (status);
		}
	}
}
/**
* routine - Innitialise data structures
* @input: DS
* @error: DS
* @ac: arg count
* @av: arv vector
*/
void routine(Shell_commands *input, Error_handler *error, int ac, char **av)
{
	input->arg_count = ac;
	input->args = av;
	input->parsed = NULL;
	input->lineptr = NULL;
	input->current_dir = NULL;
	input->file = 0;
	input->loop_counter = 0;
	input->current_dir = getcwd(NULL, 0);

	if (input->arg_count > 1)
	{
		input->file = fopen(av[1], "r");
		if (input->file == NULL)
		{
			if (access(av[1], F_OK) != 0)
			{
				error_printer(input, error, NULL);
				print_to_fd(2, "Can't open ");
				print_to_fd(2, av[1]);
				print_to_fd(2, "\n");
				exit(127);
			}
			error_printer(input, error, "cannot open ");
			exit(EXIT_FAILURE);
		}
	}
	error->exit_msg = NULL;
	error->exit_status = 0;
}
/**
* main - entry point for the shell
* @ac: arg count
* @av:arg vector
*
* Return: status
*/
int main(int ac, char **av)
{
	int status = 0;

	Shell_commands input;
	Error_handler error;

	/*innit structs*/
	routine(&input, &error, ac, av);
	/*run REPL*/
	status = Shell_loop(&input, &error);

	return (status);
}
