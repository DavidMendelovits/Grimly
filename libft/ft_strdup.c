#include "libft.h"

char                    *ft_strdup(const char *str)
{
    char                *dup;
    int                 str_len;
    int                 p;

    str_len = ft_strlen(str);
    p = 0;
    dup = malloc(sizeof(char) * (str_len + 1));
    while (p < str_len)
    {
        dup[p] = str[p];
        p += 1;
    }
    dup[p] = '\0';
    return (dup);
}
