/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:17:10 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/05 18:53:06 by ple-guya         ###   ########.fr       */
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

# define MAX_PATHLEN 2048

typedef struct s_chill
{
	
	int				(*builtin[7])(char **, struct s_chill *);
	t_simple_cmd	**cmd_tab;
	char			**env;
	char			*infile;
	char			*outfile;
	int				pipefd[2];
	int				fd_in;
	int				fd_out;
	int				error_code;
}		t_chill;

//init minishell
char	**copy_env(char **env);
void	init_minishell(t_chill *shell, char **env);

// prompt
char	*display_prompt(void);

//built-in
int		isbuiltin(char **cmd, t_chill *shell);
void	ft_cd(char **cmd, t_chill *env);
void	ft_env(char **cmd, char **env);
void	ft_echo(char **cmd);
void	ft_exit(char **cmd);
void	ft_pwd(char **cmd);
void	ft_export(char **cmd, t_chill *shell);
int		ft_unset(char **cmd, t_chill *env);
char	**update_env(t_chill *shell, char *var);

//exec
void	execution_cmd(t_chill *shell);
char	**convert_list_to_tab(t_simple_cmd *input);
char	**split_path(char **env);
char	*get_valid_path(char *cmd, char **env);

//exec utils
void	free_str_tab(char ***str_tab_ptr);

#endif
