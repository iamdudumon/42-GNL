/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:55:19 by dukim             #+#    #+#             */
/*   Updated: 2024/03/15 20:02:39 by dukim            ###   ########.fr       */
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

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	s_len;
	size_t	len;

	if (!s)
		return (ft_strdup(""));
	s_len = (size_t)(ft_get_chridx(s, '\0') - s);
	dup = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!dup)
		return (0);
	len = 0;
	while (len < s_len)
	{
		dup[len] = s[len];
		len++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	len;

	s1_len = (size_t)(ft_get_chridx(s1, '\0') - s1);
	s2_len = (size_t)(ft_get_chridx(s2, '\0') - s2);
	join_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!join_str)
		return (0);
	len = 0;
	while (len < s1_len)
	{
		join_str[len] = s1[len];
		len++;
	}
	while (len < s1_len + s2_len)
	{
		join_str[len] = s2[len - s1_len];
		len++;
	}
	join_str[len] = '\0';
	free(s1);
	free(s2);
	return (join_str);
}

t_list	*lstnew(int fd, char *backup)
{
	t_list	*node;

	if (!backup)
		return (0);
	node = (t_list *)malloc(sizeof(t_list) * 1);
	if (!node)
	{
		free(backup);
		return (0);
	}
	node->fd = fd;
	node->backup = backup;
	node->next = 0;
	return (node);
}

t_list	*find_backup_node(t_list *backup_list, int fd)
{
	t_list	*ptr;
	char	*buf;

	ptr = backup_list;
	while (ptr->fd != fd && ptr->next != 0)
		ptr = ptr->next;
	if (ptr->fd == fd)
		return (ptr);
	buf = (char *)malloc(sizeof(char) * 2);
	if (!buf || read(fd, buf, 1) <= 0)
	{
		free(buf);
		return (0);
	}
	buf[1] = '\0';
	ptr->next = lstnew(fd, buf);
	return (ptr->next);
}
