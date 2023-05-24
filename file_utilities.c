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
			return (NULL);
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

/**
 * *_realloc - reallocates a memory block using malloc and free
 * void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
 * Description: this function attempts to resize the memory block pointed to by
 * ptr that was previously allocated with a call to malloc or calloc.
 * The contents will be copied to the newly allocated space, in the range
 * from the start of ptr up to the minimum of the old and new sizes
 * If new_size > old_size, the “added” memory should not be initialized
 * If new_size == old_size do not do anything and return ptr
 * If ptr is NULL, then the call is equivalent to malloc(new_size)
 * for all values of old_size and new_size
 * If new_size is equal to zero, and ptr is not NULL, then the call is
 * equivalent to free(ptr). Return NULL
 * Don’t forget to free ptr when it makes sense
 *
 * @ptr: pointer to the memory previously allocated with a call to malloc:
 * malloc(old_size)
 * @old_size: size, in bytes, of the allocated space for ptr
 * @new_size: new size, in bytes of the new memory block
 * Return: pointer to the newly allocated memory, or NULL if the request fails
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pointer, *memory;
	unsigned int count;

	if (ptr != NULL)
		pointer = ptr;
	else
		return (malloc(new_size));
	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (0);
	}

	memory = malloc(new_size);
	if (memory == NULL)
		return (0);
	for (count = 0; count < old_size || count < new_size; count++)
	{
		*(memory + count) = pointer[count];
	}
	free(ptr);
	return (memory);
}

/**
 * _atoi - convert a string to an integer
 * Description: a function
 * @s: character to be checked
 * Return: integer
 */

int _atoi(char *s)
{
	unsigned int num = 0;
	int sign = 1;

	do {
		if (*s == '-')
			sign *= -1;
		else if (*s >= '0' && *s <= '9')
			num = (num * 10) + (*s - '0');
		else if (num > 0)
			break;
	} while (*s++);

	return (num * sign);
}

/**
 * ctrl_c_handler - Handles the SIGINT signal (Ctrl+C)
 * @signum: The signal number
 *
 * Description: This function is invoked when the SIGINT signal (Ctrl+C) is
 * received. It prints a prompt to the standard input file descriptor
 * (STDIN_FILENO)
 * Return: void
 */
void ctrl_c_handler(int signum)
{
	if (signum == SIGINT)
		write(STDIN_FILENO, "\n($) ", 6);
}
