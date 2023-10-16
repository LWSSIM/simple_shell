#include "main.h"

/**
 * _strstr - locate substring needle, in string haystack
 * @haystack: pointer to str searched
 * @needle: pointer to substring to locate
 * Return: 0 || pointer to found needle occurence
 */
char *_strstr(char *haystack, char *needle)
{
	int i, j;

	if (*needle == '\0' && *haystack == '\0')
		return (NULL);

	for (i = 0; haystack[i] != '\0'; i++)
	{
		if (haystack[i] == needle[0])
		{
			for (j = 0; needle[j] != '\0'; j++)
			{
				if (haystack[i + j] != needle[j])
					break;
			}
			if (needle[j] == '\0')
				return (&(haystack[i]));
		}
	}
	return (NULL);
}
/**
 * _strlen - calc lenght of str
 * @str: input
 * Return: int
 */
int _strlen(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}
/**
 * _strcat -  append 2 strings
 * @dest: pointer to storring adress
 * @src: pointer to source adress
 * Return: appended str
 */
char *_strcat(char *dest, char *src)
{
	char *p = dest;

	while (*p != '\0')
		++p;

	while (*src != '\0')
	{
		*p = *src;
		++p;
		++src;
	}
	*p = '\0';

	return (dest);
}
/**
 * _strcpy - copy src str in dest
 * @dest:pointer to destination str
 * @src:pointer to source str
 * Return: &dest
 */
char *_strcpy(char *dest, char *src)
{
	char *p = dest;

	while ((*dest++ = *src++) != '\0')
		;
	return (p);
}
/**
 * _strcmp - compare 2 strings
 * @s1:string 1
 * @s2:string 2
 * Return: - || 0 || + if < || == || >
 */
int _strcmp(char *s1, char *s2)
{
	if (!s1)
		return (-1);
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
