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
 * *_strcpy - copies the string pointed to by src, including the terminating
 * null byte (\0), to the buffer pointed to by dest
 * @src: string pointer
 * @dest: array
 * Description: a funcyion
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;
	int lng = 0;

	while (src[a] != '\0')
	{
		a++;
	}

	lng = a;
	for (a = 0; a < lng && src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	for ( ; a <= lng; a++)
	{
		dest[a] = '\0';
	}
	return (dest);
}

/**
 * *_strdup -  returns a pointer to a newly allocated space in memory
 *  which contains a copy of the string given as a parameter
 *  Description: a function that returns a pointer to a null-terminated byte
 *  string which is a duplicate of the string pointed to by str.
 *  The memory obtained is done dynamically using malloc and
 *  hence it can be freed using free()
 *
 *  @src: pointer string
 *  Return: pointer to the duplicated string str on success
 *  Returns NULL if str = NULL, if insufficient memory was available
 */

char *_strdup(char *src)
{
	int len = _strlen(src);
	char *dest = malloc(len + 1);
	char *ptr;

	if (src == NULL)
		return (NULL);
	if (dest == NULL)
		exit(EXIT_FAILURE);

	ptr = dest;

	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	*ptr = '\0';

	return (dest);
}

/**
 * *str_concat - concatenates two strings
 * Description: a function that concatenates the destination string and the
 * source string and the result is stored in the destination string
 * The returned pointer should point to a newly allocated space in memory which
 * contains the contents of s1, followed by the contents of s2
 * and null terminated
 *
 * @s1: pointer to the destination array, which should contain a C string
 * and should be large enough to contain the concatenated resulting string.
 * @s2: This is the string to be appended. This should not overlap the
 * destination.
 * Return: pointer to the resulting string s1
 */

char *str_concat(char *s1, char *s2)
{
	int len1 = (s1 != NULL) ? _strlen(s1) : 0;
	int len2 = (s2 != NULL) ? _strlen(s2) : 0;
	int len = len1 + len2;
	char *dest = malloc(len + 1);
	char *ptr = dest;

	if (dest == NULL)
	{
		exit(EXIT_FAILURE);
	}
	if (s1 != NULL)
	{
		while (*s1 != '\0')
		{
			*ptr = *s1;
			ptr++;
			s1++;
		}
	}
	if (s2 != NULL)
	{
		while (*s2 != '\0')
		{
			*ptr = *s2;
			ptr++;
			s2++;
		}
	}
	*ptr = '\0';
	return (dest);
}

/**
 * str_compare - compare two string
 * @s1: first string
 * @s2: second string
 * @pref_or_match: prefix
 * Return: difference between strings
 */
int str_compare(char *s1, char *s2, int pref_or_match)
{
	if (s1 == NULL || s2 == NULL)
		return (FALSE);

	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (FALSE);

		s1++;
		s2++;
	}

	if (pref_or_match == PREFIX)
		return (TRUE);

	if (*s1 == *s2)
		return (TRUE);

	return (FALSE);
}
