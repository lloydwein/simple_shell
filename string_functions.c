#include "shell.h"

/**
 * *_strncpy - copies a string
 * Description: a function that copies the string pointed to by src,
 * including the terminating null byte ('\0'), to the buffer pointed to by dest
 * @dest: pointer to the destination array where the content is to be copied
 * @src: string to be copied
 * @n: number of characters to be copied from source
 * Return: pointer to the destination string dest
 */

char *_strncpy(char *dest, char *src, int n)
{
	int a;

	for (a = 0; a < n && src[a] != '\0'; a++)
		dest[a] = src[a];

	for (; a < n; a++)
		dest[a] = '\0';

	return (dest);
}

/**
 * print_string - Prints a string to the specified stream
 * @string_to_print: The string to be printed
 * @output_stream: The stream to print the string to
 *
 * Return: void
 */
void print_string(char *string_to_print, int output_stream)
{
	int index = 0;

	for (; string_to_print[index] != '\0'; index++)
		write(output_stream, string_to_print,
				_strlen(string_to_print));

}

/**
 * _strncat - concatenates two strings
 * Description: a function similar to strcat except that
 * it will use at most n bytes from src; and src does not need to be
 * null-terminated if it contains n or more bytes
 * As with strcat(), the resulting string in dest is always null-terminated
 * @dest: string to append src to
 * @src: the appending string
 * @n: number of bytes
 * Return: pointer to the resulting string dest
 */

char *_strncat(char *dest, char *src, int n)
{
	int a = 0, b = 0;

	while (dest[a++])
		b++;

	for (a = 0; src[a] && a < n; a++)
		dest[b++] = src[a];

	return (dest);
}

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
