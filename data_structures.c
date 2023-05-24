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

/**
 * _strcmp - compares two strings
 * Description: a function that compares the two strings s1 and s2
 * if Return value < 0 then it indicates str1 is less than str2
 * if Return value > 0 then it indicates str2 is less than str1
 * if Return value = 0 then it indicates str1 is equal to str2
 * @s1: first string to be compared
 * @s2: second string to be compared
 * Return: integer >0, <0 or =0
 */

int _strcmp(char *s1, char *s2)
{
	int index = 0, diff = 0;

	while (s1[index] != '\0' && s2[index] != '\0')
	{
		if (s1[index] != s2[index])
		{
			diff = s1[index] - s2[index];
			return (diff);
		}
		index++;
	}

	if (s1[index] != '\0' || s2[index] != '\0')
		diff = _strlen(s1) - _strlen(s2);

	return (diff);
}

/**
 * *_strcat - concatenates two strings
 * Description: a function that appends the src string to the dest string
 * overwriting the terminating null byte ('\0') at the end of dest
 * and then adds a terminating null byte
 * @dest: string to append src to
 * @src: the appending string
 * Return: pointer to the resulting string dest
 */

char *_strcat(char *dest, char *src)
{
	int a = 0, b = 0;

	while (dest[a++])
		b++;

	for (a = 0; src[a]; a++)
		dest[b++] = src[a];

	return (dest);
}

/**
 * _strspn - gets the length of a prefix substring
 * Description: a function that calculates the length of the initial segment of
 * s which consists entirely of characters in accept
 * @s: main C string to be scanned
 * @accept: string containing the list of characters to match in s
 * Return: number of characters in the initial segment of s which consist
 * only of characters from accept
 */

unsigned int _strspn(char *s, char *accept)
{
	int string;
	unsigned int counter = 0;

	while (*s)
	{
		for (string = 0; accept[string]; string++)
		{
			if (*s == accept[string])
			{
				counter++;
				break;
			}
			else if (accept[string + 1] == '\0')
			{
				return (counter);
			}
		}
		s++;
	}
	return (counter);
}
