/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/builtin/cd.c
/*   Created: 2024/05/14 16:57:47 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/15 02:38:09 by ple-guya         ###   ########.fr       */
=======
/*   Created: 2024/05/14 14:11:17 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/14 18:39:44 by dbaladro         ###   ########.fr       */
>>>>>>> 599a31318144e29422d224a5ca7da297662e50b3:includes/test.h
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

<<<<<<< HEAD:src/builtin/cd.c
static void	change_old_pwd()
{
	
}

static void	change_pwd()
{
	
}

void	cd(char *dir, char **env)
{
	char	*home;
	char	*oldpwd;
	char	pwd[100];
	(void)env;
	oldpwd = getenv("OLDPWD");
	if (!dir)
	{
		home = getenv("HOME");
		if (chdir(home))
			perror("cd");
		return ;
	}
	if (!ft_strcmp(dir, "-"))
	{
		if(chdir(oldpwd))
			perror("cd");
		printf(oldpwd);
	}
	
}
=======
# include <stdio.h>

// test_lexer.h
void	print_input(char **input_tab);

#endif
>>>>>>> 599a31318144e29422d224a5ca7da297662e50b3:includes/test.h
