/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:46:29 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:35:18 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static	t_bool	check_option_p(t_option opt)
{
	if (opt.flags.hashtag != 0)
		return (FALSE);
	if (opt.flags.set_precision != 0)
		return (FALSE);
	if (opt.flags.sign != 0)
		return (FALSE);
	if (opt.flags.space != 0)
		return (FALSE);
	return (TRUE);
}

static	int	count_p(unsigned long long n)
{
	if (n)
	{
		if (n % 16 > 9)
			return (count_p(n / 16) + 1);
		else
			return (count_p(n / 16) + 1);
	}
	return (0);
}

static void	init_width(int *width, unsigned long long n, t_option opt)
{
	if (n != 0)
		*width = opt.width - count_p(n) - 2;
	else
		*width = opt.width - 5;
	if (*width < 0)
		*width = 0;
}

static int	print_p(unsigned long long n)
{
	if (n)
	{
		if (n % 16 > 9)
			return (print_p(n / 16) + print_char(n % 16 + 'a' - 10));
		else
			return (print_p(n / 16) + print_char(n % 16 + '0'));
	}
	return (0);
}

int	print_p_opt(void *n, t_option opt)
{
	int					padding;
	int					printed_char;
	unsigned long long	nbr;

	if (check_option_p(opt) == FALSE)
		return (-1);
	nbr = (unsigned long long) n;
	init_width(&padding, nbr, opt);
	printed_char = padding;
	if (opt.flags.rpadding == 0)
		putnchar(' ', padding);
	if (nbr != 0)
	{
		write(1, "0x", 2);
		printed_char += 2;
		printed_char += print_p(nbr);
	}
	else
	{
		write(1, "(nil)", 5);
		printed_char += 5;
	}
	if (opt.flags.rpadding == 1)
		putnchar(' ', padding);
	return (printed_char);
}
