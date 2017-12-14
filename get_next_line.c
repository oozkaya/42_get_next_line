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
	t_list	*file;

	file = *begin;
	while (file)
	{
		if (fd == (int)file->content_size)
			return (file);
		file = file->next;
	}
	file = ft_lstnew("\0", 1);
	file->content_size = fd;
	ft_lstadd(begin, file);
	return (file);
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*file;
	char			buf[BUFF_SIZE + 1];
	int				ret;
	t_list			*begin;
	char			*tmp;

	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	begin = file;
	file = ft_check_fd(&begin, fd);
	while (!ft_memchr(file->content, '\n', ft_strlen(file->content) + 1)
			&& (ret = read(fd, buf, BUFF_SIZE)))
		file->content = ft_strnjoinfree(file->content, buf, ret, 0);
	ret = 0;
	while (((char*)file->content)[ret] && ((char*)file->content)[ret] != '\n')
		++ret;
	*line = ft_strndup(file->content, ret);
	(((char*)file->content)[ret] == '\n') ? ++ret : 0;
	tmp = file->content;
	file->content = ft_strdup(file->content + ret);
	free(tmp);
	file = begin;
	return (ret ? 1 : 0);
}
