/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:34:12 by dukim             #+#    #+#             */
/*   Updated: 2024/07/02 13:52:50 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_buffer(t_list	*node)
{
	char	*buf;
	char	*res;
	ssize_t	size;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	size = read(node->fd, buf, BUFFER_SIZE);
	buf[size] = '\0';
	res = ft_strjoin(node->backup, buf, '\0');
	free(node->backup);
	free(buf);
	if (!ft_get_chridx(res, '\n'))
	{
		if (size == 0)
		{
			node->backup = 0;
			return (res);
		}
		node->backup = res;
		return (0);
	}
	buf = ft_strjoin("", res, '\n');
	node->backup = ft_strjoin(ft_get_chridx(res, '\n') + 1, "", '\0');
	free(res);
	return (buf);
}

static char	*get_one_line(t_list *node)
{
	char	*buf;

	buf = read_buffer(node);
	while (!buf)
		buf = read_buffer(node);
	if (*buf == '\0' && !(node->backup))
	{
		free(buf);
		return (0);
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*node;
	char			*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	node = list;
	while (node)
	{
		if (node->fd == fd)
			break ;
		node = node->next;
	}
	if (!node)
	{
		node = ft_lstnew(fd);
		ft_lstadd_back(&list, node);
	}
	res = get_one_line(node);
	if (!res)
		del_node(&list, node);
	return (res);
}
