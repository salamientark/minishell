/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:46:52 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:35:18 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_bool	check_option_u(t_option opt)
{
	if (opt.flags.hashtag != 0)
		return (FALSE);
	if (opt.flags.space != 0)
		return (FALSE);
	if (opt.flags.sign != 0)
		return (FALSE);
	if (opt.flags.rpadding != 0 && opt.flags.zero != 0)
		return (FALSE);
	return (TRUE);
}

static	void	init_wid_prec(int *width, int *prec, unsigned int n,
	t_option opt)
{
	int	n_len;

	n_len = nbr_base_len((long long) n, 10);
	*prec = opt.precision - n_len;
	if (*prec < 0)
		*prec = 0;
	*width = opt.width - (n_len + *prec);
	if (*width < 0)
		*width = 0;
}

static int	ft_print_uint_rec(unsigned int n)
{
	if (n)
		return (ft_print_uint_rec(n / 10) + print_char(n % 10 + '0'));
	return (0);
}

int	ft_print_uint(unsigned int n)
{
	if (n)
		return (ft_print_uint_rec(n));
	print_char('0');
	return (1);
}

int	print_uint_opt(int n, t_option opt)
{
	int		padding_len;
	int		precision;
	int		printed_char;

	if (check_option_u(opt) == FALSE)
		return (-1);
	if (opt.flags.zero == 1 && opt.precision > 0)
		opt.flags.zero = 0;
	init_wid_prec(&padding_len, &precision, n, opt);
	printed_char = padding_len + precision;
	if (opt.flags.rpadding == 0 && opt.flags.zero == 1)
		putnchar('0', padding_len);
	if (opt.flags.rpadding == 0 && opt.flags.zero == 0)
		putnchar(' ', padding_len);
	putnchar('0', precision);
	if (!(n == 0 && opt.flags.set_precision != 0 && opt.precision == 0
			&& opt.width == 0))
		printed_char += ft_print_uint(n);
	if (opt.flags.rpadding == 1)
		putnchar(' ', padding_len);
	return (printed_char);
}
