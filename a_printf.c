#include "main.h"
/**
 * _printf - produces output according to a format
 * @format:
 * @...:
 * Return: i
 */
int _printf(const char *format, ...)
{
	int i;
	va_list arg;

	i = 0;

	va_start(arg, format);

	if (!format || (format[0] == '%' && !format[1]))
	{
		return (-1);
	}
	if (format[0] == '%' && format[1] == ' ' && !format[2])
	{
		return (-1);
	}
	while (*format)
	{
	if (*format == '%')
	{
		format++;
		handle_for(arg, *format, &i);
	}
		else
		{
_putchar(*format);
i++;
		}
		format++;
	}
	va_end(arg);
	return (i);
}
