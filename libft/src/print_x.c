/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:46:42 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:35:18 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_bool	check_option_hexlow(t_option opt)
{
	if (opt.flags.sign != 0)
		return (FALSE);
	if (opt.flags.space != 0)
		return (FALSE);
	if (opt.flags.rpadding != 0 && opt.flags.zero != 0)
		return (FALSE);
	return (TRUE);
}

static void	init_width_precision(int *width, int *precision, long n,
	t_option opt)
{
	int	n_len;

	n_len = nbr_base_len((long long) n, 16);
	*precision = opt.precision - n_len;
	if (*precision < 0)
		*precision = 0;
	*width = opt.width - (n_len + *precision);
	if (n != 0)
		*width = *width - (2 * opt.flags.hashtag);
	if (*width < 0)
		*width = 0;
}

static int	print_hexlow_rec(unsigned int n)
{
	if (n)
	{
		if (n % 16 > 9)
			return (print_hexlow_rec(n / 16) + print_char(n % 16 + 'a' - 10));
		else
			return (print_hexlow_rec(n / 16) + print_char(n % 16 + '0'));
	}
	return (0);
}

static int	print_hexlow(unsigned int n)
{
	if (n == 0)
		return (print_char('0'));
	return (print_hexlow_rec(n));
}

int	printf_xlow_opt(unsigned int n, t_option opt)
{
	int		padding;
	int		precision;
	int		printed_char;

	if (check_option_hexlow(opt) == FALSE)
		return (-1);
	if (opt.flags.zero == 1 && opt.precision > 0)
		opt.flags.zero = 0;
	init_width_precision(& padding, &precision, n, opt);
	printed_char = padding + precision;
	if (opt.flags.rpadding == 0 && opt.flags.zero == 0)
		putnchar(' ', padding);
	if (opt.flags.hashtag == 1 && n != 0)
		printed_char += print_str("0x");
	if (opt.flags.rpadding == 0 && opt.flags.zero == 1)
		putnchar('0', padding);
	putnchar('0', precision);
	printed_char += print_hexlow(n);
	if (opt.flags.rpadding == 1)
		putnchar(' ', padding);
	return (printed_char);
}
