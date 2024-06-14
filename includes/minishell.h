/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:17:10 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/14 10:32:12 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/fcntl.h>
# include <sys/types.h>
# include <signal.h>
# include <errno.h>

# include "../libft/includes/libft.h"
# include "parser.h"
# include "expander.h"

# define READ_END 0
# define WRITE_END 1

# define MAX_PATHLEN 2048

// exit_shell.c
int		exit_shell(t_chill *shell, int exit_status);

// init_minishell.c
t_chill	*init_shell(char **env);

// prompt
char	*display_prompt(void);

//built-in
int		isbuiltin(char **cmd, t_chill *shell);
int		ft_cd(char **cmd, t_chill *env);
int		ft_env(char **cmd, char **env);
int		ft_echo(char **cmd, t_chill *shell);
int		ft_exit(char **cmd, t_chill *shell);
int		ft_pwd(char **cmd);
int		ft_export(char **cmd, t_chill *shell);
int		ft_unset(char **cmd, t_chill *env);
char	**update_env(t_chill *shell, char *var);

// signals
void	heredoc_sig_handler(int signum);
void	signal_handler(int signum);
void	set_signals(void);

//exec
int		exec_builtin(t_chill *shell);
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
