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
#include <stdio.h>
char	*read_buff_size(int fd)
{
	ssize_t	size;
	char	buf[BUFFER_SIZE + 1];

	size = read(fd, buf, BUFFER_SIZE);
	if (size < 0)
		return (0);
	buf[size] = '\0';
	return (ft_strdup(buf));
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

char	*merge_line(int fd, char **backup)
{
	char	*merge;
	char	*buf;
	char	*chridx;

	merge = *backup;
	while (1)
	{
		chridx = ft_get_chridx(merge, '\n');
		if (chridx)
			break ;
		buf = read_buff_size(fd);
		if (!buf || (*buf == '\0' && *merge == '\0'))
		{
			free(buf);
			return (0);
		}
		if (*buf == '\0')
		{
			*backup = ft_strdup("");
			free(buf);
			return (merge);
		}
		merge = ft_strjoin(merge, buf);
		if (!merge)
			return (0);
	}
	*backup = ft_strdup(chridx + 1);
	return (get_sub_newline(merge));
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;	

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (0);
	if (!backup)
	{
		backup = ft_strdup("");
		if (!backup)
			return (0);
	}
	line = merge_line(fd, &backup);
	if (!line)
	{
		free(backup);
		return (0);
	}
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>

// int main(){
// 	int fd = open("./test.txt", O_RDONLY);
// 	int i = 0;
// 	char *line;
// 	while (1){
// 		line = get_next_line(fd);
// 		if (!line)
// 			break;
// 		printf("%d: %s", i++, line);
// 		free(line);
// 	}
// 	close(fd);
// }
