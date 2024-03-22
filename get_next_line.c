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

char	*get_next_line(int fd)
{
	size_t		size;
	size_t		buf_size;
	char		c;
	char		*buf;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	buf_size = BUFFER_SIZE;
	if (!buf)
		return (0);
	size = 0;
	while (read(fd, &c, 1) > 0)
	{	
		if (c == '\n')
			return (buf);
		buf[size++] = c;
		buf[size] = '\0';
		if (size == buf_size)
		{
			buf = ft_str_realloc(buf, size * 2);
			buf_size *= 2;
		}
	}
	if (size == 0)
		return (0);
	return (buf);
}

#include <stdio.h>

int main(){
	int fd = open("./test.txt", O_RDONLY);

	while (1){
		char *line = get_next_line(fd);
		if (!line)
			break;
		printf("%s\n", line);
		free(line);
	}
	close(fd);
}
