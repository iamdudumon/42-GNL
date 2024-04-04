/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:17:14 by dukim             #+#    #+#             */
/*   Updated: 2024/04/04 19:02:39 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*is_readable_fd(int fd, char *backup)
{
	char	*temp;
	char	*buf;

	buf = read_buff_size(fd);
	temp = ft_strjoin(backup, buf);
	if (!temp)
		return (0);
	if (*temp == '\0')
	{
		free(temp);
		return (0);
	}
	return (temp);
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
	static char	*backup_list[4096];
	char		*backup;
	char		*merge;
	char		*newline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	backup = backup_list[fd];
	if (!backup)
	{
		backup = ft_strdup("");
		if (!backup)
			return (0);
	}
	backup = is_readable_fd(fd, backup);
	if (!backup)
		return (0);
	merge = merge_line(fd, &backup);
	newline = ft_get_sub_newline(merge, !backup);
	backup_list[fd] = backup;
	if (!newline)
		free(backup);
	return (newline);
}

#include <stdio.h>
#include <fcntl.h>

int main(){
	int fd1 = open("files/test1.txt", O_RDONLY);
	int fd2 = open("files/test2.txt", O_RDONLY);
	int fd3 = open("files/test3.txt", O_RDONLY);
	int i = 0;

	while (1){
		char *line1= get_next_line(fd1);
		char *line2 = get_next_line(fd2);
		char *line3 = get_next_line(fd3);

		if (line1)
			printf("line1->%d: %s", i, line1);
		else
			printf("line1->%d: null\n", i);
		if (line2)
			printf("line2->%d: %s", i, line2);
		else
			printf("line2->%d: null\n", i);
		if (line3)
			printf("line3->%d: %s", i, line3);
		else
			printf("line3->%d: null\n", i);
		free(line1);
		free(line2);
		free(line3);
		i++;
		if (!line1 && !line2 && !line3)//  
			break;
	}
	close(fd1);
	close(fd2);
	close(fd3);
}
