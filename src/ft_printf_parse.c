#include "ft_printf.h"

static void parse_flags(const char **s, t_fmt *f)
{
    while (**s == '-' || **s == '0' || **s == '#'
        || **s == ' ' || **s == '+')
    {
        if (**s == '-')
            f->flag_minus = 1;
        else if (**s == '0')
            f->flag_zero = 1;
        else if (**s == '#')
            f->flag_hash = 1;
        else if (**s == ' ')
            f->flag_space = 1;
        else if (**s == '+')
            f->flag_plus = 1;
        (*s)++;
    }
    if (f->flag_minus)
        f->flag_zero = 0;
}

static void parse_width(const char **s, t_fmt *f)
{
    while (ft_isdigit(**s))
    {
        f->width = f->width * 10 + (**s - '0');
        (*s)++;
    }
}

static void parse_precision(const char **s, t_fmt *f)
{
    if (**s != '.')
        return ;
    f->precision_specified = 1;
    f->precision = 0;
    (*s)++;
    while (ft_isdigit(**s))
    {
        f->precision = f->precision * 10 + (**s - '0');
        (*s)++;
    }
    f->flag_zero = 0;
}

int     parse_format(const char **s, t_fmt *f)
{
    f->flag_minus = 0;
    f->flag_zero = 0;
    f->flag_hash = 0;
    f->flag_space = 0;
    f->flag_plus = 0;
    f->width = 0;
    f->precision = 0;
    f->precision_specified = 0;
    f->spec = 0;
    parse_flags(s, f);
    parse_width(s, f);
    parse_precision(s, f);
    if (**s == 'c' || **s == 's' || **s == 'p' || **s == 'd'
        || **s == 'i' || **s == 'u' || **s == 'x'
        || **s == 'X' || **s == '%')
    {
        f->spec = **s;
        (*s)++;
        return (0);
    }
    return (-1);
}
