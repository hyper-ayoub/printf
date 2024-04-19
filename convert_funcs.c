#include "main.h"

/**
 * convert_c - Converts an argument to an unsigned char and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_c(va_list args, buffer *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char c;
	unsigned int ret = 0;

	(void)prec;
	(void)len;

	c = va_arg(args, int);

	ret += print_width(output, ret, flags, wid);
	ret += _memcpy(output, &c, 1);
	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

/**
 * convert_percent - Stores a percent sign to a
 *                   buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer (always 1).
 */
unsigned int convert_percent(va_list args, buffer *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char percent = '%';
	unsigned int ret = 0;

	(void)args;
	(void)prec;
	(void)len;

	ret += print_width(output, ret, flags, wid);
	ret += _memcpy(output, &percent, 1);
	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

/**
 * convert_p - Converts the address of an argument to hex and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_p(va_list args, buffer *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *null = "(nil)";
	unsigned long int address;
	unsigned int ret = 0;

	(void)len;

	address = va_arg(args, unsigned long int);
	if (address == '\0')
		return (_memcpy(output, null, 5));

	flags |= 32;
	ret += convert_ubase(output, address, "0123456789abcdef",
			flags, wid, prec);
	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

/**
 * convert_sbase - Converts a signed long to an inputted base and stores
 *                 the result to a buffer contained in a struct.
 * @output: A buffer struct containing a character array.
 * @num: A signed long to be converted.
 * @base: A pointer to a string containing the base to convert to.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_sbase(buffer *output, long int num, char *base,
		unsigned char flags, int wid, int prec)
{
	int size;
	char digit, pad = '0';
	unsigned int ret = 1;

	for (size = 0; *(base + size);)
		size++;

	if (num >= size || num <= -size)
		ret += convert_sbase(output, num / size, base,
				flags, wid - 1, prec - 1);

	else
	{
		for (; prec > 1; prec--, wid--) /* Handle precision */
			ret += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
				ret += _memcpy(output, &pad, 1);
		}
	}

	digit = base[(num < 0 ? -1 : 1) * (num % size)];
	_memcpy(output, &digit, 1);

	return (ret);
}

/**
 * convert_ubase - Converts an unsigned long to an inputted base and
 *                 stores the result to a buffer contained in a struct.
 * @output: A buffer struct containing a character array.
 * @num: An unsigned long to be converted.
 * @base: A pointer to a string containing the base to convert to.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_ubase(buffer *output, unsigned long int num, char *base,
		unsigned char flags, int wid, int prec)
{
	unsigned int size, ret = 1;
	char digit, pad = '0', *lead = "0x";

	for (size = 0; *(base + size);)
		size++;

	if (num >= size)
		ret += convert_ubase(output, num / size, base,
				flags, wid - 1, prec - 1);

	else
	{
		if (((flags >> 5) & 1) == 1) /* Printing a ptr address */
		{
			wid -= 2;
			prec -= 2;
		}
		for (; prec > 1; prec--, wid--) /* Handle precision */
			ret += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
				ret += _memcpy(output, &pad, 1);
		}
		if (((flags >> 5) & 1) == 1) /* Print 0x for ptr address */
			ret += _memcpy(output, lead, 2);
	}

	digit = base[(num % size)];
	_memcpy(output, &digit, 1);

	return (ret);
}
