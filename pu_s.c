#include"main.h"
/**
 * pu_s - its function that print a string
 * @b: string
 * Return: c
 */
int pu_s(const char *b)
{
	int c = 0;

	if (b == NULL)
	{
		pu_s("(null)");
		return (6);
	}
	while (*(b + c) != '\0')
	{
		_putchar(*(b + c));
		c++;
	}
	return (c);
}
