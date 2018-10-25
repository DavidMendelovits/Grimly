#include "libft.h"

int         ft_atoi(const char *str)
{
    int         i;
    int         len;
    int         div;
    int         p;

    i = 0;
    len = ft_strlen((char *)str);
    div = 1;
    p = len - 1;
    while (p >= 0)
    {
        i += (str[p] -'0') * div;
        div *= 10;
        p -= 1;
    }
    return (i);
}
