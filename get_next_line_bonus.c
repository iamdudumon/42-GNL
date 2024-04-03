/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:17:14 by dukim             #+#    #+#             */
/*   Updated: 2024/03/15 20:15:45 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_buff_size(int fd)
{
	ssize_t	size;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	size = read(fd, buf, BUFFER_SIZE);
	if (size == -1)
	{
		free(buf);
		return (0);
	}
	buf[size] = '\0';
	return (buf);
}

void	delete_backup_node(t_list **backup_list, t_list *target)
{
	t_list	*ptr;

	if (*backup_list == target)
	{
		*backup_list = target->next;
		free(target->backup);
		free(target);
		return ;
	}
	ptr = *backup_list;
	while (ptr->next->fd != target->fd && ptr->next->next != 0)
		ptr = ptr->next;
	ptr->next = target->next;
	free(target->backup);
	free(target);
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

	buf = read_buff_size(fd);
	if (!buf)
		return (0);
	ptr = backup_list;
	while (ptr->fd != fd && ptr->next != 0)
		ptr = ptr->next;
	if (ptr->fd == fd)
	{	
		ptr->backup = ft_strjoin(ptr->backup, buf);
		if (!(ptr->backup))
			return (0);
		return (ptr);
	}
	if (*buf == '\0')
	{
		free(buf);
		return (0);
	}
	ptr->next = lstnew(fd, buf);
	return (ptr->next);
}

char	*merge_line(int fd, char **backup)
{
	char	*merge;
	char	*chridx;
	char	*buf;

	merge = ft_strdup(*backup);
	chridx = ft_get_chridx(merge, '\n');
	while (!chridx)
	{
		buf = read_buff_size(fd);
		if (buf && *buf == '\0')
		{
			free(buf);
			break ;
		}
		merge = ft_strjoin(merge, buf);
		if (!merge)
			return (0);
		chridx = ft_get_chridx(merge, '\n');
	}
	if (chridx)
		chridx += 1;
	free(*backup);
	*backup = ft_strdup(chridx);
	return (merge);
}

char	*get_next_line(int fd)
{
	static t_list	*backup_list;
	t_list			*node;
	char			*newline;
	char			*merge;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!backup_list)
	{
		merge = read_buff_size(fd);
		if (merge && *merge == '\0')
		{
			free(merge);
			return (0);
		}
		backup_list = lstnew(fd, merge);
		if (!backup_list)
			return (0);
	}
	node = find_backup_node(backup_list, fd);
	if (!node)
		return (0);
	merge = merge_line(node->fd, &(node->backup));
	newline = ft_get_sub_newline(merge, !(node->backup));
	if (!newline || !(node->backup))
		delete_backup_node(&backup_list, node);
	return (newline);
}

// #include <stdio.h>
// #include <fcntl.h>

// int main(){
// 	int fd1 = open("./42_with_nl", O_RDONLY);
// 	int fd2 = open("./42_with_nl", O_RDONLY);
// 	int fd3 = open("./42_with_nl", O_RDONLY);
// 	int i = 0;

// 	while (1){
// 		char *line1= get_next_line(fd1);
// 		char *line2 = get_next_line(fd2);
// 		char *line3 = get_next_line(fd3);

// 		if (line1)
// 			printf("line1->%d: %s", i, line1);
// 		else
// 			printf("line1->%d: null\n", i);
// 		if (line2)
// 			printf("line2->%d: %s", i, line2);
// 		else
// 			printf("line2->%d: null\n", i);
// 		if (line3)
// 			printf("line3->%d: %s", i, line3);
// 		else
// 			printf("line3->%d: null\n", i);
// 		free(line1);
// 		free(line2);
// 		free(line3);
// 		i++;
// 		if (!line1 && !line2 && !line3)//  
// 			break;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// }

// int main(){
// 	int fd1 = open("./42_with_nl", O_RDONLY);
// 	int i = 0;

// 	while (1){
// 		char *line1= get_next_line(fd1);

// 		if (!line1)
// 			break;
// 		printf("line1->%d: %s", i, line1);
// 		free(line1);
// 		i++;
// 	}
// 	close(fd1);
// }
