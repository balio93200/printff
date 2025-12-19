/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_diuxx.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badiakha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:40:19 by badiakha          #+#    #+#             */
/*   Updated: 2025/12/19 21:40:21 by badiakha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	write_number(t_fmt *f, char *prefix, char *num)
{
	int	num_len;
	int	pre_len;
	int	zeros;
	int	field;
	int	padding;
	int	count;

	num_len = ft_strlen(num);
	if (f->precision_specified && f->precision == 0 && num[0] == '0')
		num_len = 0;
	zeros = 0;
	if (f->precision_specified && f->precision > num_len)
		zeros = f->precision - num_len;
	pre_len = ft_strlen(prefix);
	field = pre_len + zeros + num_len;
	padding = 0;
	if (f->width > field)
		padding = f->width - field;
	count = 0;
	if (!f->flag_minus && padding && !(f->flag_zero && !f->precision_specified))
	{
		if (put_padding(padding, ' ') < 0)
			return (-1);
		count += padding;
	}
	if (pre_len && put_str(prefix, pre_len) < 0)
		return (-1);
	if (!f->flag_minus && padding && (f->flag_zero && !f->precision_specified))
	{
		if (put_padding(padding, '0') < 0)
			return (-1);
		count += padding;
	}
	if (zeros && put_padding(zeros, '0') < 0)
		return (-1);
	if (num_len && put_str(num, num_len) < 0)
		return (-1);
	count += pre_len + zeros + num_len;
	if (f->flag_minus && padding)
	{
		if (put_padding(padding, ' ') < 0)
			return (-1);
		count += padding;
	}
	return (count);
}


static char	*get_signed_prefix(t_fmt *f, long n, unsigned long *un, char *buf)
{
	if (n < 0)
	{
		*un = (unsigned long)(-n);
		buf[0] = '-';
		buf[1] = '\0';
		return (buf);
	}
	*un = (unsigned long)n;
	if (f->flag_plus)
		return ("+");
	if (f->flag_space)
		return (" ");
	return ("");
}

int	conv_signed(t_fmt *f, long n)
{
	unsigned long	un;
	char			buf[2];
	char			*prefix;
	char			*num;
	int				res;

	prefix = get_signed_prefix(f, n, &un, buf);
	num = ft_utoa_base(un, 10, 0);
	if (!num)
		return (-1);
	res = write_number(f, prefix, num);
	free(num);
	return (res);
}

int	conv_unsigned(t_fmt *f, unsigned int n)
{
	char	*num;
	int		res;

	num = ft_utoa_base((unsigned long)n, 10, 0);
	if (!num)
		return (-1);
	res = write_number(f, "", num);
	free(num);
	return (res);
}

int	conv_hex(t_fmt *f, unsigned int n, int upper)
{
	char	*num;
	char	*prefix;
	int		res;

	num = ft_utoa_base((unsigned long)n, 16, upper);
	if (!num)
		return (-1);
	prefix = "";
	if (f->flag_hash && n != 0)
	{
		if (upper)
			prefix = "0X";
		else
			prefix = "0x";
	}
	res = write_number(f, prefix, num);
	free(num);
	return (res);
}
