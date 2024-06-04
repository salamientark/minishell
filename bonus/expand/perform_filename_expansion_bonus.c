/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_filename_expansion_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 00:06:55 by madlab            #+#    #+#             */
/*   Updated: 2024/06/04 12:38:08 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander_bonus.h"
#include "../includes/minishell_bonus.h"

/* Return 1 if the elem->word contain an unquoted *
 * */
static int	contain_filename_expansion(t_expand *elem)
{
	int	index;

	index = 0;
	while (elem->word[index])
	{
		if (elem->quote[index] == 1)
		{
			index++;
			while (elem->quote[index] != 1)
				index++;
			index++;
		}
		else if (elem->word[index] == '*')
			return (1);
		else
			index++;
	}
	return (0);
}

/* Add a new t_expand *element duplicating the char *str
 *  and reallocating the tab in consequence
 * */
static t_expand	**add_back(t_expand **tab, char *str)
{
	char		*str_clone;
	t_expand	*new_elem;
	t_expand	**new_tab;
	size_t		tab_len;

	str_clone = ft_strdup(str);
	if (!str_clone)
		return (print_error("ft_strdup", strerror(errno)),
				free_expand_tab(&tab), NULL);
	new_elem = make_expand_elem(str_clone);
	if (!new_elem)
		return (free_expand_tab(&tab), free(str_clone), NULL);
	ft_memset(new_elem->quote, 0, sizeof(int) * new_elem->size);
	tab_len = 0;
	while (tab[tab_len])
		tab_len++;
	new_tab = (t_expand **)malloc(sizeof(t_expand *) * tab_len + 2);
	if (!new_tab)
		return (print_error("malloc", strerror(errno)),
			free_expand_tab(&tab), free_expand_elem(&new_elem), NULL);
	new_tab[tab_len + 1] = NULL;
	new_tab[tab_len] = new_elem;
	while (tab_len-- > 0)
		new_tab[tab_len] = tab[tab_len];
	return (free(tab), new_tab);
}

/* return a t_expand_tab of every matching entry
 * */
static t_expand **get_matching_entry(char *pattern, DIR *dir_p)
{
	struct dirent	*entry;
	t_expand		**result;

	result = (t_expand **)malloc(sizeof(t_expand *));
	if (!result)
		return (print_error("malloc", strerror(errno)), NULL);
	result[0] = NULL;
	entry = readdir(dir_p);
	while (entry && errno != 0)
	{
		if (pattern_match(pattern, entry->d_name))
		{
			result = add_back(result, entry->d_name);
			if (!result)
				return (free(pattern), NULL);
		}
		entry = readdir(dir_p);
	}
	if (errno != 0)
		return (print_error("readir", strerror(errno)),
				free_expand_tab(&result), NULL);
	return (result);
}

/* Perform filename expansion on single element
 * */
static t_expand	**expand_filename(t_expand **tab, char *cwd, int *index,
	int cmd_flag)
{
	char			*pattern;
	DIR				*dir_p;
	t_expand		**expand_result;
	t_expand		**final_tab;

	pattern = simplify_pattern(tab[*index]);
	if (!pattern)
		return (NULL);
	dir_p = opendir(cwd);
	if (!dir_p)
		return (print_error("opendir", strerror(errno)), free(pattern), NULL);
	expand_result = get_matching_entry(pattern, dir_p);
	if (!expand_result)
		return (closedir(dir_p), NULL);
	if (expand_result[0] && expand_result[1] && cmd_flag == 0)
		return (print_error(tab[*index]->word, AMBIGUOUS_REDIRECT),
			free(pattern), free_expand_tab(&expand_result),
				free_expand_tab(&tab), closedir(dir_p), NULL);
	if (expand_result[0] == NULL)
		return (closedir(dir_p), free(expand_result), tab);
	final_tab = expand_replace(tab, expand_result, index);
	if (!final_tab)
		return (closedir(dir_p), NULL);
	return (closedir(dir_p), final_tab);
}

/* perform filename expansion (wildcard * matching) on every element
 *  of the t_expand_tab array
 * It will modify the expand tab directly, that's why the char ^^^
 * THe cmd_flag indicates if the expand is erformed on cmd OR redirection
 *  part of the t_expand element. It will raise an error if file expansion
 *  match multiple file in the redirection part
 * The perform_filename_expansion() return 0 on sucess else return 1
 * */
int	perform_filename_expansion(t_expand ***expand_tab, int cmd_flag)
{
	char		cwd[MAX_PATHLEN];
	int			index;

	if (getcwd(cwd, MAX_PATHLEN))
		return (print_error("getcwd", strerror(errno)), 1);
	index = 0;
	while (expand_tab[index])
	{
		if (contain_filename_expansion((*expand_tab)[index]))
		{
			(*expand_tab) = expand_filename(*expand_tab, cwd, &index,
				cmd_flag);
			if (!(*expand_tab))
				return (1);
		}
		index++;
	}
	return (0);
}
