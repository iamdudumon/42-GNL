/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:34:19 by dukim             #+#    #+#             */
/*   Updated: 2024/07/02 13:53:02 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_chridx(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2, char end)
{
	char	*join_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	if (!s1)
		s1 = "";
	s1_len = (size_t)(ft_get_chridx(s1, '\0') - s1);
	s2_len = (size_t)(ft_get_chridx(s2, end) - s2);
	if (end == '\n')
		s2_len++;
	join_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!join_str)
		return (0);
	i = -1;
	while (++i < s1_len)
		join_str[i] = s1[i];
	while (++i - 1 < s1_len + s2_len)
		join_str[i - 1] = s2[i - 1 - s1_len];
	join_str[s1_len + s2_len] = '\0';
	return (join_str);
}

void	ft_lstadd_back(t_list **list, t_list *new)
{
	t_list	*tail;

	if (!(*list))
	{
		*list = new;
		tail = *list;
		return ;
	}
	if (!list || !new)
		return ;
	tail = *list;
	while (tail->next)
		tail = tail->next;
	tail->next = new;
	tail->next->prev = tail;
	tail = tail->next;
}

t_list	*ft_lstnew(int fd)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list) * 1);
	if (!node)
		return (0);
	node->fd = fd;
	node->backup = 0;
	node->next = 0;
	node->prev = 0;
	return (node);
}

void	del_node(t_list **list, t_list *node)
{
	if (!(node->prev) && !(node->next))
	{
		free((node)->backup);
		free(node);
		*list = 0;
		return ;
	}
	if (!(node->next))
		node->prev->next = 0;
	if (!(node->prev))
	{
		node->next->prev = 0;
		*list = node->next;
	}
	if ((node->prev) && (node->next))
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	free(node->backup);
	free(node);
}
