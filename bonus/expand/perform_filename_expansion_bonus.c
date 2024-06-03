/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_filename_expansion_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 00:06:55 by madlab            #+#    #+#             */
/*   Updated: 2024/06/03 09:54:56 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_bonus.h"

int	perform_filename_expansion(t_expand **expand_tab)
{
	char			cwd_name[MAX_PATH_LEN];
	DIR				*dir_ptr;
	struct dirent	*dir;

	cwd = getcwd(cwd, MAX_PATH_LEN);
	if (!getcwd)
		return (print_error("getcwd", strerror(errno)), 1);
	dir_ptr = opendir(cwd_name);
	if (!dir_ptr)
		return (print_error("opendir", strerror(errno)), 1);
	dir = read_dir(dir);
	if (!dir && errno != 0)
		return (closedir(dir_ptr), 1);
	if (!dir)
		return (closedir(dir_ptr), 0);
			
}
