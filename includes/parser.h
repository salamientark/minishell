/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:08:26 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/15 21:06:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

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

# define AND 2
# define OR 3
# define APPEND 4
# define HERE_DOC 5

int	unclosed_delimiter(const char *input);
int	first_pass(const char *cmd);

// ft_delimiter.c
// int	is_opening_delimiter(const char *str);
// int	is_closing_delimiter(const char c, const char delimiter);

// int	is_opening_delimiter(const char c);
// int	is_closing_delimiter(const char limiter, const char c);

// ft_shell_type.c
// int	is_control_operator(const char c);
// int	is_redirection_operator(const char c);
// int	is_operator(const char c);
int	is_space_metachar(const char c);
int	is_pipe(const char *s);

// src/
int	expand_strlen(const char *input, int ref);
int	quoted_strlen(const char *str, int ref, const char quote);

#endif
