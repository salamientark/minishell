/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:17:10 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/17 14:59:05 by ple-guya         ###   ########.fr       */
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
# include "expander.h"
# include <sys/fcntl.h>
# include <sys/types.h>
#include <signal.h>
# include <errno.h>

# define READ_END 0
# define WRITE_END 1

# define MAX_PATHLEN 2048


//init minishell
char	**copy_env(char **env);
void	init_minishell(t_chill *shell, char **env);

// prompt
char	*display_prompt(void);

//built-in
int		isbuiltin(char **cmd, t_chill *shell);
int	ft_cd(char **cmd, t_chill *shell);
int	ft_env(char **cmd, t_chill *shell);
int	ft_echo(char **cmd, t_chill *shell);
int	ft_exit(char **cmd, t_chill *shell);
int	ft_pwd(char **cmd, t_chill *shell);
int	ft_export(char **cmd, t_chill *shell);
int		ft_unset(char **cmd, t_chill *env);
char	**update_env(t_chill *shell, char *var);

//exec
void	execution_cmd(t_chill *shell);
char	**convert_list_to_tab(t_simple_cmd *input);
char	**split_path(char **env);
char	*get_valid_path(char *cmd, char **env);
int		is_last_cmd(t_chill *shell);
int		cmd_count(t_simple_cmd **cmd);
void	redirect_for_next_cmd(t_chill *shell);

//exec utils
void	get_file(t_chill *shell, char **redirection);
void	redirect(t_chill *shell);
void	free_str_tab(char ***str_tab_ptr);

#endif
