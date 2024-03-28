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
		return (ft_strdup(""));
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
	size_t	len;

	s1_len = (size_t)(ft_get_chridx(s1, '\0') - s1);
	s2_len = (size_t)(ft_get_chridx(s2, '\0') - s2);
	join_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!join_str)
		return (0);
	len = 0;
	while (len < s1_len)
	{
		join_str[len] = s1[len];
		len++;
	}
	while (len < s1_len + s2_len)
	{
		join_str[len] = s2[len - s1_len];
		len++;
	}
	join_str[len] = '\0';
	free(s1);
	free(s2);
	return (join_str);
}