/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:40:48 by madlab            #+#    #+#             */
/*   Updated: 2024/05/14 11:32:25 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# define BASH "minishell"

void	syntax_error(const char *token);
void	print_error(char *function, int errno);

#endif
