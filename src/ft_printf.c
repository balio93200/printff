/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badiakha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:40:10 by badiakha          #+#    #+#             */
/*   Updated: 2025/12/19 21:40:11 by badiakha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int	handle_conv(t_fmt *f, va_list ap)
{
	if (f->spec == 'c')
		return (conv_char(f, va_arg(ap, int)));
	if (f->spec == 's')
		return (conv_string(f, va_arg(ap, char *)));
	if (f->spec == 'p')
		return (conv_pointer(f, va_arg(ap, void *)));
	if (f->spec == 'd' || f->spec == 'i')
		return (conv_signed(f, (long)va_arg(ap, int)));
	if (f->spec == 'u')
		return (conv_unsigned(f, va_arg(ap, unsigned int)));
	if (f->spec == 'x')
		return (conv_hex(f, va_arg(ap, unsigned int), 0));
	if (f->spec == 'X')
		return (conv_hex(f, va_arg(ap, unsigned int), 1));
	if (f->spec == '%')
		return (conv_percent(f));
	return (0);
}

static int	handle_format(const char **fmt, va_list ap, int *count)
{
	t_fmt	f;
	int		n;

	if (**fmt == '%')
	{
		(*fmt)++;
		if (parse_format(fmt, &f) == -1)
			return (-1);
		n = handle_conv(&f, ap);
		if (n < 0)
			return (-1);
		*count += n;
	}
	else
	{
		if (write(1, *fmt, 1) < 0)
			return (-1);
		(*fmt)++;
		(*count)++;
	}
	return (0);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		count;

	if (!fmt)
		return (-1);
	va_start(ap, fmt);
	count = 0;
	while (*fmt)
	{
		if (handle_format(&fmt, ap, &count) == -1)
			return (va_end(ap), -1);
	}
	va_end(ap);
	return (count);
}
