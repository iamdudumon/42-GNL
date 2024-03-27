/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:17:14 by dukim             #+#    #+#             */
/*   Updated: 2024/03/15 20:15:45 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*find_backup(t_list *backup_list, int fd)
{
	t_list	*ptr;

	ptr = backup_list;
	while (ptr->fd == fd && ptr->next != 0)
		ptr = ptr->next;
	if (ptr->fd == fd)
		return (ptr);
	ptr->next = (t_list *)malloc(sizeof(t_list) * 1);
	if (!(ptr->next))
		return (0);
	ptr->next->fd = fd;
	ptr->next->backup = ft_strdup("");
	if (!(ptr->next->backup))
		return (0);
	ptr->next->next = 0;
	return (ptr->next);
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

	if (!s)
		return (0);
	s_len = (size_t)(ft_get_chridx(s, '\n') - s);
	newline = (char *)malloc(sizeof(char) * (s_len + 2));
	if (!newline)
		return (0);
	newline[0] = '\0';
	ft_strlcat(newline, s, s_len + 2);
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
	*backup = ft_strdup(chridx + 1);
	if (**backup == '\0')
		return (merge);
	return (get_sub_newline(merge));
}

char	*get_next_line(int fd)
{
	static t_list	*backup_list;
	t_list			*backup;
	char			*line;
	char			*buf;	

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (0);
	if (!backup_list)
	{
		backup_list = (t_list *)malloc(sizeof(t_list) * 1);
		if (!backup_list)
			return (0);
		backup_list->fd = fd;
		backup_list->backup = ft_strdup("");
		if (!(backup_list->backup))
			return (0);
		backup_list->next = 0;
	}
	backup = find_backup(backup_list, fd);
	line = merge_line(backup->fd, &(backup->backup), &buf);
	if (!line)
	{
		free(backup);
		free(buf);
		return (0);
	}
	return (line);
}
#include <stdio.h>
#include <fcntl.h>

int main(){
	int fd1 = open("./test1.txt", O_RDONLY);
	int fd2 = open("./test2.txt", O_RDONLY);
	int i = 0;

	while (1){
		char *line1= get_next_line(fd1);
		char *line2 = get_next_line(fd2);

		if (line1)
			printf("line1->%d: %s", i, line1);
		else
			printf("line1->%d: null\n", i);
		if (line2)
			printf("line2->%d: %s", i, line2);
		else
			printf("line2->%d: null\n", i);
		free(line1);
		free(line2);
		i++;
		if (!line1 && !line2)
			break;
	}
	close(fd1);
	close(fd2);
}
