/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badiakha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:39:55 by badiakha          #+#    #+#             */
/*   Updated: 2025/12/19 21:39:58 by badiakha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

typedef struct s_fmt
{
	int		flag_minus;
	int		flag_zero;
	int		flag_hash;
	int		flag_space;
	int		flag_plus;
	int		width;
	int		precision;
	int		precision_specified;
	char	spec;
}			t_fmt;

int			ft_printf(const char *fmt, ...);

int			parse_format(const char **s, t_fmt *f);

int			conv_char(t_fmt *f, int c);
int			conv_string(t_fmt *f, char *s);
int			conv_pointer(t_fmt *f, void *p);
int			conv_signed(t_fmt *f, long n);
int			conv_unsigned(t_fmt *f, unsigned int n);
int			conv_hex(t_fmt *f, unsigned int n, int upper);
int			conv_percent(t_fmt *f);

int			pf_write_number(t_fmt *f, char *prefix, char *num);
int			ft_strlen(const char *s);
int			ft_isdigit(int c);
int			put_padding(int n, char c);
int			put_str(char *s, int len);
char		*ft_utoa_base(unsigned long n, int base, int upper);

#endif
