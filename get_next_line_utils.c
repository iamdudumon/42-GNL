/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:55:19 by dukim             #+#    #+#             */
/*   Updated: 2024/03/15 20:02:39 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

// char    *ft_str_realloc(char *s, size_t len)
// {
// 	char	*realloc;
// 	size_t	i;

// 	realloc = (char *)malloc(sizeof(char) * len);
// 	if (!realloc)
// 		return (0);
// 	i = -1;
// 	while (++i < len)
// 		realloc[i] = s[i];
// 	realloc[i] = '\0';
// 	free(s);
// 	return (realloc);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!join_str)
		return (0);
	join_str[0] = '\0';
	ft_strlcat(join_str, s1, s1_len + 1);
	ft_strlcat(join_str, s2, s1_len + s2_len + 1);
	free(s1);
	free(s2);
	return (join_str);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	if (!dst && size == 0)
		return (0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len > size)
		return (src_len + size);
	i = 0;
	while (*src != '\0' && dst_len + i + 1 < size)
	{
		dst[dst_len + i] = *src++;
		i++;
	}
	dst[dst_len + i] = 0;
	return (dst_len + src_len);
}
