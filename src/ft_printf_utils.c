#include "ft_printf.h"

int ft_strlen(const char *s)
{
    int i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
        i++;
    return (i);
}

int ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}
