/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:39:51 by madlab            #+#    #+#             */
/*   Updated: 2024/06/04 03:53:01 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_BONUS_H
# define EXPAND_BONUS_H

# include "../../includes/expand.h"

// simplify_pattern_bonus.c
char	*simplify_pattern(t_expand *pattern);

// perform_filename_expansion_bonus.c
int		perform_filename_expansion(t_expand ***expand_tab, int cmd_flag);

#endif
