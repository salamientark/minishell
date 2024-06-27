/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:24:37 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/24 18:01:21 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	init_file(t_chill *shell, char **redirections)
{
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->outfile = NULL;
	shell->infile = NULL;
	if (!redirections)
	{
		shell->fd_in = dup(STDIN_FILENO);
		shell->fd_out = dup(STDOUT_FILENO);
		return (FALSE);
	}
	return (TRUE);
}

static void	get_outfile(t_chill *shell, char *redirect_to, bool append)
{
	if (shell->fd_out != -1)
	{
		close (shell->fd_out);
		shell->fd_out = -1;
	}
	if (append)
		shell->fd_out = open(redirect_to, O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		shell->fd_out = open(redirect_to, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (shell->outfile)
	{
		free(shell->outfile);
		shell->outfile = NULL;
	}
	shell->outfile = ft_strdup(redirect_to);
}

static void	get_infile(t_chill *shell, char *redirect_from)
{
	int	errno_cp;

	if (shell->fd_in != -1)
	{
		close(shell->fd_in);
		shell->fd_in = -1;
	}
	shell->fd_in = open(redirect_from, O_RDWR);
	if (shell->fd_in == -1)
	{
		errno_cp = errno;
		print_error(redirect_from, strerror(errno_cp));
		exit_shell(shell, 1);
	}
	if (shell->infile)
	{
		free(shell->infile);
		shell->infile = NULL;
	}
	shell->infile = ft_strdup(redirect_from);
}

static void	get_heredocs(t_chill *shell)
{
	char	buffer[11];

	here_doc_name(buffer, shell->hd_count++);
	if (shell->infile)
	{
		free(shell->infile);
		shell->infile = NULL;
	}
	shell->infile = ft_strdup(buffer);
	if (shell->fd_in != -1)
	{
		close(shell->fd_in);
		shell->fd_in = -1;
	}
	shell->fd_in = open(buffer, O_RDONLY, 0400);
	ft_putnbr_fd(shell->fd_in, 2);
}

void	get_file(t_chill *shell, char **redirections)
{
	int	i;

	i = 0;
	if (!init_file(shell, redirections))
		return ;
	while (redirections[i])
	{
		if (!ft_strcmp(redirections[i], "<<"))
			get_heredocs(shell);
		if (!ft_strcmp(redirections[i], ">>"))
			get_outfile(shell, redirections[i + 1], TRUE);
		if (!ft_strcmp(redirections[i], "<"))
			get_infile(shell, redirections[i + 1]);
		if (!ft_strcmp(redirections[i], ">"))
			get_outfile(shell, redirections[i + 1], FALSE);
		i = i + 2;
	}
	if (!shell->infile)
		shell->fd_in = dup(STDIN_FILENO);
	if (!shell->outfile)
		shell->fd_out = dup(STDOUT_FILENO);
}
