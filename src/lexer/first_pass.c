/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:40:05 by madlab            #+#    #+#             */
/*   Updated: 2024/05/16 17:09:33 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * THE FIRST PASS HAPPEN AFTER THE QUOTE/BRACE CHECK
 * IT'S THE 'syntax error' checker + here_doc executor:
 *	The syntax error happen if you try to pipe/redirect from/to nothing
 *	$ | ls					=> SYNTAX ERROR
 *	$ ls |					=> SYNTAX ERROR
 *	$ <						=> SYNTAX ERROR
 *	$ ls | cat <<			=> SYNTAX ERROR
 *	$ ls | cat << LIM | <	=> HERE_DOC then SYNTAX_ERROR
 * THe first pass will open here_doc and check for syntax error
 *	IN THE ORDER THEY APPEAR
 *	*/

#include "minishell.h"

static int	is_preceeded_by_word(const char *cmd, int ref)
{
	int	index;

	index = ref - 1;
	while (index >= 0 && (cmd[index] == SPACE || cmd[index] == TAB))
		index--;
	if (index == -1 || cmd[index] == '\n')
		return (0);
	if (cmd[index] == GREATER_THAN || cmd[index] == LESS_THAN
		|| cmd[index] == PIPE)
		return (0);
	if (index >= 1 && cmd[index] == AMPERSAND && cmd[index - 1] == AMPERSAND)
		return (0);
	return (1);
}

static int	is_followed_by_word(const char *cmd, int operator)
{
	int	index;

	index = 1;
	if (operator == HERE_DOC)
		operator = LESS_THAN;
	if (operator == APPEND)
		operator = GREATER_THAN;
	if (!cmd[index])
		return (0);
	if (cmd[index] && cmd[index] == operator)
		index++;
	while (cmd[index] && (cmd[index] == SPACE || cmd[index] == TAB))
		index++;
	if (!cmd[index] || cmd[index] == '\n')
		return (0);
	if (cmd[index] == GREATER_THAN || cmd[index] == LESS_THAN
		|| cmd[index] == PIPE)
		return (0);
	if (cmd[index] == AMPERSAND && cmd[index + 1] && cmd[index] == AMPERSAND)
		return (0);
	return (1);
}

static int	analyze_operator_syntax(const char *str, int ref)
{
	char	operator;

	operator = get_operator(str + ref);
	if (operator == PIPE || operator == AND || operator == OR)
	{
		if (!is_preceeded_by_word(str, ref))
			return (syntax_error(str, ref, operator), 2);
	}
	if (operator == LESS_THAN || operator == GREATER_THAN
		|| operator == APPEND || operator == HERE_DOC)
	{
		if (!is_followed_by_word(str + ref, operator))
			return (syntax_error(str, ref, operator), 2);
		if (operator == HERE_DOC)
			here_doc(str, ref);
	}
	return (0);
}

/* First pass check for syntax error and open every necessary Here_doc
 **/
int	first_pass(const char *cmd)
{
	int	index;
	int	analyzed_op;

	if (!cmd)
		return (0);
	index = 0;
	while (cmd[index])
	{
		if (cmd[index] == LESS_THAN || cmd[index] == GREATER_THAN
			|| cmd[index] == AMPERSAND || cmd[index] == PIPE)
		{
			analyzed_op = analyze_operator_syntax(cmd, index);
			if (analyzed_op != 0)
				return (analyzed_op);
			index += 1 + (cmd[index + 1] && cmd[index] == cmd[index + 1]);
		}
		else if (cmd[index] == SINGLE_QUOTE || cmd[index] == DOUBLE_QUOTE)
			index += quoted_strlen(cmd, index, cmd[index]);
		else if (cmd[index] == DOLLAR && cmd[index + 1]
			&& cmd[index + 1] == LEFT_BRACE)
			index += expand_strlen(cmd, index);
		else
			index++;
	}
	return (0);
}
