/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:08:26 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/15 18:08:44 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <errno.h>
# include "libft.h"
# include "error.h"

# define DOUBLE_QUOTE '\"' 
# define SINGLE_QUOTE '\'' 
# define LEFT_BRACE '{'
# define RIGHT_BRACE '}'
# define DOLLAR '$'
# define LEFT_PARENTHESIS '('
# define RIGHT_PARENTHESIS ')'
# define PIPE '|'
# define LESS_THAN '<'
# define GREATER_THAN '>'
# define SPACE ' '
# define AMPERSAND '&'
# define TAB '\t'
# define NEWLINE '\n'

int	unclosed_delimiter(const char *input);

// ft_delimiter.c
int	is_opening_delimiter(const char *str);
int	is_closing_delimiter(const char c, const char delimiter);

// int	is_opening_delimiter(const char c);
// int	is_closing_delimiter(const char limiter, const char c);

// ft_shell_type.c
// int	is_control_operator(const char c);
// int	is_redirection_operator(const char c);
// int	is_operator(const char c);
int	is_space_metachar(const char c);
int	is_pipe(const char *s);

// split_input.c
char	**split_input(const char *input);

#endif
