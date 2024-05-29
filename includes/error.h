/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:40:48 by madlab            #+#    #+#             */
/*   Updated: 2024/05/29 01:09:17 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include "../libft/includes/libft.h"
# include "parser.h"
# define BASH "minishell"
# define HERE_DOC_COUNT_EXCEEDED "minishell: maximum here-document count \
exceeded"

void	print_syntax_error(const char *input, int ref, char operator);
void	print_error(char *function, char *error);
void	unclosed_delimiter_error(const char *str, int ref);

#endif
