/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozkaya <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:08:56 by oozkaya           #+#    #+#             */
/*   Updated: 2017/12/07 09:28:03 by oozkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*ft_node_browser(t_list **begin, int fd)
{
	t_list	*p;

	p = *begin;
	while (p)
	{
		if (fd == (int)p->content_size)
			return (p);
		p = p->next;
	}
	p = ft_lstnew("\0", 1);
	p->content_size = fd;
	ft_lstadd(begin, p);
	return (p);
}

char			*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
	char	*s;
	char	*join;

	//if (!s1 || !s2)
	//	return (NULL);
	s = ft_strnew(ft_strlen(s1) + len + 1);
	join = s;
	while (*s1)
		*s++ = *s1++;
	while (*s2 && len--)
		*s++ = *s2++;
	return (join);
}

char			*ft_strjoinfree(char const *s1, char const *s2, int pick)
{
	char	*join;

	//if (pick < 0 || pick > 2)
	//	return (NULL);
	join = ft_strjoin(s1, s2);
	if (pick == 0 || pick == 2)
		free((char*)s1);
	if (pick == 1 || pick == 2)
		free((char*)s2);
	return (join);
}

char	*ft_strnjoinfree(char const *s1, char const *s2, size_t len, int pick)
{
	char	*join;

	//if (pick < 0 || pick > 2)
	//	return (NULL);
	join = ft_strnjoin(s1, s2, len);
	if (pick == 0 || pick == 2)
		free((char*)s1);
	if (pick == 1 || pick == 2)
		free((char*)s2);
	return (join);
}

char	*ft_strndup(char const *s, size_t n)
{
	char	*str;

	if (!(str = ft_strnew(n)))
		return (NULL);
	str = ft_strncpy(str, s, n);
	str[n] = '\0';
	return (str);
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*p;
	char			buf[BUFF_SIZE + 1];
	int				ret;
	t_list			*begin;
	char			*tmp;

	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	begin = p;
	p = ft_node_browser(&begin, fd);
	while (!ft_strchr(p->content, '\n') && (ret = read(fd, buf, BUFF_SIZE)))
		p->content = ft_strnjoinfree(p->content, buf, ret, 0);
	ret = 0;
	while (((char*)p->content)[ret] && ((char*)p->content)[ret] != '\n')
		++ret;
	*line = ft_strndup(p->content, ret);
	(((char*)p->content)[ret] == '\n') ? ++ret : 0;
	tmp = p->content;
	p->content = ft_strdup(tmp + ret);
	p = begin;
	free(tmp);
	return (ret ? 1 : 0);
}
