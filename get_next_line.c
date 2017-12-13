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

static t_list	*ft_check_fd(t_list **begin, int fd)
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
	p = ft_check_fd(&begin, fd);
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
