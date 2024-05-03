/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_opt.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:47:01 by dbaladro          #+#    #+#             */
/*   Updated: 2023/11/16 17:27:36 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_OPT_H
# define FT_PRINTF_OPT_H

# include <stddef.h>
# include <unistd.h> 

typedef struct s_flags
{
	unsigned int	rpadding;
	unsigned int	sign;
	unsigned int	space;
	unsigned int	hashtag;
	unsigned int	zero;
	unsigned int	set_precision;
}					t_flags;

typedef struct s_option
{
	t_flags			flags;
	unsigned int	width;
	unsigned int	precision;
	char			specifier;
	size_t			len;
}					t_option;

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0,
}					t_bool;

t_bool			check_flags(t_flags flags);
t_bool			is_flag(char c);
void			add_flag(t_option *option, const char c);
t_flags			init_flags(void);
t_option		make_option(const char *s);
unsigned int	make_nbr(const char **s);
int				nbr_base_len(long long n, int base);
void			putnchar(const char c, int n);

#endif