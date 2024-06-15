/* ************************************************************************** */
/*                                                                            */
/*      G                                                  :::      ::::::::   */
/*   make_new_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:48:50 by madlab            #+#    #+#             */
/*   Updated: 2024/06/15 19:19:39 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_colored(char *dest,char *text,char *color)
{
	if (!dest || !text || !color)
		return ;
	ft_strcat(dest, color);
	ft_strcat(dest, text);
	ft_strcat(dest, "\002");
}

static char	*ft_getenv(const char *key, char **env)
{
	char	*value;
	int		index;
	int		key_len;

	if (!env)
		return (NULL);
	index = 0;
	key_len = ft_strlen(key);
	while (env[index])
	{
		if (ft_strncmp(env[index], key, key_len) == 0 && env[index][key_len]
			&& env[index][key_len] == '=')
		{
			value = &(env[index][key_len + 1]);
			return (value);
		}
		index++;
	}
	return (NULL);
}

static void	short_home(char *dest, char *home, char *dir, char *color)
{
	int	dir_start;

	ft_strcpy(dest, color);
	ft_strcat(dest, "~");
	dir_start = 0;
	while (home[dir_start] && home[dir_start] == dir[dir_start])
		dir_start++;
	if (!dir[dir_start])
	{
		ft_strcat(dest, "\002");
		add_colored(dest, NULL, WHITE);
		return ;
	}
	if (home[dir_start - 1] != '/')
		ft_strcat(dest, "/");
	dir_start += (home[dir_start - 1] != '/');
	ft_strcat(dest, dir + dir_start);
	ft_strcat(dest, "\002");
	add_colored(dest, NULL, WHITE);
	return ;
}

static void	reset_color(char *dest, char *color)
{
	ft_strcat(dest, color);
	ft_strcat(dest, "\002");
}

void	make_new_prompt(t_chill *shell)
{
	char	*home;
	char	cwd[MAX_PATHLEN];
	size_t	home_len;

	ft_bzero(shell->prompt, MAX_PATHLEN);
	if (!getcwd(cwd, MAX_PATHLEN) || (ft_strlen(cwd) + 22 > MAX_PATHLEN))
	{
		shell->exit_status = 1;
		add_colored(shell->prompt, "∅ ❯ ", RED);
		return (reset_color(shell->prompt, WHITE));
	}
	add_colored(shell->prompt, cwd, MAGENTA);
	home = ft_getenv("HOME", shell->env);
	if (!home || ft_strlen(home) <= 1)
	{
		shell->exit_status = 1;
		add_colored(shell->prompt, " ❯ ", RED);
		return (reset_color(shell->prompt, WHITE));
	}
	home_len = ft_strlen(home);
	if (ft_strncmp(home, cwd, home_len) == 0)
		short_home(shell->prompt, home, cwd, MAGENTA);
	if (shell->exit_status == 0)
		add_colored(shell->prompt, " ❯ ", GREEN);
	else
		add_colored(shell->prompt, " ❯ ", RED);
	return (reset_color(shell->prompt, WHITE));
}
