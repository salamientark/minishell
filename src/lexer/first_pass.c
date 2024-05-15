/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:40:05 by madlab            #+#    #+#             */
/*   Updated: 2024/05/15 15:40:14 by madlab           ###   ########.fr       */
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

int	is_preceeded_by_word(const char *cmd, int index)
{
	while (index >= 0 && (cmd[index] == SPACE || cmd[index] == TAB))
		index--;
	if (index == -1 || cmd[index] == '\n')
		return (1);
	if (!is_operator(cmd[index]))
		return (0);
	return (1);
}

int	is_followed_by_word(const char *cmd, int index)
{
	index++;
	while (cmd[index] && (cmd[index] == SPACE || cmd[index] == TAB))
		index++;
	if (!cmd[index] || cmd[index] == '\n')
		return (1);
	if (!is_operator(cmd[index]))
		return (0);
	return (1);
}

void	get_operator(const char *cmd, char buff[], int index)
{
	buff[0] = cmd[index];
	buff[1] = 0;
	buff[2] = 0;
	if (!(cmd[index] == LESS_THAN || cmd[index] == GREATER_THAN
				|| cmd[index] == PIPE || cmd[index] == AMPERSAND))
		return ;
	if (cmd[index + 1] && cmd[index + 1] == cmd[index])
		buff[1] = cmd[index + 1];
	return ;
}

/*
 * If operator == |, ||, &&, ) without previous (
 * Check if previous token is operator.
 * If yes -> Syntax error
 * 
 * If operator == <, <<, >, >>
 * Check if next token is operator
 * if yes return -> sytax error
 * 
 * ||, &&, (, | with nothing after should be detected before
 * (unclosed quote/brace pass)
 * */
int	first_pass(const char *cmd)
{
	int		index;
	char	last_quote;
	char	buffer[3];

	if (!cmd)
		return (0);
	index = 0;
	while (cmd[index])
	{
		if (is_operator(cmd[index]))
		{
			get_operator(cmd, buffer, index);
			if (is_control_operator(buffer[0]))
			{
				if (!(is_preceeded_by_word(cmd, index)))
					return (syntax_error(buffer), 1);
				index = index + 1 + (buffer[1] != 0);
			}
			else if (buffer[0] == LESS_THAN && buffer[0] == buffer[1])
			{
				// HERE_DOC
			}
			else
				// REDIRECTION_OPERATOR -> CCHECK NEXT WORD
			{
				index = index + (buffer[1] != 0);
				if (!(is_followed_by_word(cmd, index)))
					// ERROR
					return (syntax_error(buffer), 1);
				index = index + 1 + (buffer[1] != 0);
			}
			buffer[1] = 0;
		}
		if (cmd[index] == DOUBLE_QUOTE || cmd[index] == SINGLE_QUOTE)
		{
			last_quote = cmd[index++];
			while (cmd[index] != last_quote)
				index++;
			index++;
		}
		index++;
	}
	return (0);
}

/* 1 : |
 * 2 : ||
 * 3 : &&
 * 4 : <
 * 5 : >
 * 6 : >>
 * 7 : <<
 **/
int	get_operator(const char *s)
{
	int	operator;

	if (*s == PIPE && *(s + 1) && *(s + 1) == PIPE)
		operator = 2;
	else if (*s == PIPE)
		operator = PIPE;
	else if (*s == AMPERSAND && *(s + 1) && *(s + 1) == AMPERSAND)
		operator = 3;
	else if (*s == LESS_THAN && *(s + 1) && *(s + 1) == LESS_THAN)
		operator = 7;
	else if (*s == GREATER_THAN && *(s + 1) && *(s + 1) == GREATER_THAN)
		operator = 6;
	else if (*s == LESS_THAN)
		operator = 4;
	else if (*s == GREATER_THEN)
		operator == 5;
	else
		operator = 0;
	return (operator);
}

int	analyze_operator_syntax(const char *str)
{
	int	operator;

	operator = get_operator(str);
	if (operator > 0 || operator < 3)
	{
		if (!is_preceeded_by_word(str))
			return (syntax_error(str, operator), 2);
		

	}
}

/* First pass check for syntax error and opene every necessary Here_doc
 **/
int	first_pass(const char *cmd)
{
	int	index;
	int	operator;

	if (!cmd)
		return (0);
	index = 0;
	while (cmd[index])
	{
		if (is_operator(cmd[index]))
		{
			operator = get_operator;
			if (is_control_operator(operator))
			{
				if (!is_preceeded_by_word(cmd[index], operator));
					//ERROR
			}
			if (is_redirection_operator(operator))
			{
				if (!is_followed_by_word(cmd[index], operator));
				// ERROR
				if (operator == HERE_DOC)
					// HERE_DOC
			}
		}
		if (cmd[index] == SINGLE_QUOTE || cmd[index] == DOUBLE_QUOTE)
			index += skip_quote(cmd, index);
		if (cmd[index] == DOLLR && cmd[index + 1]
			&& cmd[index + 1] == LEFT_BRACE)
			index += skip_expand(cmd[index]);
		index++;
	}
}
