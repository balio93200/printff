/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badiakha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:32:30 by badiakha          #+#    #+#             */
/*   Updated: 2025/12/19 22:32:31 by badiakha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len(t_fmt *f, char *num)
{
	int	len;

	len = ft_strlen(num);
	if (f->precision_specified && f->precision == 0 && num[0] == '0')
		return (0);
	return (len);
}

static int	zeros_len(t_fmt *f, int len)
{
	if (f->precision_specified && f->precision > len)
		return (f->precision - len);
	return (0);
}

static int	write_middle(t_fmt *f, char *prefix, char *num, int pad)
{
	int	len;
	int	zeros;
	int	pre;
	int	zpad;

	len = num_len(f, num);
	zeros = zeros_len(f, len);
	pre = ft_strlen(prefix);
	zpad = (f->flag_zero && !f->flag_minus && !f->precision_specified);
	if (!f->flag_minus && pad && !zpad)
		if (put_padding(pad, ' ') < 0)
			return (-1);
	if (pre && put_str(prefix, pre) < 0)
		return (-1);
	if (!f->flag_minus && pad && zpad)
		if (put_padding(pad, '0') < 0)
			return (-1);
	if (zeros && put_padding(zeros, '0') < 0)
		return (-1);
	if (len && put_str(num, len) < 0)
		return (-1);
	return (pre + pad + zeros + len);
}

int	pf_write_number(t_fmt *f, char *prefix, char *num)
{
	int	len;
	int	zeros;
	int	pre;
	int	pad;
	int	count;

	len = num_len(f, num);
	zeros = zeros_len(f, len);
	pre = ft_strlen(prefix);
	pad = 0;
	if (f->width > pre + zeros + len)
		pad = f->width - (pre + zeros + len);
	count = write_middle(f, prefix, num, pad);
	if (count < 0)
		return (-1);
	if (f->flag_minus && pad)
		if (put_padding(pad, ' ') < 0)
			return (-1);
	return (count);
}
