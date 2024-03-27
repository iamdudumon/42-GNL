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

char	*read_buff_size(int fd)
{
	ssize_t	size;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	size = read(fd, buf, BUFFER_SIZE);
	if (size < 0)
		return (0);
	buf[size] = '\0';
	return (buf);
}

char	*get_sub_newline(char *s)
{
	char	*newline;
	size_t	s_len;
	size_t	len;

	if (!s)
		return (0);
	s_len = (size_t)(ft_get_chridx(s, '\n') - s);
	newline = (char *)malloc(sizeof(char) * (s_len + 2));
	if (!newline)
		return (0);
	len = 0;
	while (len < s_len + 1)
	{
		newline[len] = s[len];
		len++;
	}
	newline[len] = '\0';
	free(s);
	return (newline);
}

char	*merge_line(int fd, char **backup, char **buf)
{
	char	*merge;
	char	*chridx;

	merge = *backup;
	chridx = ft_get_chridx(merge, '\n');
	while (!chridx)
	{
		*buf = read_buff_size(fd);
		if (!(*buf) || (**buf == '\0' && *merge == '\0'))
			return (0);
		if (**buf == '\0')
			break ;
		merge = ft_strjoin(merge, *buf);
		if (!merge)
			return (0);
		chridx = ft_get_chridx(merge, '\n');
	}
	if (chridx)
		chridx += 1;
	*backup = ft_strdup(chridx);
	if (**backup == '\0')
		return (merge);
	return (get_sub_newline(merge));
}

char	*get_next_line(int fd)
{
	static t_list	*backup_list;
	t_list			*node;
	char			*line;
	char			*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!backup_list)
	{
		backup_list = lstnew(fd, ft_strdup(""));
		if (!backup_list)
			return (0);
	}
	node = find_backup_node(backup_list, fd);
	if (!node)
		return (0);
	line = merge_line(node->fd, &(node->backup), &buf);
	if (!line)
	{
		delete_backup_node(&backup_list, node);
		free(buf);
		return (0);
	}
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>

// int main(){
// 	int fd1 = open("./test1.txt", O_RDONLY);
// 	int fd2 = open("./test2.txt", O_RDONLY);
// 	int fd3 = open("./test3.txt", O_RDONLY);
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
