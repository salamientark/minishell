/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:46:49 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:35:18 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	print_str(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
	return (len);
}

static t_bool	check_option_str(t_option opt)
{
	if (opt.flags.sign != 0)
		return (FALSE);
	if (opt.flags.hashtag != 0)
		return (FALSE);
	return (TRUE);
}

static void	init_width_precision(int *width, int *prec, const char *s,
	t_option opt)
{
	*prec = 0;
	while (s[*prec])
		*prec += 1;
	if (opt.flags.set_precision == 1 && opt.precision < (unsigned int)*prec)
		*prec = opt.precision;
	*width = opt.width - *prec;
	if (*width < 0)
		*width = 0;
}

int	print_str_opt(const char *str, t_option opt)
{
	int	padding;
	int	str_len;

	if (check_option_str(opt) == FALSE)
		return (-1);
	if (opt.flags.zero != 0 && opt.flags.rpadding != 1)
		opt.flags.zero = 0;
	if (!str)
	{
		if (opt.flags.set_precision == 0 || opt.precision >= 6)
			str = "(null)";
		else
			str = "";
	}
	init_width_precision(&padding, &str_len, str, opt);
	if (opt.flags.rpadding == 0 && padding > 0)
		putnchar(' ', padding);
	write(1, str, str_len);
	if (opt.flags.rpadding == 1 && padding > 0)
		putnchar(' ', padding);
	return (padding + str_len);
}
