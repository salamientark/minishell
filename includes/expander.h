/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:00:54 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/30 19:09:14 by madlab           ###   ########.fr       */
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

// is_expand.c
int		is_expand(const char *str);

// expanded_variable_len.c
size_t	expanded_variable_len(const char *word, char **env);

// expand_variable.c
char		*expand_variable(const char *to_expand, char **env);

// var_expand_elem.c
t_expand		*var_expand_elem(t_expand *elem, char **env);

// word_split.c
t_expand	**word_split(t_expand *elem);

// perform_variable_expansion.c
int		perform_variable_expansion(t_expand **expand_tab, char **env);

// word_split.c
t_expand	**word_split(t_expand *elem);


// perform_word_split.c
int	perform_word_split(t_expand ***expand_tab);


// makae_rexpand_tab.c
void	free_expand_tab(t_expand ***expand_p);
t_expand	**make_expand_tab(char **tab);
// expand.c
int	expand(t_simple_cmd *cmd, char **env);
// FOR TESTING PURPOSE
void	print_expand_tab(t_expand **expand);

#endif
