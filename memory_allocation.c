#include "shell.h"

/**
 * *_memset - fills memory with a constant byte
 * Description: a function that  fills the first n bytes of the memory area
 * pointed to by s with the constant byte b
 * @s: pointer
 * @b: constant byte
 * @n: number of bytes of memory area
 * Return: pointer to the memory area s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int byte;

	for (byte = 0; byte < n; byte++)
		s[byte] = b;
	return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
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
	for (count = 0; count < (old_size || count < new_size); count++)
	{
		*(memory + count) = pointer[count];
	}
	free(ptr);
	return (memory);
}
