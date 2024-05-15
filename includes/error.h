/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:40:48 by madlab            #+#    #+#             */
/*   Updated: 2024/05/14 14:32:39 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include "../libft/includes/libft.h"
# define BASH "minishell"

void	syntax_error(const char *token);
void	print_error(char *function, char *error);

#endif
