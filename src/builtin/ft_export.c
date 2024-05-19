/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:42:38 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/16 23:42:38 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	case_noarg(char **env)
{
	int i;

	i = 0;
	while(env[i])
		printf("export %s\n", env[i++]);
}

static int	check_valid_var(char *cmd)
{
	int		i;
	int		len;
	int		is_equal_sign;

	i = 0;
	len = 0;
	is_equal_sign = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			is_equal_sign = 1;
		if ((cmd[i] == SINGLE_QUOTE || cmd[i] == DOUBLE_QUOTE) && cmd[i])
			i++;
		if ((cmd[i] == '{' || cmd[i] == '}' || cmd[i] == '[' || cmd[i] == ']') 
			&&  !is_equal_sign)
		{
			ft_putendl_fd("invalid name for export", 2);
			return (0);
		}
		len++;
		i++;
	}
	return(len);
}

static char	*get_var(char *cmd, int len)
{

}

static void	add_to_env(char *cmd, char **env)
{
	int		len;

	(void)env;
	len = check_valid_var(cmd);
	printf("%d\n", len); 
	if (!len)
		return ;
	
}

void	ft_export(char **cmd, char **env)
{
	int i;

	i = 1;
	if (!cmd[i])
		return (case_noarg(env));
	while(cmd[i + 1])
		i++;
	add_to_env(cmd[i], env);
}