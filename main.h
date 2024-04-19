#ifndef MAIN
#define MAIN

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

/**
 * struct struct_buffer - A new type defining a buffer struct.
 *
 * @buffer: A pointer to a character array.
 * @start: A pointer to the start of buffer.
 * @len: The length of the string stored in buffer.
 *
 */
typedef struct struct_buffer
{
	char *buffer;
	char *start;
	unsigned int len;
} buffer;

/**
 * struct print_all - A new type defining a converter struct.
 *
 * @specifier: A character representing a conversion specifier.
 * @func: A pointer to a conversion function corresponding to specifier.
 *
 */
typedef struct print_all
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buffer *, unsigned char, int,
	int, unsigned char);
} printfuncs;

/**
 * struct flag_s - A new type defining a flags struct.
 * @flag: A character representing a flag.
 * @value: The integer value of the flag.
 */
typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_t;

int _printf(const char *format, ...);
unsigned int convert_c(va_list args, buffer *output, unsigned char flags,
					int wid, int prec, unsigned char len);
unsigned int convert_s(va_list args, buffer *output, unsigned char flags,
					int wid, int prec, unsigned char len);
unsigned int convert_di(va_list args, buffer *output, unsigned char flags,
					int wid, int prec, unsigned char len);
unsigned int convert_percent(va_list args, buffer *output,
					unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_b(va_list args, buffer *output, unsigned char flags,
					int wid, int prec, unsigned char len);
unsigned int convert_u(va_list args, buffer *output, unsigned char flags,
					int wid, int prec, unsigned char len);
unsigned int convert_o(va_list args, buffer *output, unsigned char flags,
					int wid, int prec, unsigned char len);
unsigned int convert_x(va_list args, buffer *output, unsigned char flags,
					int wid, int prec, unsigned char len);
unsigned int convert_X(va_list args, buffer *output, unsigned char flags,
					int wid, int prec, unsigned char len);
unsigned int convert_S(va_list args, buffer *output, unsigned char flags,
					int wid, int prec, unsigned char len);
unsigned int convert_p(va_list args, buffer *output, unsigned char flags,
						int wid, int prec, unsigned char len);
unsigned int convert_r(va_list args, buffer *output, unsigned char flags,
						int wid, int prec, unsigned char len);
unsigned int convert_R(va_list args, buffer *output, unsigned char flags,
					int wid, int prec, unsigned char len);
unsigned char handle_flags(const char *flags, char *index);
unsigned char handle_length(const char *modifier, char *index);
int handle_width(va_list args, const char *modifier, char *index);
int handle_precision(va_list args, const char *modifier, char *index);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer *,
			unsigned char, int, int, unsigned char);
buffer *init_buffer(void);
void free_buffer(buffer *output);
unsigned int _memcpy(buffer *output, const char *src, unsigned int n);
unsigned int convert_sbase(buffer *output, long int num, char *base,
						unsigned char flags, int wid, int prec);
unsigned int convert_ubase(buffer *output, unsigned long int num, char *base,
							unsigned char flags, int wid, int prec);

unsigned int print_width(buffer *output, unsigned int printed,
						unsigned char flags, int wid);
unsigned int print_string_width(buffer *output, unsigned char flags,
								int wid, int prec, int size);
unsigned int print_neg_width(buffer *output, unsigned int printed,
							unsigned char flags, int wid);
#endif
