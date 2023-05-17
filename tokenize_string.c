#include "main.h"

/**
 * get_token_length - Calculates the length of a token in a string until a
 * delimiter is encountered.
 * @str: The string to analyze.
 * @delimiter: The delimiter character.
 * Return: The length of the token until the delimiter is encountered.
 */
int get_token_length(char *str, char *delimiter)
{
	/* Index ofr traversing the string */
	int index = 0;
	/* Lenth of the token */
	int length = 0;

	/* Loop until end of string or delimiter is found */
	while (*(str + index) && *(str + index) != *delimiter)
	{
		/* Increment token length */
		length++;
		/* Move to the next character in the string */
		index++;
	}

	/* Return the length of the token */
	return (length);
}

/**
 * get_num_tokens - Count the number of tokens in a string based on a delimiter
 * @line: The string to be tokenized.
 * @delimiter: The delimiter character.
 * Return: The number of tokens.
 */
int get_num_tokens(char *line, char *delimiter)
{
	int numTokens = 0;
	int currentIndex = 0;

	while (line[currentIndex])
	{
		while (line[currentIndex] == *delimiter)
			currentIndex++;
		if (line[currentIndex])
		{
			numTokens++;
			currentIndex += get_token_length(line + currentIndex,
					delimiter);
		}
	}
	return (numTokens);
}

/**
 * copy_token - Copies a token from the source string to a new dynamically
 * allocated memory
 * @src: The source string containing the token.
 * @start: The starting index of the token.
 * @end: The ending index of the token.
 * Return: The dynamically allocated memory containing the token.
 */
char *copy_token(char *src, int start, int end)
{
	int length = end - start;
	char *token = malloc(sizeof(char) * (length + 1));
	int i;

	if (!token)
		return (NULL);

	for (i = 0; i < length; i++)
		token[i] = src[start + i];

	token[length] = '\0';

	return (token);
}

/**
 * tokenize_string - Tokenizes a string based on a delimiter and returns an
 * array of tokens
 * @line: The string to be tokenized.
 * @delimiter: The delimiter character
 * Return: An array of tokens (char**) or NULL if there are no tokens or if
 * memory allocation fails.
 */
char **tokenize_string(char *line, char *delimiter)
{
	char **tokens;
	int currentIndex = 0;
	int numTokens = get_num_tokens(line, delimiter);
	int tokenIndex, tokenLength, letterIndex, start, end;

	/* Count the number of tokens in the string */
	if (numTokens == 0)
		return (NULL);
	/* Allocate memory for the array of tokens */
	tokens = malloc(sizeof(char *) * (numTokens + 2));
	if (!tokens)
		return (NULL);
	tokenIndex = 0;
	while (line[currentIndex])
	{
		/* Skip delimiter characters */
		while (line[currentIndex] == *delimiter)
			currentIndex++;

		if (line[currentIndex])
		{
			start = currentIndex;
			end = start + get_token_length(line + currentIndex,
					delimiter);
			tokens[tokenIndex] = copy_token(line, start, end);
			if (!tokens[tokenIndex])
			{
				for (letterIndex = tokenIndex - 1;
						letterIndex >= 0; letterIndex--)
					free(tokens[letterIndex]);
				free(tokens);
				return (NULL);
			}
			tokenIndex++;
			currentIndex = end;
		}
	}
	/* Set the last element of the array to NULL to mark the end */
	tokens[tokenIndex] = NULL;
	return (tokens);
}
