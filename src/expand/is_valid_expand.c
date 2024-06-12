/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:35:49 by madlab            #+#    #+#             */
/*   Updated: 2024/06/12 21:58:50 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

/* Print the Bad substitution error on variable expansion
 * */
static void	print_expansion_error(const char *str)
{
	printf("minishell: %s : bad substitution\n", str);
}

/* Check if the expansion starting with ? don't have substitution error
 * */
static int	valid_brace_exit_status(const char *str, int *ref)
{
	while (str[*ref])
	{
		if (str[*ref] == '}')
			return (1);
		if (str[*ref] != '?')
			return (print_expansion_error(str), 0);
		*ref += 1;
	}
	return (0);
}

/* Check if the digit starting expansion don't have substitution error
 * */
static int	valid_brace_digit(const char *str, int *ref)
{
	while (str[*ref])
	{
		if (str[*ref] == '}')
			return (0);
		if (!ft_isdigit(str[*ref]))
			return (print_expansion_error(str), 0);
		*ref += 1;
	}
	return (0);
}

/* Check if the alphanum/_ starting expansion don't have substitution error
 * */
static int	valid_brace_alnum(const char *str, int *ref)
{
	while (str[*ref])
	{
		if (str[*ref] == '}')
			return (1);
		if (!(ft_isalnum(str[*ref] || str[*ref] == UNDERSCORE)))
			return (print_expansion_error(str), 0);
		*ref += 1;
	}
	return (0);
}

/* Check if paramter in brace is valid substitution
 * */
int	is_valid_expand(const char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == DOLLAR && str[index + 1] && str[index + 1] == '{')
		{
			index += 2;
			if (str[index] == '?' && !valid_brace_exit_status(str, &index))
				return (0);
			else if (ft_isdigit(str[index]) && !valid_brace_digit(str, &index))
				return (0);
			else
			{
				if (!valid_brace_alnum(str, &index))
					return (0);
			}
		}
		else
			index++;
	}
	return (1);
}
