/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:40:05 by madlab            #+#    #+#             */
/*   Updated: 2024/06/02 22:31:43 by madlab           ###   ########.fr       */
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

#include "parser.h"

int	is_followed_by_word(const char *cmd, int operator)
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

static	int	is_followed_by_newline(const char *cmd)
{
	int	index;

	index = 1;
	if (!cmd[index])
		return (1);
	while (cmd[index] && (cmd[index] == SPACE || cmd[index] == TAB))
		index++;
	if (!cmd[index] || (cmd[index] && cmd[index] == NEWLINE))
		return (1);
	return (0);
}

/*
 * */
static int	analyze_operator_syntax(const char *str, int ref, int *here_doc_count)
{
	char	operator;

	operator = get_operator(str + ref);
	if (operator == PIPE || operator == AND || operator == OR)
	{
		if (!is_preceeded_by_word(str, ref))
			return (print_syntax_error(str, ref, operator), 2);
		if (operator == PIPE && is_followed_by_newline(str + ref))
			return (print_error("analyze_operator_syntax",
					"nothing aftert pipe"), 1);
	}
	if (operator == LESS_THAN || operator == GREATER_THAN
		|| operator == APPEND || operator == HERE_DOC)
	{
		if (!is_followed_by_word(str + ref, operator))
			return (print_syntax_error(str, ref, operator), 2);
		if (operator == HERE_DOC)
			return (here_doc(str, ref, here_doc_count));
	}
	return (0);
}

/* First pass check for syntax error and open every necessary Here_doc
 **/
int	syntax_error(const char *cmd)
{
	int	i;
	int	analyzed_op;
	int	here_doc_count;

	if (!cmd)
		return (0);
	i = 0;
	here_doc_count = 0;
	while (cmd[i])
	{
		if (can_be_operator(cmd[i]))
		{
			analyzed_op = analyze_operator_syntax(cmd, i, &here_doc_count);
			if (analyzed_op != 0)
				return (analyzed_op);
			i += 1 + (cmd[i + 1] && cmd[i] == cmd[i + 1]);
		}
		else if (cmd[i] == SINGLE_QUOTE || cmd[i] == DOUBLE_QUOTE)
			i += quoted_strlen(cmd, i, cmd[i]);
		else if (cmd[i] == DOLLAR && cmd[i + 1] && cmd[i + 1] == LEFT_BRACE)
			i += expand_strlen(cmd, i, 0);
		else
			i++;
	}
	return (0);
}
