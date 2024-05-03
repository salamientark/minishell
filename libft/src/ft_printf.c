/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:08:21 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:35:18 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_printf_format(const char *str, int *pos, va_list arg)
{
	t_option	opt;
	int			success;

	*pos += 1;
	opt = make_option(str + *pos);
	success = -1;
	if (opt.specifier == 'c')
		success = (print_char_opt(va_arg(arg, int), opt));
	if (opt.specifier == 's')
		success = print_str_opt(va_arg(arg, char *), opt);
	if (opt.specifier == 'd' || opt.specifier == 'i')
		success = print_int_opt(va_arg(arg, int), opt);
	if (opt.specifier == 'u')
		success = (print_uint_opt(va_arg(arg, unsigned int), opt));
	if (opt.specifier == 'x')
		success = (printf_xlow_opt(va_arg(arg, int), opt));
	if (opt.specifier == 'X')
		success = (print_xup_opt(va_arg(arg, int), opt));
	if (opt.specifier == 'p')
		success = (print_p_opt(va_arg(arg, void *), opt));
	if (opt.specifier == '%')
		success = (print_char('%'));
	*pos += (opt.len + 1);
	return (success);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		printed_char;
	int		success;
	int		pos;

	if (!s)
		return (-1);
	va_start(ap, s);
	printed_char = 0;
	pos = 0;
	while (s[pos])
	{
		if (s[pos] == '%')
			success = ft_printf_format(s, &pos, ap);
		else
		{
			success = print_char(s[pos]);
			pos++;
		}
		if (success == -1)
			return (success);
		printed_char += success;
	}
	va_end(ap);
	return (printed_char);
}
