/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:24:37 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/07 16:24:37 by ple-guya         ###   ########.fr       */
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
	shell->fd_in = open(redirect_from, O_RDWR);
	if (shell->fd_in == -1)
	{	
		perror(redirect_from);
		exit(1);
	}
	shell->infile = redirect_from;
}

void	get_file(t_chill *shell, char **redirections)
{
	char	buffer[11];
	int		i;

	i = 0;
	shell->hd_count = 0;
	shell->outfile = NULL;
	shell->infile = NULL;
	while (redirections[i])
	{
		if (!ft_strcmp(redirections[i], "<<"))
		{
			shell->hd_count++;
			here_doc_name(buffer , shell->hd_count);
			i++;
		}
		if (!ft_strcmp(redirections[i], "<"))
			get_infile(shell, redirections[++i]);
		if (!ft_strcmp(redirections[i], ">"))
			get_outfile(shell, redirections[++i]);
		i++;
	}
	if (!shell->infile && shell->nb_cmd == 1)	
		shell->fd_in = 0;
    if (!shell->infile && shell->nb_cmd != 1)
		shell->fd_in = shell->pipefd[READ_END];
	if (!shell->outfile && (shell->nb_cmd == 1 || (shell->index_cmd + 1) == shell->nb_cmd))
		shell->fd_out = 1;
	if (!shell->outfile && shell->nb_cmd != 1)
		shell->fd_out = shell->pipefd[WRITE_END];
}
