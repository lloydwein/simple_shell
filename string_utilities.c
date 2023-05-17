#include "main.h"

/**
 * _strlen - returns the length of a string
 * @s: the string to be measured
 * Return: the length of the string
 */
int _strlen(const char *s)
{
	int length = 0;

	/* check for a NULL pointer */
	if (!s)
	{
		return (length);
	}

	/**
	 * Iterate over the string, incrementing the length each time a
	 * non-null character is encountered
	 */
	for (; *s; s++)
	{
		length++;
	}

	/* Return the length of the string. */
	return (length);
}

/**
 * _strcpy - Copies a string.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the destination string.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	/* Check for NULL pointers. */
	if (!dest || !src)
	{
		return (dest);
	}

	/**
	 * Iterate over the source string, copying each character to the
	 * destination string
	 */
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	/* Terminate the destination string with a null character. */
	dest[i] = '\0';

	/* Return a pointer to the destination string. */
	return (dest);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: Pointer to the resulting string @dest.
 */
char *_strcat(char *dest, const char *src)
{
	char *dest_ptr = dest;
	const char *src_ptr = src;

	/**
	 * Iterate over the destination string, copying characters from the
	 * source string until the end of the source string is reached
	 */
	while (*dest_ptr != '\0')
	{
		dest_ptr++;
	}

	while (*src_ptr != '\0')
	{
		*dest_ptr++ = *src_ptr++;
	}

	/* Terminate the destination string with a null character */
	*dest_ptr = '\0';

	/* Return a pointer to the destination string */
	return (dest);
}

/**
 * _strncat - Concatenates at most 'n' characters from the string 'src' to the
 * end of the string 'dest'.
 * @dest: The destination string to append to.
 * @src: The source string to append from.
 * @n: The maximum number of characters to append.
 * Return: A pointer to the resulting string 'dest'.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_length = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[dest_length + i] = src[i];
	}

	dest[dest_length + i] = '\0';

	return (dest);
}

/**
 * _strchr - Finds the first occurrence of a character in a string.
 * @str: The string to be searched.
 * @ch: The character to be found.
 * Return: A pointer to the first occurrence of the character in the string,
 * or NULL if the character is not found.
 */
char *_strchr(char *str, char ch)
{
	int i;

	/* Iterate through each character in the string */
	for (i = 0; str[i]; i++)
	{
		/* If the current character matches the target character */
		if (str[i] == ch)
			/* Return a pointer to the matching character */
			return (str + i);
	}

	/* Return NULL if the character is not found */
	return (NULL);
}
