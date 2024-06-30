/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:34:17 by dukim             #+#    #+#             */
/*   Updated: 2024/06/28 13:34:18 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	int				fd;
	char			*backup;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

char	*get_next_line(int fd);

char	*ft_get_chridx(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2, char end);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(int fd);
void	del_node(t_list **list, t_list *node);

#endif
