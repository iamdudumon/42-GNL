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

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_get_chridx(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (0);
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

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (ft_strdup(""));
	len = ft_strlen(s);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (0);
	dup[0] = '\0';
	ft_strlcat(dup, s, len + 1);
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
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
