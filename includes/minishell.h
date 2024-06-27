/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:17:10 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/27 16:18:20 by madlab           ###   ########.fr       */
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
# include <stdbool.h>
# include <errno.h>

# include "../libft/includes/libft.h"
# include "parser.h"
# include "expander.h"

# define READ_END 0
# define WRITE_END 1

# define MAGENTA "\001\033[0;35m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
# define WHITE "\001\033[0;0m\002"

// exit_shell.c
void	exit_shell(t_chill *shell, int exit_status);

// init_minishell.c
char	**new_env(void);
t_chill	*init_shell(int ac, char **av, char **env);

// prompt
// make_new_prompt.c
char	*ft_getenv(const char *key, char **env);
void	make_new_prompt(t_chill *shell);

char	*read_command(t_chill *shell);

//built-in
int		isbuiltin(char **cmd, t_chill *shell);
int		ft_cd(char **cmd, t_chill *env);
int		ft_env(char **cmd, t_chill *env);
int		ft_echo(char **cmd, t_chill *shell);
int		ft_exit(char **cmd, t_chill *shell);
int		ft_pwd(char **cmd, t_chill *shell);
void	case_noargs(char **env);
int		ft_export(char **cmd, t_chill *shell);
int		ft_unset(char **cmd, t_chill *env);
char	**update_env(t_chill *shell, char *var);

// signals
void	heredoc_sig_handler(int signum);
void	signal_handler(int signum);
void	set_signals(void);

//exec
void	init_exec(t_chill *shell);
void	update_fd(t_chill *shell);
int		exec_builtin(char **cmd, t_chill *shell);
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
