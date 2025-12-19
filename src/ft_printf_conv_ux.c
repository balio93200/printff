/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_ux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badiakha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:38:54 by badiakha          #+#    #+#             */
/*   Updated: 2025/12/19 22:38:56 by badiakha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int	conv_unsigned(t_fmt *f, unsigned int n)
{
	char	*num;
	int		res;

	num = ft_utoa_base((unsigned long)n, 10, 0);
	if (!num)
		return (-1);
	res = pf_write_number(f, "", num);
	free(num);
	return (res);
}

int	conv_hex(t_fmt *f, unsigned int n, int upper)
{
	char	*num;
	char	*pre;
	int		res;

	num = ft_utoa_base((unsigned long)n, 16, upper);
	if (!num)
		return (-1);
	pre = "";
	if (f->flag_hash && n != 0)
	{
		if (upper)
			pre = "0X";
		else
			pre = "0x";
	}
	res = pf_write_number(f, pre, num);
	free(num);
	return (res);
}
