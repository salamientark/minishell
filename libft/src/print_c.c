/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:35:18 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

static	t_bool	check_option_c(t_option opt)
{
	if (opt.flags.sign != 0)
		return (FALSE);
	if (opt.flags.space != 0)
		return (FALSE);
	if (opt.flags.hashtag != 0)
		return (FALSE);
	if (opt.flags.zero != 0)
		return (FALSE);
	if (opt.flags.set_precision != 0)
		return (FALSE);
	return (TRUE);
}

int	print_char_opt(int c, t_option opt)
{
	if (check_option_c(opt) == FALSE)
		return (-1);
	if (opt.width > 0 && opt.flags.rpadding == 0)
		putnchar(' ', opt.width - 1);
	write(1, &c, 1);
	if (opt.width > 0 && opt.flags.rpadding == 1)
		putnchar(' ', opt.width - 1);
	if (opt.width == 0)
		return (1);
	return (opt.width);
}

// int	ft_print_char(int c)
// {
// 	write(1, &c, 1);
// 	return (1);
// }
