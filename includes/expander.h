/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:00:54 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/29 18:38:09 by madlab           ###   ########.fr       */
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

// expand_variable.c
int		expand_variable(char **expand_result, const char *to_expand, char **env);

// expanded_variable_len.c
size_t	expanded_variable_len(const char *word, char **env);

// str_var_expansion.c
int		str_var_expansion(char **final_str, const char *word, int *split_flag,
			char **env);

// word_split.c
char	**word_split(const char *word);

// perform_variable_expansion.c
int		perform_variable_expansion(char ***tab, int cmd_flag, char **env);


// makae_rexpand_tab.c
t_expand	**make_expand_tab(char **tab);
// expand.c
void	free_expand_tab(t_expand ***expand_p);
int	expand(t_simple_cmd *cmd);
// FOR TESTING PURPOSE
void	print_expand_tab(t_expand **expand);

#endif
