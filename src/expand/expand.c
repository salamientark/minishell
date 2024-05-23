/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:33:20 by madlab            #+#    #+#             */
/*   Updated: 2024/05/23 01:42:11 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


char	**expand_tab(char **tab, int cmd_flag, char **env)
{
	char	**final_tab;

	final_tab = perform_var_expansion(tab, env);
	if (!final_tab)
		return (NULL);
}

int	expand(t_simple_cmd *simple_cmd, char **env)
{
	int	expand_result;

	expand_result = 
}
