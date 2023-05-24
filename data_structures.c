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
	int in = 0, a = 0;

	while (s1[a] != '\0' && s2[a] != '\0')
	{
		if (s1[a] != s2[a])
		{
			in = s1[a] - s2[a];
			return (in);
		}
		a++;
	}

	return (in);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
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
