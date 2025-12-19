/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_csp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badiakha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:40:43 by badiakha          #+#    #+#             */
/*   Updated: 2025/12/19 21:40:44 by badiakha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>

int	conv_char(t_fmt *f, int c)
{
	int		padding;
	int		count;
	char	pad;

	padding = 0;
	if (f->width > 1)
		padding = f->width - 1;
	pad = ' ';
	if (f->flag_zero && !f->flag_minus)
		pad = '0';
	count = 0;
	if (!f->flag_minus && padding)
	{
		if (put_padding(padding, pad) < 0)
			return (-1);
		count += padding;
	}
	if (write(1, &c, 1) < 0)
		return (-1);
	count++;
	if (f->flag_minus && padding)
	{
		if (put_padding(padding, ' ') < 0)
			return (-1);
		count += padding;
	}
	return (count);
}

int	conv_string(t_fmt *f, char *s)
{
	int	len;
	int	out;
	int	padding;
	int	count;

	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	out = len;
	if (f->precision_specified && f->precision < out)
		out = f->precision;
	padding = 0;
	if (f->width > out)
		padding = f->width - out;
	count = 0;
	if (!f->flag_minus && padding)
	{
		if (put_padding(padding, ' ') < 0)
			return (-1);
		count += padding;
	}
	if (put_str(s, out) < 0)
		return (-1);
	count += out;
	if (f->flag_minus && padding)
	{
		if (put_padding(padding, ' ') < 0)
			return (-1);
		count += padding;
	}
	return (count);
}

int	conv_pointer(t_fmt *f, void *p)
{
	char	*num;
	int		len;
	int		padding;
	int		count;

	if (!p)
		return (conv_string(f, "(nil)"));
	num = ft_utoa_base((unsigned long)p, 16, 0);
	if (!num)
		return (-1);
	len = ft_strlen(num) + 2;
	padding = 0;
	if (f->width > len)
		padding = f->width - len;
	count = 0;
	if (!f->flag_minus && padding)
	{
		if (put_padding(padding, ' ') < 0)
			return (free(num), -1);
		count += padding;
	}
	if (put_str("0x", 2) < 0
		|| put_str(num, ft_strlen(num)) < 0)
		return (free(num), -1);
	count += len;
	if (f->flag_minus && padding)
	{
		if (put_padding(padding, ' ') < 0)
			return (free(num), -1);
		count += padding;
	}
	free(num);
	return (count);
}

int	conv_percent(t_fmt *f)
{
	int		padding;
	int		count;
	char	c;

	c = '%';
	padding = 0;
	if (f->width > 1)
		padding = f->width - 1;
	count = 0;
	if (!f->flag_minus && padding)
	{
		if (put_padding(padding, f->flag_zero ? '0' : ' ') < 0)
			return (-1);
		count += padding;
	}
	if (write(1, &c, 1) < 0)
		return (-1);
	count++;
	if (f->flag_minus && padding)
	{
		if (put_padding(padding, ' ') < 0)
			return (-1);
		count += padding;
	}
	return (count);
}
