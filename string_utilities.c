#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: character to be checked
 * Description: a function
 * Return: string length
 */

int _strlen(char *s)
{
	int lng = 0;

	while (*s != '\0')
	{
		s++;
		lng++;
	}
	return (lng);
}

/**
 * _strcpy - Copies the contents of source string to destination string
 * @source: The source string to be copied from
 * @dest: The destination string to copy to
 *
 * Return: void
 */
void _strcpy(char *source, char *dest)
{
	int index = 0;

	while (source[index] != '\0' && dest[index] != '\0')
	{
		dest[index] = source[index];
		index++;
	}

	if (dest[index] != '\0')
		dest[index] = '\0';
}
