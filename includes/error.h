/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:40:48 by madlab            #+#    #+#             */
/*   Updated: 2024/05/18 13:23:18 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include "../libft/includes/libft.h"
# include "parser.h"
# define BASH "minishell"

void	print_syntax_error(const char *input, int ref, char operator);
void	print_error(char *function, char *error);
void	unclosed_delimiter_error(const char *str, int ref);

#endif
