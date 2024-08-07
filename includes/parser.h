/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:08:26 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/27 20:27:25 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "error.h"
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "error.h"
# include "../libft/includes/libft.h"

# define MAX_PATHLEN 2048

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

# define UNDERSCORE '_'
# define ASTERISK '*'
# define EQUAL '='

# define HERE_DOC_PROMPT "> "
# define HERE_DOC_WARNING_MSG_1 "minishell: warning: here_document at line "
# define HERE_DOC_WARNING_MSG_2 " delimited by end-of-file (wanted \'"
# define HERE_DOC_WARNING_MSG_3 "\')\n"

# define SHLVL_TOO_HIGH "warning: shell level (1000) too high, resetting to 1"
# define HERE_DOC_1 "/tmp/.here_doc_1"
# define HERE_DOC_2 "/tmp/.here_doc_2"
# define HERE_DOC_3 "/tmp/.here_doc_3"
# define HERE_DOC_4 "/tmp/.here_doc_4"
# define HERE_DOC_5 "/tmp/.here_doc_5"
# define HERE_DOC_6 "/tmp/.here_doc_6"
# define HERE_DOC_7 "/tmp/.here_doc_7"
# define HERE_DOC_8 "/tmp/.here_doc_8"
# define HERE_DOC_9 "/tmp/.here_doc_9"
# define HERE_DOC_10 "/tmp/.here_doc_10"
# define HERE_DOC_11 "/tmp/.here_doc_11"
# define HERE_DOC_12 "/tmp/.here_doc_12"
# define HERE_DOC_13 "/tmp/.here_doc_13"
# define HERE_DOC_14 "/tmp/.here_doc_14"
# define HERE_DOC_15 "/tmp/.here_doc_15"
# define HERE_DOC_16 "/tmp/.here_doc_16"

typedef struct s_btree
{
	void			*content;
	struct s_btree	*l_node;
	struct s_btree	*r_node;

}				t_btree;

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
	T_EXPAND = 6,
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
	char	**cmd;
	char	**redirection;
}				t_simple_cmd;

typedef struct s_chill
{
	int				(*builtin[7])(char **, struct s_chill *);
	t_btree			*tree;
	t_simple_cmd	**cmd_tab;
	char			**env;
	char			*infile;
	char			*outfile;
	char			*input;
	char			prompt[MAX_PATHLEN];
	int				pipefd[2];
	int				fd_in;
	int				fd_out;
	int				hd_count;
	int				nb_cmd;
	int				old_fd;
	int				builtin_ref;
	int				index_cmd;
	int				exit_status;
}				t_chill;

// 
void			builtin_tab(t_chill *shell);

// expand_strlen.c
int				expand_strlen(const char *input, int ref, int in_double_quote);

// quoted_strlen.c
int				quoted_strlen(const char *str, int ref, const char quote);

// operator.c
int				can_be_operator(const char c);
char			get_operator(const char *s);
int				is_space_metachar(const char c);
int				is_metachar(const char c);

// is_name.c
int				is_name(char *word);

// count_here_doc.c
int				heredoc_count(const char *input);

// token_utils
void			ft_token_free_list(t_token_list **elem);
t_token_list	*ft_token_get_head(t_token_list *token_list);
t_token_list	*ft_token_add_back(t_token_list *last_token,
					t_token_list *new_token);
t_token_list	*ft_token_init_one(const char *input);

// unclose_delimiter.c
int				unclosed_delimiter(const char *input);

// unlink_here_doc.c
void			unlink_here_doc(void);

// here_doc_name.c
char			*here_doc_name(char buff_name[11], int here_doc_count);

// here_doc.c
int				here_doc(const char *cmd, int ref, int *here_doc_count,
					t_chill *shell);

// syntax_error.c
int				is_followed_by_word(const char *cmd, int operator);
int				syntax_error(const char *cmd, t_chill *shell);

// tokenize.c
t_token_list	*tokenize(const char *input);

// free_cmd_tab.c
void			free_cmd_tab(t_simple_cmd ***cmd_tab);

// alloc_simple_cmd.c
t_simple_cmd	*alloc_simple_cmd(t_token_list *token_list);

// split_to_simple_cmd.c
t_simple_cmd	**split_to_simple_command(t_token_list **token_list_p);

// parse_input.c
t_simple_cmd	**parse_input(const char *input, t_chill *shell);

#endif
