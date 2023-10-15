#include "main.h"

/**
* _strdup - duplicate str to new allocated memory space
* @str: pointer to input string
* Return: pointer to new memory space && NULL if str = null
*/
char *_strdup(char *str)
{
	char *p;

	int i, size;

	if (str == 0)
		return (0);

	size = 0;
	while (str[size] != '\0')
		size++;

	p = malloc(sizeof(char) * (size + 1));
	if (p == 0)
		return (0);

	for (i = 0; i < size; i++)
	{
		p[i] = str[i];
	}
	p[size] = '\0';
	return (p);
}
/**
* _isspace - check if char is space
* @c: input
* Return: bool
*/
bool _isspace(char c)
{
	return (c == ' ' ||
			c == '\t' ||
			c == '\n' ||
			c == '\r' ||
			c == '\v' ||
			c == '\f');
}
/**
* _putchar - prints char to stdout w/write()
* @c: input char
* Return: 1 success || -1 error
*/
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
* check_space - check for non_white spcae
* @str: input
* @chars_read: nbr of chars
* Return: i
*/
int check_space(char *str, ssize_t chars_read)
{
	int i = 0;

	ssize_t j;

	for (j = 0; j < chars_read; j++)
	{
		if (!_isspace(str[j]))
		{
			i = 1;
			break;
		}
	}
	return (i);
}

/**
* _isdigit - check if input is digit
* @c: input
* Return: 1 yes? || 0 no?
*/
int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
