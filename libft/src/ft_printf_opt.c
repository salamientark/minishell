/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:10:42 by dbaladro          #+#    #+#             */
/*   Updated: 2023/11/16 17:15:14 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_opt.h"

static t_bool	is_specifier(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%')
		return (TRUE);
	return (FALSE);
}

t_option	init_option(void)
{
	t_option	opt;

	opt.flags = init_flags();
	opt.width = 0;
	opt.precision = 0;
	opt.specifier = 0;
	opt.len = 0;
	return (opt);
}

static t_bool	check_option(t_option opt)
{
	if (check_flags(opt.flags) == FALSE)
		return (FALSE);
	if (opt.specifier == 0)
		return (FALSE);
	return (TRUE);
}

t_option	make_option(const char *s)
{
	t_option	options;
	const char	*ptr;

	ptr = s;
	options = init_option();
	while (*ptr && is_flag(*ptr))
		add_flag(&options, *ptr++);
	if (*ptr && ('0' <= *ptr && *ptr <= '9'))
	{
		options.width = make_nbr(&ptr);
	}
	if (*ptr && *ptr == '.')
	{
		add_flag(&options, '.');
		ptr++;
		options.precision = make_nbr(&ptr);
	}
	if (*ptr && is_specifier(*ptr))
		options.specifier = *ptr;
	options.len = ptr - s;
	if (check_option(options) == TRUE)
		return (options);
	return (init_option());
}
