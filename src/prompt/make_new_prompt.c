/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:48:50 by madlab            #+#    #+#             */
/*   Updated: 2024/06/24 18:12:56 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Get environment value like getenv 
 * */
char	*ft_getenv(const char *key, char **env)
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

/* add new color color to dest
 * WARNING : No check are performed, you should be sur that dest is big enough
 * and color is valid 
 * */
static void	change_color(char *dest, char *color)
{
	ft_strcat(dest, color);
}

static int	match_home(const char *home, const char *cwd)
{
	size_t	home_len;

	if (!home)
		return (0);
	home_len = ft_strlen(home);
	if (home_len <= 1)
		return (0);
	if (home[home_len - 1] == '/')
		return (0);
	if (ft_strlen(cwd) < home_len)
		return (0);
	if (ft_strncmp(home, cwd, home_len) != 0)
		return (0);
	return (1);
}

/* write the directory part of the prompt into it
 * */
void	prompt_cwd(t_chill *shell)
{
	char	*home;
	char	cwd[MAX_PATHLEN];
	int		index;

	if (!getcwd(cwd, MAX_PATHLEN) || (ft_strlen(cwd) + 22 > MAX_PATHLEN))
	{
		shell->exit_status = 1;
		change_color(shell->prompt, RED);
		return ((void)ft_strcat(shell->prompt, "∅ "));
	}
	change_color(shell->prompt, MAGENTA);
	home = ft_getenv("HOME", shell->env);
	if (match_home(home, cwd) == 0)
		return ((void) ft_strcat(shell->prompt, cwd));
	ft_strcat(shell->prompt, "~");
	index = 0;
	while (home[index] && home[index] == cwd[index])
		index++;
	if (!cwd[index])
		return ((void)strcat(shell->prompt, "/"));
	if (home[index - 1] != '/')
		ft_strcat(shell->prompt, "/");
	index += (home[index - 1] != '/');
	ft_strcat(shell->prompt, cwd + index);
}

void	make_new_prompt(t_chill *shell)
{
	ft_bzero(shell->prompt, MAX_PATHLEN);
	prompt_cwd(shell);
	if (shell->exit_status == 0)
		change_color(shell->prompt, GREEN);
	else
		change_color(shell->prompt, RED);
	ft_strcat(shell->prompt, " ❯ ");
	change_color(shell->prompt, WHITE);
	return ;
}
