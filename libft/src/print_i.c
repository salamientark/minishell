/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_i.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:46:47 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:35:18 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_bool	check_option_d(t_option opt)
{
	if (opt.flags.hashtag != 0)
		return (FALSE);
	if (opt.flags.rpadding != 0 && opt.flags.zero != 0)
		return (FALSE);
	if (opt.flags.space != 0 && opt.flags.sign != 0)
		return (FALSE);
	return (TRUE);
}

static int	print_sign(long n, const t_option opt)
{
	if (n < 0)
	{
		write(1, "-", 1);
		return (1);
	}
	if (opt.flags.sign == 1)
	{
		write(1, "+", 1);
		return (1);
	}
	if (opt.flags.space == 1)
	{
		write(1, " ", 1);
		return (1);
	}
	return (0);
}

static void	init_width_precision(int *width, int *precision, long n,
	t_option opt)
{
	int	n_len;
	int	sign;

	n_len = nbr_base_len((long long) n, 10);
	sign = 0;
	if (n < 0 || opt.flags.space == 1 || opt.flags.sign == 1)
		sign = 1;
	*precision = opt.precision - n_len;
	if (*precision < 0)
		*precision = 0;
	*width = opt.width - (n_len + *precision + sign);
	if (*width < 0)
		*width = 0;
}

int	print_int_opt(int n, t_option opt)
{
	int		padding;
	int		precision;
	int		printed_char;
	long	nbr;

	if (check_option_d(opt) == FALSE)
		return (-1);
	if (opt.flags.zero == 1 && opt.precision > 0)
		opt.flags.zero = 0;
	nbr = (long) n;
	init_width_precision(&padding, &precision, n, opt);
	printed_char = padding + precision;
	if (opt.flags.rpadding == 0 && opt.flags.zero == 0)
		putnchar(' ', padding);
	printed_char += print_sign(nbr, opt);
	if (opt.flags.rpadding == 0 && opt.flags.zero == 1)
		putnchar('0', padding);
	if (nbr < 0)
		nbr = -nbr;
	putnchar('0', precision);
	printed_char += ft_print_uint(nbr);
	if (opt.flags.rpadding == 1)
		putnchar(' ', padding);
	return (printed_char);
}
