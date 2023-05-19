#include "shell.h"

/**
 * *_strchr -  locates a character in a string
 * Description: a function that searches for the first occurrence of the
 * character c (an unsigned char) in the string pointed to by the argument s
 * @s: C string to be scanned
 * @c: character to be searched in s
 * Return: pointer to the first occurrence of the character c
 * in the string s, or NULL if the character is not found
 */

char *_strchr(char *s, char c)
{
	char *string;

	string = s;
	while (*string != c)
	{
		if (*string == 0)
			return (0);
		string++;
	}
	return (string);
}
