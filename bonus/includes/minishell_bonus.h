/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:17:10 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/14 08:51:35 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "../../libft/includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parser_bonus.h"
# include "expander_bonus.h"
# include "../../includes/minishell.h"

# define MAX_PATHLEN 2048

// INIT
int		exit_shell(t_chill *shell, int exit_status);

// parenthesis_strlen_bonus.c
int		parenthesis_strlen(const char *str, int ref);

// exec_tree_bonus.c
int		exec_tree(t_btree *tree, t_chill *shell);
// void	exec_tree_void(t_btree *tree, t_chill *shell);

#endif
