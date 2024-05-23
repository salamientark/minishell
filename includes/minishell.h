/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:17:10 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/23 16:45:58 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parser.h"

# define MAX_PATHLEN 2048

typedef struct s_chill
{
	char	**env;
	
	t_simple_cmd *rastaman;
}	t_chill;

//init minishell
char	**copy_env(char **env);

// prompt
char	*display_prompt(void);

//built-in
int		isbuiltin(char **cmd, t_chill *shell);
void	ft_cd(char **cmd, char **env);
void	ft_env(char **cmd, char **env);
void	ft_echo(char **cmd);
void	ft_exit(char **cmd);
void	ft_pwd(char **cmd);
void	ft_export(char **cmd, t_chill *shell);
int	ft_unset(char **cmd, t_chill *env);

//exec
char	**convert_list_to_tab(t_simple_cmd *input);

#endif
