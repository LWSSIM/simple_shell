#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stddef.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>

#define MAX_ARGS 10 /* maximum of accepted arguments*/
/*Promt message*/
#define PROMPT_MSG "($) "

/*array of pointers to environment variables*/
extern char **environ;

/*---Structures---*/
/**
* struct Shell_commands - structure to handle passed commands
* @lineptr: line read from stdin
* @args: array of entered commands
* @parsed_input: parsed input line
* @arg_count: number of passed args
* @fd: file descriptor
*/
typedef struct Shell_commands
{
	char *lineptr;

	char **parsed_input;

	char **args;

	int arg_count;

	int fd;

} Shell_commands;

/**
* struct Error_handler - structure to handle and pass error(status/msg)
* @exit_msg: str to print to strerr
* @exit_status: exit status number
*/
typedef struct Error_handler
{
	char *exit_msg;

	int exit_status;

} Error_handler;

/*---Functions---*/
/*shell.c---[Shell entry point]*/
int main(int ac, char **av);
/*shell.c---[DS init]*/
void routine(Shell_commands *input, Error_handler *error, int ac, char **av);
/*shell.c---[Shell main RPEL loop]*/
int Shell_loop(Shell_commands *input, Error_handler *error);
/*shell.c---[normal mode]*/
int non_inter(Shell_commands *input, Error_handler *error);
/*shell.c---[interactive mode]*/
int inter(Shell_commands *input, Error_handler *error);

/*get_functions*/
char *_getcom(char *cmd);
char *_getenv(char *var_name);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char **get_token(char *input, const char *delimiter);

/*executer.c*/
int exec_process(Shell_commands *input, Error_handler *error);
int _fork(char *cmd_fp, char **input);

/*printer.c---[Write str to fd]*/
int print_to_fd(int fd, char *str);
void usr_interupt(int signal);
void exit_routine(Shell_commands *, Error_handler *);
void print_env(void);

/*memory.c---[free str]*/
void free_str_ar(char **ar);
/*memory.c---[free Data structs]*/
void free_shell(Shell_commands *input, Error_handler *error);


/*str_functions*/
char *_strstr(char *haystack, char *needle);
int _strlen(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
bool _isspace(char c);
int _putchar(char c);
int check_space(char *str, ssize_t chars_read);
#endif /*MAIN_H*/