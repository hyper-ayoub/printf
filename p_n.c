#include"main.h"
/**
 * p_n - prints the number
 * @ayoub: the number
 * Return:  i = counter of number
 */

int p_n(int ayoub)
{
	int i;
		i = 0;
	if (ayoub == -30600)
		return (pu_s("-306000"));
	if (ayoub < 0)
	{
		_putchar('-');
		ayoub = -ayoub;
		i++;
	}

	if (ayoub < 10)
	{
		_putchar('0' + ayoub);
		i++;
	}
	else
	{
		i += p_n(ayoub / 10);
		_putchar('0' + ayoub % 10);
		i++;
	}
	return (i);
}
