/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:48:50 by madlab            #+#    #+#             */
/*   Updated: 2024/06/14 19:11:52 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_new_prompt(t_chill *shell)
{
	char	*home;
	size_t	home_len;

	if (!getcwd(shell->prompt + 10, MAX_PATHLEN))
		return ((void)ft_strcpy(shell->prompt, DEFAULT_PROMPT));
	home = getenv("HOME");
	if (!home)
		return ((void) printf("NO HOME\n"));
	home_len = ft_strlen(home);
	if (home_len <= 1)
		return ((void) printf("NO HOME\n"));
	if (ft_strncmp(home, shell->prompt + 10, home_len) == 0)
	{
		if (home[home_len - 1] != '/' && shell->prompt[home_len + 10] != '/')
			return ;
		home_len += (home[home_len - 1] != '/');
		ft_strcpy(shell->prompt + 10, "❯ ~");
		ft_strcat(shell->prompt + 12, shell->prompt + home_len + 12);
	}
}
