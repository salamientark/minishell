/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:53:28 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/28 07:16:24 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

// Read one text_block and put the result into block->content
// On ERROR or NULL reading (read 0 char)
// free the allocated block
//	Return :
//		[0;BUFFER_SIZE]	: number of char read from file
//			-1			: ERROR
static ssize_t	read_block(const int fd, t_block **block)
{
	int	content_len;

	if (!(*block))
		*block = init_block();
	content_len = read(fd, (*block)->content + (*block)->content_len,
			BUFFER_SIZE - (*block)->content_len) + (*block)->content_len;
	if (content_len <= 0)
	{
		if ((*block)->content)
		{
			free((*block)->content);
			(*block)->content = NULL;
		}
		free((*block));
		(*block) = NULL;
		return (content_len);
	}
	(*block)->content_len = content_len;
	while ((*block)->last_pos < content_len
		&& (*block)->content[(*block)->last_pos] != '\n')
		(*block)->last_pos = (*block)->last_pos + 1;
	if ((*block)->last_pos < (*block)->content_len
		&& (*block)->content[(*block)->last_pos] == '\n')
		return ((*block)->last_pos + 1);
	return ((*block)->last_pos);
}

// Read one line from file store the result as a chained list
// Don't free on error
//	Return :
//		[0;∞[	: number of char in line
//		-1	: ERROR
static ssize_t	read_line(const int fd, t_block **head)
{
	t_block	*tmp_block;
	int		line_len;
	int		read_result;

	line_len = read_block(fd, head);
	if (line_len <= 0)
		return (line_len);
	while ((*head)->last_pos == BUFFER_SIZE)
	{
		tmp_block = init_block();
		read_result = read_block(fd, &tmp_block);
		if (read_result > 0)
		{
			line_len += read_result;
			tmp_block->next = *head;
			*head = tmp_block;
		}
		else if (read_result == -1)
			return (-1);
		else
			return (line_len);
	}
	return (line_len);
}

// Convert chained list (head) to line of len (line_len)a
//	Return :
//		(char *)	: New_line made
//		NULL		: ERROR or no line to make
static char	*make_line(ssize_t line_len, t_block *head)
{
	char	*line;
	ssize_t	buff_index;
	t_block	*record;

	record = head;
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	if (record->content_len == 0)
		record = record->next;
	line[line_len] = '\0';
	buff_index = record->last_pos;
	if (buff_index == record->content_len)
		buff_index--;
	while (line_len-- > 0)
	{
		line[line_len] = record->content[buff_index];
		if (buff_index == 0 && line_len > 0)
		{
			record = record->next;
			buff_index = BUFFER_SIZE;
		}
		buff_index--;
	}
	return (line);
}

// Move block->buffer_content at the beginning of it
// after a line was read
//		Return :
//			void
void	content_move(t_block **block)
{
	int	index;

	index = 0;
	(*block)->last_pos = (*block)->last_pos + 1;
	while (index < ((*block)->content_len - (*block)->last_pos)
		&& (*block)->content[(*block)->last_pos + index] != '\0')
	{
		(*block)->content[index] = (*block)->content[(*block)->last_pos
			+ index];
		index++;
	}
	(*block)->content_len = index;
	(*block)->last_pos = 0;
	while ((*block)->last_pos < (*block)->content_len
		&& (*block)->content[(*block)->last_pos] != '\n')
		(*block)->last_pos = (*block)->last_pos + 1;
}

// Read a line from fd
//	Return :
//		char *  : New_line
//		NULL	: Error or No more line
char	*get_next_line(const int fd)
{
	static t_block	*head;
	ssize_t			line_len;
	char			*line;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	line_len = read_line(fd, &head);
	if (line_len <= 0)
		return (free_block(&head), NULL);
	line = make_line(line_len, head);
	content_move(&head);
	if (!line || head->content_len == 0)
		free_block(&head);
	else
	{
		free_block(&(head->next));
		head->next = NULL;
	}
	return (line);
}
