/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:17:10 by dbaladro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/15 18:35:08 by marvin           ###   ########.fr       */
=======
/*   Updated: 2024/05/15 01:59:19 by dbaladro         ###   ########.fr       */
>>>>>>> origin/lexer
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

# define MAX_PATHLEN 2048

// prompt
char	*display_prompt(void);

//built-in
void	ft_cd(char **cmd, char **env);
void    ft_env(char **cmd, char **env);
void    isbuiltin(char **cmd, char **env);

#endif
