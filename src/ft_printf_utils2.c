/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badiakha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:40:30 by badiakha          #+#    #+#             */
/*   Updated: 2025/12/19 21:40:31 by badiakha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>

static int	count_digits(unsigned long n, int base)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*ft_utoa_base(unsigned long n, int base, int upper)
{
	char			*res;
	const char		*digits;
	int				len;

	digits = "0123456789abcdef";
	if (upper)
		digits = "0123456789ABCDEF";
	len = count_digits(n, base);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (n == 0)
		res[0] = '0';
	while (n)
	{
		res[--len] = digits[n % base];
		n /= base;
	}
	return (res);
}

int	put_padding(int n, char c)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (write(1, &c, 1) < 0)
			return (-1);
		i++;
	}
	return (n);
}

int	put_str(char *s, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (write(1, &s[i], 1) < 0)
			return (-1);
		i++;
	}
	return (len);
}
