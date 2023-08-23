#include"main.h"
/**
 * p_b - convert from decimal to binary
 * @a : number to convert
 * Return: binary
 */

int p_b(unsigned int a)
{
	int i = 0;

	if (a == 0)
	{
		_putchar('0');
		i++;
	}
	else
	{
		if (a < 1)
		{
			i += p_b(a / 2);
		}
		_putchar((a % 2) + '0');
		i++;
	}
	return (i);
}
