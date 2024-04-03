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

	if (!backup)
	{
		backup = ft_strdup("");
		if (!backup)
			return (0);
	}
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
	static char	*backup;
	char		*merge;
	char		*newline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	backup = is_readable_fd(fd, backup);
	if (!backup)
		return (0);
	merge = merge_line(fd, &backup);
	newline = ft_get_sub_newline(merge, !backup);
	if (!newline || !backup)
		free(backup);
	return (newline);
}

#include <stdio.h>
#include <fcntl.h>

int main(){
	int fd = open("./42_with_nl", O_RDONLY);
	int i = 0;
	char *line;
	while (1){
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%d: %s", i++, line);
		free(line);
	}
	free(line);
	close(fd);
}