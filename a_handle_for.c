#include"main.h"
/**
 * handle_for - handles different specifiers
 * @i: the counter
 * @specifier: the specifier
 * @arg: argument
 */
int handle_for(va_list arg, char specifier, int *i)
{
	switch (specifier)
	{
		case 'b':
				(*i) += p_b(va_arg(arg, unsigned int));
				break;
		case 'c':
				(*i) += _putchar(va_arg(arg, int));
				break;
		case 'i':
		case 'd':
				(*i) += p_n(va_arg(arg, int));
				break;
		case 's':
				(*i) += pu_s(va_arg(arg, char *));
				break;
		case '%':
				(*i) += _putchar('%');
				break;

		default:
				_putchar('%');
				_putchar(specifier);
				(*i) += 2;
				break;
	}
	return 0;
}
