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

/**
 * _strtok_r - Thread-safe string tokenization function.
 * @str_to_tokenize: The string to tokenize.
 * @delimiter: The delimiter used for tokenization.
 * @save_ptr: Pointer to maintain the context of the string being tokenized.
 *
 * Return: A pointer to the next token, or NULL if no more tokens are found.
 */
char *_strtok_r(char *str_to_tokenize, char *delimiter, char **save_ptr)
{
	char *token_finish;

	if (str_to_tokenize == NULL)
		str_to_tokenize = *save_ptr;

	if (*str_to_tokenize == '\0')
	{
		*save_ptr = str_to_tokenize;
		return (NULL);
	}

	str_to_tokenize += _strspn(str_to_tokenize, delimiter);
	if (*str_to_tokenize == '\0')
	{
		*save_ptr = str_to_tokenize;
		return (NULL);
	}

	token_finish = str_to_tokenize + _get_segment_length(str_to_tokenize,
			delimiter);
	if (*token_finish == '\0')
	{
		*save_ptr = token_finish;
		return (str_to_tokenize);
	}

	*token_finish = '\0';
	*save_ptr = token_finish + 1;
	return (str_to_tokenize);
}
