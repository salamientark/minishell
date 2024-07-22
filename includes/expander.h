/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:00:54 by dbaladro          #+#    #+#             */
/*   Updated: 2024/07/22 19:20:47 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"

// word is the word (cmd, redirection...)
// quote is a int type where	1 = quote to remove at the end
//								0 = everything else
// cmd_flag is a 'boolen' indicating if the word_tab come from the cmd part
//  mostly to now if word_splt should be performed
// It will be use like an improved char ** where each value have more infos
typedef struct s_expand
{
	char	*word;
	int		*quote;
	int		size;
	int		cmd_flag;
}				t_expand;

// free_expand.v
void		free_expand_elem(t_expand **expand_p);
void		free_expand_tab(t_expand ***expand_p);

// is_expand.c
int			is_expand(const char *str);

// expand_heredoc.c
char		*expand_heredoc(char *input, t_chill *shell);

// expanded_variable_len.c
size_t		expanded_variable_len(const char *word, t_chill *shell);

// expand_variable.c
char		*expand_variable(const char *to_expand, t_chill *shell);

// var_expand_elem.c
t_expand	*var_expand_elem(t_expand *elem, t_chill *shell);

// is_valid_expansion.c
int			is_valid_expand(const char *str);

// perform_variable_expansion.c
int			perform_variable_expansion(t_expand **expand_tab, t_chill *shell);

// word_split.c
t_expand	**word_split(t_expand *elem);

// perform_word_split.c
t_expand	**expand_replace(t_expand **expand_tab, t_expand **to_insert,
				int *index_p);
int			perform_word_split(t_expand ***expand_tab);

// make_rexpand_tab.c
t_expand	*make_expand_elem(char *str);
t_expand	**make_expand_tab(char **tab);

// expand.c
int			expand(t_simple_cmd *cmd, t_chill *shell);

//remove_quote.c
void		remove_quote(t_expand **expand_tab);

#endif
