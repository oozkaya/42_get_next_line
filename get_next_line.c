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

int		ft_check_fd(fd,)
{
	t_list	*file;
	t_list	*tmp;
	tmp = file;
	while (file->next)
	{
		if (file->fd == fd)
			return (file);
		file = file->next;
	}
	tmp->fd = fd;
	tmp->left = 
	return (0);
}

t_list	ft_get_fd(fd)
{
	if (ft_check_fd(fd))

}

int		get_next_line(const int fd, char **line)
{
	
	int		newlen;
	int		piece;
	char	*buff;
	char	*newbuff;
	//char	tmp[2];

	newlen = 0;
	piece = 0;
	buff = malloc(1);
	buff[0] = 0;
	while ((piece = read(fd, *line, BUFF_SIZE)))
	{
		newlen += piece;
		if (!(newbuff = malloc(sizeof(char) * (newlen + 1))))
			return (0);
		ft_strcpy(newbuff, buff);
		ft_strcat(newbuff, *line);
		free(buff);
		buff = newbuff;
		buff[newlen] = 0;
	}
	return (1);
}

