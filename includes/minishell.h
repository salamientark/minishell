/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:17:10 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/16 16:41:52 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
# include <unistd.h>
# include "parser.h"
# include "error.h"

# define MAX_PATHLEN 2048

// prompt
char	*display_prompt(void);

//built-in
void	ft_cd(char **cmd, char **env);
void    ft_env(char **cmd, char **env);
void    isbuiltin(char **cmd, char **env);
void	ft_echo(char **cmd);

#endif
