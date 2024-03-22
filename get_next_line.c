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
	char	buf[BUFFER_SIZE + 1];

	size = read(fd, buf, BUFFER_SIZE);
	if (size < 0)
		return (0);
	buf[size] = '\0';
	return (ft_strdup(buf, 0));
}

char	*update_backup(char *backup, char *chridx)
{
	free(backup);
	return (ft_strdup(chridx, 0));
}

char	*merge_line(int fd, char **backup)
{
	char	*buf;
	char	*merge;
	char	*chridx;
	size_t	idx;

	merge = ft_strdup(*backup, 0);
	while (1)
	{
		idx = 0;
		buf = read_buff_size(fd);
		merge = ft_strjoin(merge, buf);
		if (!merge)
			return (0);
		chridx = ft_get_chridx(merge, '\n', &idx);
		if (chridx)
			break ;
		if (buf[0] == '\0')
		{
			idx = ft_strlen(merge) - 1;
			*backup = ft_strdup("", 0);
			break ;
		}
	}
	if (chridx)
		*backup = update_backup(*backup, chridx + 1);
	buf = ft_strdup(merge, idx + 1);
	free(merge);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;	

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (0);
	if (backup && *backup == '\0')
	{
		free(backup);
		return (0);
	}
	line = merge_line(fd, &backup);
	return (line);
}

// #include <stdio.h>
// # include <fcntl.h>

// int main(){
// 	int fd = open("./test.txt", O_RDONLY);

// 	while (1){
// 		char *line = get_next_line(fd);
// 		if (!line)
// 			break;
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// }
