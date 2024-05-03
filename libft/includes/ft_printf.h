/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:08:19 by dbaladro          #+#    #+#             */
/*   Updated: 2023/11/16 20:26:28 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "ft_printf_opt.h"
# include <stdarg.h>
# include <unistd.h>

# define MAX_INT 2147483647
# define MIN_INT -2147483648

int	print_char(char c);
int	print_char_opt(int c, t_option opt);
int	print_str_opt(const char *str, t_option opt);
int	print_str(const char *s);
int	ft_print_uint(unsigned int n);
int	print_uint_opt(int n, t_option opt);
int	print_int_opt(int n, t_option opt);
int	printf_xlow_opt(unsigned int n, t_option opt);
int	print_xup_opt(unsigned int n, t_option opt);
int	print_p_opt(void *n, t_option opt);
int	ft_printf(const char *s, ...);

#endif
