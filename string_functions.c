#include "main.h"

/**
 * _strspn - Calculates the length of the initial segment of the string 'str'
 * that consists entirely of characters from the string 'ch'.
 * @str: The string to calculate the length of the initial segment.
 * @ch: The string containing characters to be considered for the initial
 * segment
 * Return: The length of the initial segment of 'str' consisting of characters
 * from ch
 */
int _strspn(char *str, char *ch)
{
	/* Counter for the number of bytes in the initial segment */
	int byte = 0;
	int i;

	/* Iterate through each character in 'str' */
	while (*str)
	{
		/* Iterate through each character in 'ch' */
		for (i = 0; ch[i]; i++)
		{
			/*
			 * If the current character in 'str' matches a character
			 * in 'ch'
			 */
			if (*str == ch[i])
			{
				/* Increment the byte count */
				byte++;
				/* Exit the inner loop */
				break;
			}
		}
		/* Move to the next character in 'str' */
		str++;
	}
	/* Return the number of bytes in the initial segment */
	return (byte);
}

/**
 * _strcmp - Compares two strings and returns an integer value indicating
 * whether the first string is less than, equal to, or greater than the
 * second string.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 * Return: An integer value less than, equal to, or greater than zero,
 * indicating whether the first string is less than, equal to, or greater than
 * the second string.
 */
int _strcmp(char *str1, char *str2)
{
	/*
	 * Compare each character of the two strings until either of them end or
	 * they differ
	 */
	while (*str1 && *str2 && *str1 == *str2)
	{
		/* Move to the next character of the first string */
		str1++;
		/* Move to the next character of the second string */
		str2++;
	}

	/* If the two strings differ at some point */
	if (*str1 != *str2)
	{
		/* Return the difference between the two differing character */
		return (*str1 - *str2);
	}

	/* Return 0 if the two strings are identical */
	return (0);
}

/**
 * _strncmp - Compares at most 'n' characters of two strings and returns an
 * integer value indicating whether the first string is less than, equal to,
 * or greater than the second string.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 * @n: The maximum number of characters to compare.
 * Return: An integer value less than, equal to, or greater than zero,
 * indicating whether the first string is less than, equal to, or greater than
 * the second string.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	/*
	 * Compare each character of the two strings until either of them ends,
	 * 'n' characters are compared, or they differ
	 */
	for (i = 0; str1[i] && str2[i] && i < n; i++)
	{
		if (str1[i] > str2[i])
		{
			/* Return difference btw the two differing character */
			return (str1[i] - str2[i]);
		}
		else if (str1[i] < str2[i])
		{
			/* Return difference btw the two differing character */
			return (str1[i] - str2[i]);
		}
	}
	/* If 'n' characters have been compared and no differences found */
	if (i == n)
	{
		/* Return 0 to indicate equality */
		return (0);
	}
	else
		/* Return a non-zero value to indicate inequality */
		return (-15);
}
