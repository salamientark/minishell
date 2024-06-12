/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 02:33:33 by madlab            #+#    #+#             */
/*   Updated: 2024/06/12 15:02:06 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/* Print error message when a wrong expansion occur
 * */
static int	expand_error(const char *word)
{
	int	index;

	index = 2;
	if (word[index] && (word[index] == RIGHT_BRACE || ft_isdigit(word[index])))
		return (print_error((char *)word, "bad substitution"), 1);
	while (word[index] && word[index] != RIGHT_BRACE)
	{
		if (word[index] == SINGLE_QUOTE || word[index] == DOUBLE_QUOTE
			|| can_be_operator(word[index] || word[index] == LEFT_PARENTHESIS
				|| word[index] == RIGHT_PARENTHESIS || word[index] == LEFT_BRACE
				|| word[index] == ASTERISK))
			return (print_error((char *)word, "bad substitution"), 1);
		if (!ft_isalnum(word[index]) && word[index] != UNDERSCORE)
			break ;
		index++;
	}
	return (0);
}

/* get the key len of env variable based on the word given as input.
 * to_expand = $[something]
 * */
static int	get_key_len(const char *to_expand)
{
	int	len;

	len = 0;
	if (to_expand[len] == '?')
		return (1);
	while (to_expand[len] && (ft_isalnum(to_expand[len])
			|| to_expand[len] == UNDERSCORE))
		len++;
	return (len);
}

/* Return the env value when found. If not found return an empty string that
 * can be freed (whichi mean it have benn malloced)
 * */
static char	*get_env_val(const char *key, int key_len, char **env)
{
	int		index;
	int		val_len;
	char	*expand_result;

	index = 0;
	val_len = 0;
	while (env[index])
	{
		if (ft_strncmp(key, env[index], key_len) == 0
			&& env[index][key_len] && env[index][key_len] == EQUAL)
		{
			while (env[index][key_len + 1 + val_len])
				val_len++;
			break ;
		}
		index++;
	}
	expand_result = (char *)malloc(val_len + 1);
	if (!expand_result)
		return (print_error("malloc", strerror(errno)), NULL);
	expand_result[0] = '\0';
	if (val_len == 0)
		return (expand_result);
	expand_result = ft_strcpy(expand_result, &(env[index][key_len + 1]));
	return (expand_result);
}

char	*expand_variable(const char *to_expand, t_chill *shell)
{
	int		ref;
	int		key_len;
	char	*expand_result;

	ref = 1;
	if (to_expand[ref] && to_expand[ref] == LEFT_BRACE)
	{
		ref++;
		if (expand_error(to_expand))
			return (NULL);
		key_len = get_key_len(to_expand + ref);
	}
	else
		key_len = get_key_len(to_expand + ref);
	if (key_len == 1 && to_expand[ref] == '?')
		expand_result = ft_itoa(shell->exit_status);
	else
		expand_result = get_env_val(to_expand + ref, key_len, shell->env);
	if (!expand_result)
		return (NULL);
	return (expand_result);
}
