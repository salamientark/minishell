/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:39:51 by madlab            #+#    #+#             */
/*   Updated: 2024/06/04 18:45:27 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_BONUS_H
# define EXPANDER_BONUS_H

# include "../../includes/expander.h"

# define AMBIGUOUS_REDIRECT "ambiguous redirect"

// simplify_pattern_bonus.c
char	*simplify_pattern(t_expand *pattern);

// patern_match_bonus.c
int		pattern_match(const char *pattern, const char *word);

// perform_filename_expansion_bonus.c
int		perform_filename_expansion(t_expand ***expand_tab, int cmd_flag);

#endif
