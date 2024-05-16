/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:40:05 by madlab            #+#    #+#             */
/*   Updated: 2024/05/16 17:44:16 by dbaladro         ###   ########.fr       */
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

#include "../../includes/minishell.h"

static int	can_be_operator(const char c)
{
	if (c == GREATER_THAN)
		return (1);
	if (c == LESS_THAN)
		return (1);
	if (c == AMPERSAND)
		return (1);
	if (c == PIPE)
		return (1);
	return (0);
}

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

static int	analyze_operator_syntax(const char *str, int ref, int stdin_fd)
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
			here_doc(str, ref, stdin_fd);
	}
	return (0);
}

/* First pass check for syntax error and open every necessary Here_doc
 **/
int	first_pass(const char *cmd)
{
	int	i;
	int	analyzed_op;
	int	original_stdin;

	if (!cmd)
		return (0);
	i = 0;
	original_stdin = dup(STDIN_FILENO);
	while (cmd[i])
	{
		if (can_be_operator(cmd[i]))
		{
			analyzed_op = analyze_operator_syntax(cmd, i, original_stdin);
			if (analyzed_op != 0)
				return (analyzed_op);
			i += 1 + (cmd[i + 1] && cmd[i] == cmd[i + 1]);
		}
		else if (cmd[i] == SINGLE_QUOTE || cmd[i] == DOUBLE_QUOTE)
			i += quoted_strlen(cmd, i, cmd[i]);
		else if (cmd[i] == DOLLAR && cmd[i + 1] && cmd[i + 1] == LEFT_BRACE)
			i += expand_strlen(cmd, i);
		else
		i++;
	}
	return (0);
}
