/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_cs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badiakha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:32:02 by badiakha          #+#    #+#             */
/*   Updated: 2025/12/19 22:32:05 by badiakha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	conv_char(t_fmt *f, int c)
{
	int		pad;
	char	fill;

	pad = 0;
	if (f->width > 1)
		pad = f->width - 1;
	fill = ' ';
	if (f->flag_zero && !f->flag_minus)
		fill = '0';
	if (!f->flag_minus && pad && put_padding(pad, fill) < 0)
		return (-1);
	if (write(1, &c, 1) < 0)
		return (-1);
	if (f->flag_minus && pad && put_padding(pad, ' ') < 0)
		return (-1);
	return (pad + 1);
}

int	conv_string(t_fmt *f, char *s)
{
	int	len;
	int	out;
	int	pad;

	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	out = len;
	if (f->precision_specified && f->precision < out)
		out = f->precision;
	pad = 0;
	if (f->width > out)
		pad = f->width - out;
	if (!f->flag_minus && pad && put_padding(pad, ' ') < 0)
		return (-1);
	if (put_str(s, out) < 0)
		return (-1);
	if (f->flag_minus && pad && put_padding(pad, ' ') < 0)
		return (-1);
	return (out + pad);
}
