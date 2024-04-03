/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:55:19 by dukim             #+#    #+#             */
/*   Updated: 2024/03/15 20:02:39 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = 0;
	while (src[src_len] != '\0' && src_len + 1 < size)
	{
		dst[src_len] = src[src_len];
		src_len++;
	}
	if (size > 0)	
		dst[src_len] = '\0';
	while (src[src_len] != '\0')
		src_len++;
	return (src_len);
}

char	*ft_get_chridx(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	s_len;
	size_t	len;

	if (!s)
		return (0);
	s_len = (size_t)(ft_get_chridx(s, '\0') - s);
	dup = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!dup)
		return (0);
	len = 0;
	while (len < s_len)
	{
		dup[len] = s[len];
		len++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
	{
		free(s1);
		free(s2);
		return (0);
	}
	s1_len = (size_t)(ft_get_chridx(s1, '\0') - s1);
	s2_len = (size_t)(ft_get_chridx(s2, '\0') - s2);
	join_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!join_str)
	{
		free(s1);
		free(s2);
		return (0);
	}
	ft_strlcpy(join_str, s1, s1_len + 1);
	ft_strlcpy(join_str + s1_len, s2, s2_len + 1);
	free(s1);
	free(s2);
	return (join_str);
}

char	*ft_get_sub_newline(char *s, int end_flag)
{
	char	*newline;
	size_t	s_len;

	if (!s)
		return (0);
	if (*s == '\0')
	{
		free(s);
		return (0);
	}
	if (end_flag)
		s_len = (size_t)(ft_get_chridx(s, '\0') - s);
	else
		s_len = (size_t)(ft_get_chridx(s, '\n') - s) + 1;
	newline = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!newline)
	{
		free(s);
		return (0);
	}
	ft_strlcpy(newline, s, s_len + 1);
	free(s);
	return (newline);
}