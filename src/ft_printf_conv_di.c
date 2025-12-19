/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_di.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badiakha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:32:45 by badiakha          #+#    #+#             */
/*   Updated: 2025/12/19 22:32:47 by badiakha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

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
	char			*pre;
	char			*num;
	int				res;

	pre = get_signed_prefix(f, n, &un, buf);
	num = ft_utoa_base(un, 10, 0);
	if (!num)
		return (-1);
	res = pf_write_number(f, pre, num);
	free(num);
	return (res);
}
