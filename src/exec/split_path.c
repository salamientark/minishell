/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:39:10 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/06 14:09:33 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all(char ***split_path_ptr, unsigned int size)
{
	while (size > 0 || (*split_path_ptr)[size] != NULL)
	{
		free(*(split_path_ptr[size]));
		*(split_path_ptr[size--]) = 0;
	}
	free(*split_path_ptr);
	*split_path_ptr = 0;
}

/*
	count PATH entrys from environment PATH variable
*/
static unsigned int	count_path(const char *path)
{
	int			word_count;
	int			new_word;
	const char	*path_p;

	path_p = path;
	word_count = 0;
	new_word = 1;
	while (*path_p)
	{
		if (*path_p != ':')
		{
			if (new_word == 1)
				word_count++;
			new_word = 0;
		}
		else
			new_word = 1;
		path_p++;
	}
	return (word_count);
}

/*
	Malloc and extract one path from the PATH variable (extracted from env)
*/
static char	*extract_path(char **path)
{
	int		i;
	int		size;
	char	*word;

	while (**path == ':')
		(*path)++;
	i = 0;
	while ((*path)[i] && (*path)[i] != ':')
		i++;
	if (i == 0)
		return (NULL);
	word = (char *)malloc(i + 2);
	if (!word)
		return (NULL);
	size = i;
	i = 0;
	while (i < size)
	{
		word[i] = (*path)[i];
		i++;
	}
	word[i++] = '/';
	word[i] = '\0';
	*path += size;
	return (word);
}

/*
	Get the PATH vaiable from env
	Return NULL if not found
*/
static char	*find_path_in_env(char **env)
{
	int	index;

	index = 0;
	while (env[index] && ft_strncmp(env[index], "PATH=", 5) != 0)
		index++;
	if (!env[index])
	{
		print_error("minishell: ", "No PATH");
		return ((char *) NULL);
	}
	return (env[index] + 5);
}

/*
	split the PATH variable from env
*/
char	**split_path(char **env)
{
	char			**splited_path;
	char			*env_path;
	unsigned int	path_nbr;
	unsigned int	i;

	if (!env)
		return (print_error("get_path: ", "No ENV"), (char **) NULL);
	env_path = find_path_in_env(env);
	if (!env_path)
		return ((char **) NULL);
	path_nbr = count_path(env_path);
	splited_path = (char **)malloc(sizeof(char *) * (path_nbr + 1));
	if (!splited_path)
		return (print_error("get_path: ", strerror(errno)), (char **) NULL);
	i = 0;
	while (i < path_nbr)
	{
		splited_path[i] = extract_path(&env_path);
		if (!splited_path[i])
			return (free_all(&splited_path, i), print_error("make_path: ",
					strerror(errno)), (char **) NULL);
		i++;
	}
	splited_path[i] = NULL;
	return (splited_path);
}