/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-verd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:46:04 by ade-verd          #+#    #+#             */
/*   Updated: 2017/12/13 15:35:33 by ade-verd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int		ft_open_file(char *path, int flags)
{
	int		fd;

	fd = open(path, flags);
	if (fd == -1)
	{
		ft_putstr_fd("open() error\n", 2);
		return (-1);
	}
	return (fd);
}

int		ft_close(int fd)
{
	if (close(fd) == -1)
	{
		ft_putstr_fd("close() error\n", 2);
		return (-1);
	}
	return (1);
}

void	ft_print_n_free(int i, int ret, int fd, char **line)
{
	printf("line: %d\t\treturn: %d\tfd: %d\t|%s|\n", i, ret, fd, *line);
	ft_memdel((void**)line);
}

int		ft_display_all_fd(char *path)
{
	char	*line;
	int		ret;
	int		i;
	int		fd;

	i = 0;
	if ((fd = ft_open_file(path, O_RDONLY)) == -1)
		return (-1);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ret == -1)
		{
			printf("get_next_line() error\n");
			return (-1);
		}
		ft_print_n_free(i, ret, fd, &line);
		i++;
	}
	printf("-----\n");
	if (ft_close(fd) == -1)
		return (-1);
	return (1);
}

int		ft_display_altern_fd(char *path1, char *path2, int fd1, int fd2)
{
	char	*line1;
	char	*line2;
	int		ret1;
	int		ret2;
	int		i;

	i = 0;
	ret1 = 1;
	ret2 = 1;
	if ((fd1 = ft_open_file(path1, O_RDONLY)) == -1)
		return (-1);
	if ((fd2 = ft_open_file(path2, O_RDONLY)) == -1)
		return (-1);
	while (ret1 || ret2)
	{
		if ((ret1 = get_next_line(fd1, &line1)) == 1)
			ft_print_n_free(i, ret1, fd1, &line1);
		if ((ret2 = get_next_line(fd2, &line2)) == 1)
			ft_print_n_free(i, ret2, fd2, &line2);
		if (ret1 == ret2)
			printf("-----\n");
		i++;
	}
	return ((ft_close(fd1) == -1 || ft_close(fd2) == -1) ? -1 : 1);
}

int		main(int ac, char **av)
{
	if (ac == 2)
		ft_display_all_fd(av[1]);
	else if (ac == 3)
		ft_display_altern_fd(av[1], av[2], 0, 0);
	return (0);
}
