/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:24:37 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/14 10:16:02 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_outfile(t_chill *shell, char *redirect_to)
{
	shell->fd_out = open(redirect_to, O_RDWR | O_CREAT | O_TRUNC, 0666);
	shell->outfile = redirect_to;
}

static void	get_infile(t_chill *shell, char *redirect_from)
{
	int	errno_cp;

	shell->fd_in = open(redirect_from, O_RDWR);
	if (shell->fd_in == -1)
	{
		errno_cp = errno;
		print_error(redirect_from, strerror(errno_cp));
		exit(exit_shell(shell, errno_cp));
	}
	shell->infile = redirect_from;
}

void	get_file(t_chill *shell, char **redirections)
{
	char	buffer[11];
	int		i;

	i = 0;
	shell->outfile = NULL;
	shell->infile = NULL;
	while (redirections[i])
	{
		if (!ft_strcmp(redirections[i], "<<"))
		{
			here_doc_name(buffer, shell->hd_count++);
			open(buffer, O_RDWR);
		}
		if (!ft_strcmp(redirections[i], ">>"))
			open(redirections[i + 1], O_RDWR | O_APPEND);
		if (!ft_strcmp(redirections[i], "<"))
			get_infile(shell, redirections[i + 1]);
		if (!ft_strcmp(redirections[i], ">"))
			get_outfile(shell, redirections[i + 1]);
		i = i + 2;
	}
	if (!shell->infile)
		shell->fd_in = dup(STDIN_FILENO);
	if (!shell->outfile)
		shell->fd_out = dup(STDOUT_FILENO);
}
