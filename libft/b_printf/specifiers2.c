#include "b_printf.h"

void            put_integer(va_list arg_list, int *chars)
{
    int             _int;

    _int = va_arg(arg_list, int);
    if (_int < 0)
	{
		ft_putchar('-');
		_int *= -1;
		*chars += 1;
	}
	putnbr_base(_int, 10, chars);
}


void            put_uint(va_list arg_list, int *chars)
{
    unsigned int    _uint;

    _uint = va_arg(arg_list, unsigned int);
    putnbr_base(_uint, 10, chars);
}

void            put_oct(va_list arg_list, int *chars)
{
    int             _oct;

    _oct = va_arg(arg_list, int);
    putnbr_base(_oct, 8, chars);
}

void            put_hex(va_list arg_list, int *chars)
{
    unsigned int    _hex;

    _hex = va_arg(arg_list, unsigned int);
    putnbr_base(_hex, 16, chars);
}

void            put_ptr(va_list arg_list, int *chars)
{
    unsigned long   _ptr;

    _ptr = va_arg(arg_list, unsigned long);
    write(1, "0x", 2);
    *chars += 2;
    putnbr_base(_ptr, 16, chars);
}
