/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:51:31 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/27 14:58:34 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int				solve(t_map *map, t_legend *legend)
{
	map->distances = zero_matrix(legend->height, legend->width);
	map->parents = zero_matrix(legend->height, legend->width);
	if (!bfs(&map, legend))
		return (0);
	return (1);
}

void			read_validate_map(int fd)
{
	t_legend		*legend;
	t_map			*map;

	legend = read_first_line(fd);
	if (!legend)
	{
		write_error(MAP_ERROR, sizeof(MAP_ERROR));
		return ;
	}
	print_legend(legend);
	map = read_map(legend, fd);
	if (!map)
	{
		write_error(MAP_ERROR, sizeof(MAP_ERROR));
		return ;
	}
	if (!solve(map, legend))
	{
		write_error(MAP_ERROR, sizeof(MAP_ERROR));
		return ;
	}
}

void			read_file(char *filename)
{
	int				fd;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write_error(MAP_ERROR, sizeof(MAP_ERROR));
		return ;
	}
	read_validate_map(fd);
	close(fd);
}

int			main(int argc, char **argv)
{
	int				i;

	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			read_file(argv[i]);
			i += 1;
		}
	}
	else
	{
		read_validate_map(0);
	}
	return (0);
}
