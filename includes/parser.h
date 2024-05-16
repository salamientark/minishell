/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:08:26 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/16 21:10:55 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
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

# define AND 2
# define OR 3
# define APPEND 4
# define HERE_DOC 5

# define HERE_DOC_FILE "/tmp/.here_doc"
# define HERE_DOC_PROMPT "> "
# define HERE_DOC_WARNING_MSG_1 "minishell: warning: here_document at line "
# define HERE_DOC_WARNING_MSG_2 " delimited by end-of-file (wanted \'"
# define HERE_DOC_WARNING_MSG_3 "\')\n"

typedef enum	e_token_type
{
	WORD = 0,
	T_PIPE = 124,
	T_LESS_THAN = 60,
	T_GREATER_THAN = 62,
	T_LEFT_PARENTHESIS = 40,
	T_RIGHT_PARENTHESIS = 41,
	T_AND = 2,
	T_OR = 3,
	T_APPEND = 4,
	T_HERE_DOC = 5,

}				t_token_type;

typedef struct	s_token_list
{
	char				*token;
	int					size;
	t_token_type		type;
	struct s_token_list	*prev;
	struct s_token_list	*next;
}				t_token_list;

// operator.c
char	get_operator(const char *s);
int		is_space_metachar(const char c);
int		is_metachar(const char c);

int			unclosed_delimiter(const char *input);
int			here_doc(const char *cmd, int ref, int stdin_fd);
int			first_pass(const char *cmd);
t_token_list	*tokenize(const char *input);

// ft_delimiter.c
// int	is_opening_delimiter(const char *str);
// int	is_closing_delimiter(const char c, const char delimiter);

// int	is_opening_delimiter(const char c);
// int	is_closing_delimiter(const char limiter, const char c);

// ft_shell_type.c
// int	is_control_operator(const char c);
// int	is_redirection_operator(const char c);
// int	is_operator(const char c);
int		is_space_metachar(const char c);
int		is_pipe(const char *s);

// src/
int		expand_strlen(const char *input, int ref);
int		quoted_strlen(const char *str, int ref, const char quote);

#endif
