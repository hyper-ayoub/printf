#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"

#define BUFF_SIZE 1024

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
    int i, printed = 0, printed_chars = 0;
    int flags, width, precision, size, buff_ind = 0;
    va_list list;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(list, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);
            printed_chars++;
        }
        else
        {
            print_buffer(buffer, &buff_ind);
            flags = get_flags(format, &i);
            width = get_width(format, &i, list);
            precision = get_precision(format, &i, list);
            size = get_size(format, &i);
            ++i;
            if (format[i] == 's')
            {
                char *str = va_arg(list, char *);
                if (precision >= 0)
                {
                    int len;
                    for (len = 0; len < precision && str[len] != '\0'; len++)
                    {
                        buffer[buff_ind++] = str[len];
                        if (buff_ind == BUFF_SIZE)
                            print_buffer(buffer, &buff_ind);
                    }
                    printed_chars += len;
                }
                else
                {
                    int len;
                    for (len = 0; str[len] != '\0'; len++)
                    {
                        buffer[buff_ind++] = str[len];
                        if (buff_ind == BUFF_SIZE)
                            print_buffer(buffer, &buff_ind);
                    }
                    printed_chars += len;
                }
            }
            else
            {
                printed = handle_print(format, &i, list, buffer,
                                       flags, width, precision, size);
                if (printed == -1)
                    return (-1);
                printed_chars += printed;
            }
        }
    }

    print_buffer(buffer, &buff_ind);

    va_end(list);

    return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
        write(1, &buffer[0], *buff_ind);

    *buff_ind = 0;
}
