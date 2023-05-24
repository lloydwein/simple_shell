#include "shell.h"

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
 *  @str: pointer string
 *  Return: pointer to the duplicated string str on success
 *  Returns NULL if str = NULL, if insufficient memory was available
 */

char *_strdup(char *str)
{
	char *dup_string;
	int number = 0;
	int size = 0;

	if (str == NULL)
	{
		return (NULL);
	}

	for (number = 0; *(str + number) != '\0'; number++)
		;

	dup_string = malloc(number * sizeof(char) + 1);

	if (dup_string == NULL)
	{
		return (NULL);
	}

	for (size = 0; size < number; size++)
	{
		dup_string[size] = str[size];
	}
	dup_string[number] = '\0';
	return (dup_string);
}

/**
 * _puts - prints a string, followed by a new line, to stdout
 * @str: string character
 * Description: a function
 * Return: void
 */

void _puts(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
	_putchar('\n');
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
