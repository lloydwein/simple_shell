#include "shell.h"

/**
 * tokenize_string - Tokenizes a string based on a delimiter
 * @str_to_tokenize: The input string to be tokenized
 * @delimiter: The delimiter used for tokenization
 *
 * Return: An array of tokens
 */
char **tokenize_string(char *str_to_tokenize, char *delimiter)
{
	int num_tokens = 0;
	char **tokens = NULL;
	char *curr_token = NULL;
	char *save_parse = NULL;

	curr_token = _strtok_r(str_to_tokenize, delimiter, &save_parse);

	while (curr_token != NULL)
	{
		tokens = _realloc(tokens, sizeof(*tokens) * num_tokens, sizeof(*tokens) *
				(num_tokens + 1));
		tokens[num_tokens] = curr_token;
		curr_token = _strtok_r(NULL, delimiter, &save_parse);
		num_tokens++;
	}

	tokens = _realloc(tokens, sizeof(*tokens) * num_tokens, sizeof(*tokens) *
			(num_tokens + 1));
	tokens[num_tokens] = NULL;

	return (tokens);
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
		write(output_stream, &string_to_print[index], 1);
}

/**
 * remove_newline - Removes the newline character from a string
 * @str_to_modify: The string to modify
 *
 * Return: void
 */
void remove_newline(char *str_to_modify)
{
	int index = 0;

	while (str_to_modify[index] != '\0')
	{
		if (str_to_modify[index] == '\n')
			break;
		index++;
	}

	str_to_modify[index] = '\0';
}
