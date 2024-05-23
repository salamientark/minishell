/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:08:26 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/23 15:10:49 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// # include "minishell.h"
# include "error.h"
# include <errno.h>
# include <sys/wait.h>

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

# define HERE_DOC_PROMPT "> "
# define HERE_DOC_WARNING_MSG_1 "minishell: warning: here_document at line "
# define HERE_DOC_WARNING_MSG_2 " delimited by end-of-file (wanted \'"
# define HERE_DOC_WARNING_MSG_3 "\')\n"

typedef enum e_token_type
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

typedef struct s_token_list
{
	char				*token;
	int					size;
	t_token_type		type;
	struct s_token_list	*prev;
	struct s_token_list	*next;
}				t_token_list;

typedef struct s_simple_cmd
{
	t_token_list	*cmd;
	t_token_list	*redirect_from;
	t_token_list	*redirect_to;
}				t_simple_cmd;

void	**builtin_tab(void);

// expand_strlen.c
int					expand_strlen(const char *input, int ref);

// quoted_strlen.c
int					quoted_strlen(const char *str, int ref, const char quote);

// operator.c
int					can_be_operator(const char c);
char				get_operator(const char *s);
int					is_space_metachar(const char c);
int					is_metachar(const char c);

// token_utils.c
t_token_list		*get_token_list_head(t_token_list *token_list);
t_token_list		*add_token(t_token_list *last_token,
						t_token_list *new_token);
void				free_token_list(t_token_list **elem);

int					unclosed_delimiter(const char *input);
int					here_doc(const char *cmd, int ref, int stdin_fd);
int					syntax_error(const char *cmd);
t_token_list		*tokenize(const char *input);

// split_to_simple_cmd.c
int					count_simple_command(t_token_list *token_list);
t_simple_cmd		**split_to_simple_command(t_token_list **token_list_p);

// parse_input.c
t_simple_cmd		**parse_input(const char *input);

#endif
