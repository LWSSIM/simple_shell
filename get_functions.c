#include "main.h"

/**
* _getline - read line from stream
* @lineptr: ptr->line
* @n: lenght
* @stream: file strem
* Description:
* -stores address of bfr to *lineptr
* -*lineptr and *n are updated on success
* Return: nmbr of chars read || -1 on fail
*/
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t bfrsz = 257;
	size_t position = 0;
	int c;

	if (*lineptr == NULL || *n == 0)
	{
		*n = bfrsz;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	while (1)
	{
		c = fgetc(stream);
		if (c == EOF)
		{
			break;
		}
		if (position >= *n - 1)
		{
			bfrsz *= 2;
			*n = bfrsz;
			*lineptr = (char *)realloc(*lineptr, *n);
			if (*lineptr == NULL)
				return (-1);
		}
		(*lineptr)[position++] = c;
		if (c == '\n')
			break;
	}
	if (position == 0 && c == EOF)
		return (-1);
	(*lineptr)[position] = '\0';
	return (position);
}

/**
* _getenv - retreives global env variable (char **env == environ)

* @var_name: passed variable
* Return: ptr->str (found value) || NULL
*/
char *_getenv(char *var_name)
{
	int i = 0;

	char *var_key, *env_copy, *var_value, *value_copy;

	while (environ[i])
	{
		env_copy = malloc(_strlen(environ[i]) + 1);
		_strcpy(env_copy, environ[i]);
		var_key = strtok(env_copy, "=");
		if (_strcmp(var_name, var_key) == 0)
		{
			var_value = strtok(NULL, "\0");
			if (!var_value)
			{
				free(env_copy);
				return ('\0');
			}
			value_copy = malloc(_strlen(var_value) + 1);
			_strcpy(value_copy, var_value);
			free(env_copy);
			return (value_copy);
		}
		free(env_copy);
		i++;
	}
	return (NULL);
}

/**
* _getcom - retreive command if found from PATH
* @cmd: passed usr command (short)
* Return: ptr->str (found full command in path)
*/
char *_getcom(char *cmd)
{
	char *token = NULL, *cp, *command = NULL, *path = _getenv("PATH");

	/*struct stat: special C structure (checker)*/
	struct stat st;

	if (!path)
	{
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	else if (*path == '\0')
	{
		print_to_fd(1, "NULL path");
		return (NULL);
	}
	else
	{
		cp = _strdup(path);
		free(path);
		token = strtok(cp, ":");
	}
	while (token != NULL)
	{
		if (!_strstr(cmd, "/"))
		{/*malloc full_cmd(token + usr cmd + / + \0)*/
			command = malloc(_strlen(token) + _strlen(cmd) + 2);
			_strcpy(command, token);
			_strcat(command, "/");
			_strcat(command, cmd);
			_strcat(command, "\0");
		}
		else
			command = _strdup(cmd);
		if (stat(command, &st) == 0)
		{
			free(cp);
			return (command); /*full cmd from path*/
		}
		free(command);
		token = strtok(NULL, ":"); /*check next value*/
	}
	free(cp);
	return (NULL);/*usr cmd not found in path*/
}

/**
* get_token - splits string into words using (strtok)
* @input: passed input line
* @delimiter: passed delilimiter
* Return: array of words
*/
char **get_token(char *input, const char *delimiter)
{
	/*Count the number of words in the input string*/
	unsigned int w_count = 0, index = 0;

	char *copy = _strdup(input);

	char *token = NULL;

	char **words = NULL;

	if (copy == NULL)
	{
		print_to_fd(2, "Memory allocation error 1");
	}
	token = strtok(copy, delimiter);
	while (token)
	{
		w_count++;
		token = strtok(NULL, delimiter);
	}
	w_count++; /*for NULL*/
	free(copy);
	/*Allocate memory for the array of subsequent words*/
	words = malloc(((sizeof(char *) * w_count) + 1));
	if (words == NULL)
	{
		print_to_fd(2, "Memory allocation error 2");
	}
	/*Split the input string and store the words in the array*/
	copy = _strdup(input);
	token = strtok(copy, delimiter);
	while (token != NULL)
	{
		words[index] = malloc((sizeof(char) * (_strlen(token))) + 1);
		_strcpy(words[index], token);
		token = strtok(NULL, delimiter);
		index++;
	}
	words[index] = NULL;

	free(copy);
	return (words);/*free when called*/
}

/**
* built_in_checker - check for builtins and run them
* @input: DS
* @error: DS
*
* Return: int
*/
int built_in_checker(Shell_commands *input, Error_handler *error)
{
	if (!_strcmp(input->parsed_input[0], "exit"))
	{
		if (exit_routine(input, error) == 1)
			return (0);
	}
	else if (!_strcmp(input->parsed_input[0], "env"))
	{
		print_env();
		return (0);
	}

	return (1);
}
