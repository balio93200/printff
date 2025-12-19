/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_ppercent.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badiakha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:32:15 by badiakha          #+#    #+#             */
/*   Updated: 2025/12/19 22:32:18 by badiakha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	ret_free(char *s)
{
	free(s);
	return (-1);
}

int	conv_pointer(t_fmt *f, void *p)
{
	char	*num;
	int		body;
	int		pad;

	if (!p)
		return (conv_string(f, "(nil)"));
	num = ft_utoa_base((unsigned long)p, 16, 0);
	if (!num)
		return (-1);
	body = ft_strlen(num) + 2;
	pad = 0;
	if (f->width > body)
		pad = f->width - body;
	if (!f->flag_minus && pad && put_padding(pad, ' ') < 0)
		return (ret_free(num));
	if (put_str("0x", 2) < 0 || put_str(num, ft_strlen(num)) < 0)
		return (ret_free(num));
	if (f->flag_minus && pad && put_padding(pad, ' ') < 0)
		return (ret_free(num));
	free(num);
	return (body + pad);
}

int	conv_percent(t_fmt *f)
{
	return (conv_char(f, '%'));
}
