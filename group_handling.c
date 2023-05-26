#include "shell.h"

/**
 * findArrayElement - Find matching element in an array
 * @array: Array of strings
 * @elementName: Name of the element to search for
 *
 * This function searches for a matching element in the provided array.
 * It compares each element with the specified element name using a prefix
 * match. If a match is found, it returns a pointer to the matching element
 * in the array. If no match is found, it returns NULL.
 * Return: Pointer to the matching element if found, NULL otherwise.
 */
char *findArrayElement(char **array, char *elementName)
{
	while (*array != NULL)
	{
		if (str_compare(*array, elementName, PREFIX) == TRUE)
			return (*array);

		array++;
	}

	return (NULL);
}

/**
 * splitString - Split a string into an array of substrings
 * @stringToSplit: The string to be split
 * @delimiter: The delimiter character used to split the string
 * @nextSubstring: Pointer to the next substring after the delimiter and
 * semicolon
 * This function takes a string and splits it into an array of substrings
 * based on the provided delimiter. The function counts the number of elements
 * needed in the array, allocates memory for the array, and populates it with
 * the substrings. It also updates the @nextSubstring parameter to point to
 * the next substring after the delimiter and semicolon (if present).
 * The array of substrings is terminated with a NULL value.
 *
 * Return: The array of substrings if successful, NULL otherwise.
 */
char **splitString(char *stringToSplit, char delimiter, char **nextSubstring)
{
	char *stringPtr = stringToSplit;
	unsigned int numSubstrings = 2;
	char **substringArray = NULL;
	unsigned int x;

	while (*stringPtr != '\0')
	{
		if (*stringPtr == ';')
			break;
		if (*stringPtr == delimiter && *(stringPtr + 1) != '\0')
			numSubstrings++;
		stringPtr++;
	}

	substringArray = malloc(numSubstrings * sizeof(char *));
	if (substringArray == NULL)
		exit(EXIT_FAILURE);

	substringArray[0] = stringToSplit;
	stringPtr = stringToSplit;
	x = 1;

	while (*stringPtr != '\0')
	{
		if (*stringPtr == delimiter)
		{
			*stringPtr = '\0';
			stringPtr++;
			if (*stringPtr == ';')
			{
				substringArray[x] = NULL;
				if (*(stringPtr + 1) != '\0'
						&& *(stringPtr + 2) != '\0')
					*nextSubstring = stringPtr + 2;
				break;
			}
			if (*stringPtr != '\0')
			{
				substringArray[x] = stringPtr;
				x++;
			}
		}
		stringPtr++;
	}
	substringArray[x] = NULL;
	return (substringArray);
}

/**
 * countListEntries - Count the number of entries in a list
 * @list: The list of entries
 * @entry: The entry to search for (NULL to count all entries)
 *
 * This function counts the number of entries in the provided list.
 * If the @entry parameter is NULL, it counts all the entries in the list.
 * If the @entry parameter is not NULL, it counts the number of entries that
 * match the given entry.
 * Return: The number of entries in the list if successful, -1 otherwise.
 */
int countListEntries(char **list, char *entry)
{
	int count = 0;

	if (entry == NULL)
	{
		while (*list != NULL)
		{
			count++;
			list++;
		}
		count++;
		return (count);
	}
	else
	{
		while (*list != NULL)
		{
			if (str_compare(*list, entry, PREFIX) == TRUE)
				return (count);

			count++;
			list++;
		}
	}

	return (-1);
}

/**
 * copyStringArray - Create a copy of a string array with a new size
 * @oldArray: The original string array to be copied
 * @newSize: The new size of the copied array
 *
 * This function creates a new copy of a string array with a specified size.
 * It allocates memory for the new array, duplicates each string element from
 * the original array, and terminates the copied array with a NULL value.
 * Return: The copied string array if successful, NULL otherwise.
 */
char **copyStringArray(char **oldArray, int newSize)
{
	char **newArray = NULL;
	char **ptrArray;

	newArray = malloc(sizeof(char **) * newSize);
	if (newArray == NULL)
		exit(EXIT_FAILURE);

	ptrArray = newArray;
	while (*oldArray != NULL)
	{
		*ptrArray = _strdup(*oldArray);
		ptrArray++;
		oldArray++;
	}
	*ptrArray = NULL;

	return (newArray);
}

/**
 * freeStringArray - Free the memory allocated for a string array
 * @array: The string array to be freed
 *
 * This function frees the memory allocated for a string array.
 * It iterates through each string element in the array and frees the memory
 * associated with it. Finally, it frees the memory allocated for the array
 * itself
 * Return: TRUE if successful, FALSE otherwise.
 */
int freeStringArray(char **array)
{
	char **pointer = array;

	while (*pointer != NULL)
	{
		free(*pointer);
		pointer++;
	}

	free(array);

	return (TRUE);
}
