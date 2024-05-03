/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:47:05 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:35:01 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_opt.h"

// When compiling with clang you can have a flags multiple time without errors
// This is not the case for gcc or cc which will not compile
t_bool	check_flags(t_flags flags)
{
	if (flags.rpadding != 0 && flags.rpadding != 1)
		return (FALSE);
	if (flags.hashtag != 0 && flags.hashtag != 1)
		return (FALSE);
	if (flags.sign != 0 && flags.sign != 1)
		return (FALSE);
	if (flags.space != 0 && flags.space != 1)
		return (FALSE);
	if (flags.zero != 0 && flags.zero != 1)
		return (FALSE);
	return (TRUE);
}

t_bool	is_flag(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')
		return (TRUE);
	return (FALSE);
}

void	add_flag(t_option *option, const char c)
{
	if (c == '-')
		option->flags.rpadding += 1;
	else if (c == '+')
		option->flags.sign += 1;
	else if (c == ' ')
		option->flags.space += 1;
	else if (c == '#')
		option->flags.hashtag += 1;
	else if (c == '0')
		option->flags.zero += 1;
	else
		option->flags.set_precision += 1;
}

t_flags	init_flags(void)
{
	t_flags	flag;

	flag.rpadding = 0;
	flag.sign = 0;
	flag.space = 0;
	flag.hashtag = 0;
	flag.zero = 0;
	flag.set_precision = 0;
	return (flag);
}
