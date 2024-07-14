/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:24:54 by marvin            #+#    #+#             */
/*   Updated: 2024/06/14 07:54:02 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char **cmd)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			j = 1;
			while (cmd[i][j] == 'n')
				j++;
			if (!cmd[i][j])
				flag++;
		}
		i++;
	}
	return (flag);
}

// static int	write_quote(char *str, int ref, char quote)
// {
// 	int	quote_len;

// 	quote_len = quoted_strlen(str, ref, quote);
// 	ref++;
// 	if (quote_len > 2)
// 		write(1, str + ref, quote_len - 2);
// 	return (quote_len);
// }

int	ft_echo(char **cmd, t_chill *shell)
{
	int	i;
	int	j;
	int	fd;
	int	flag;

	fd = dup(STDOUT_FILENO);
	(void)shell;
	flag = check_flag(cmd);
	i = flag + 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
			ft_putchar_fd(cmd[i][j++], fd);
		if (cmd[++i])
			write(fd, " ", 1);
	}
	if (!flag)
		write(fd, "\n", 1);
	close(fd);
	return (0);
}
