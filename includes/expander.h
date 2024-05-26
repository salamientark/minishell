/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:00:54 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/26 19:35:12 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"

typedef struct s_expand
{
	char	**word_tab;
	char	**type;
}				t_expand;

// is_expand.c
int		is_expand(const char *str);

// expand_var.c
int		expand_var(char **expand_result, const char *to_expand, char **env);

// var_expand_strlen.c
size_t	var_expand_strlen(const char *word, char **env);

// str_var_expansion.c
int		str_var_expansion(char **final_str, const char *word, int *split_flag,
			char **env);

// word_split.c
char	**word_split(const char *word);

// perform_var_expansion.c
int		perform_var_expansion(char ***tab, int cmd_flag, char **env);

#endif
