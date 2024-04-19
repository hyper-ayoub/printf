#include "main.h"

/**
 * _memcpy - Copies n bytes from memory area src to
 *           the buffer contained in a buffer struct.
 * @output: A buffer struct.
 * @src: A pointer to the memory area to copy.
 * @n: The number of bytes to be copied.
 *
 * Return: The number of bytes copied.
 */
unsigned int _memcpy(buffer *output, const char *src, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
	{
		*(output->buffer) = *(src + index);
		(output->len)++;

		if (output->len == 1024)
		{
			write(1, output->start, output->len);
			output->buffer = output->start;
			output->len = 0;
		}

		else
			(output->buffer)++;
	}

	return (n);
}

/**
 * free_buffer - Frees a buffer struct.
 * @output: The buffer struct to be freed.
 */
void free_buffer(buffer *output)
{
	free(output->start);
	free(output);
}

/**
 * init_buffer - Initializes a variable of struct type buffer.
 *
 * Return: A pointer to the initialized buffer.
 */
buffer *init_buffer(void)
{
	buffer *output;

	output = malloc(sizeof(buffer));
	if (output == NULL)
		return (NULL);

	output->buffer = malloc(sizeof(char) * 1024);
	if (output->buffer == NULL)
	{
		free(output);
		return (NULL);
	}

	output->start = output->buffer;
	output->len = 0;

	return (output);
}

