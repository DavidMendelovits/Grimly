/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:08:49 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/27 14:58:45 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int				read_keys(t_legend **legend, char *line, int p)
{
	(*legend)->end = line[p--];
	(*legend)->start = line[p--];
	(*legend)->path = line[p--];
	(*legend)->empty = line[p--];
	(*legend)->full = line[p--];
	return (p);
}

t_legend		*read_first_line(int fd)
{
	char			*line;
	t_legend		*legend;
	int				p;
	int				end;

	legend = (t_legend *)malloc(sizeof(*legend));
	get_next_line(fd, &line);
	p = ft_strlen(line) - 1;
	p = read_keys(&legend, line, p);
	end = p;
	while (p >= 0 && ft_is_digit(line[p]) && line[p] != 'x')
		p -= 1;
	if (line[p] != 'x')
	{
		free(line);
		return (NULL);
	}
	legend->width = atoi_range(line, p + 1, end);
	end = --p;
	while (p > 0 && ft_is_digit(line[p]))
		p -= 1;
	if (p)
	{
		free(line);
		return (NULL);
	}
	legend->height = atoi_range(line, p, end);
	free(line);
	return (legend);
}

void			extract_line(t_map **map, char *line, t_legend *legend)
{
	static int		p = 0;
	int				x;

	x = 0;
	if (line[0] == legend->start || (x = ft_strchr_index(line, legend->start))) 
	{
		printf("found start\n");
		(*map)->start = (t_coordinate *)malloc(sizeof(t_coordinate));
		(*map)->start->row = p;
		(*map)->start->column = x;
	}
	else if ((x = ft_strchr_index(line, legend->end)))
	{
		printf("ends + 1\n");
		(*map)->ends += 1;
	}
	(*map)->map[p] = ft_strdup(line);
	p += 1;
}

t_map			*read_map(t_legend *legend, int fd)
{
	char			*line;
	t_map			*map;
	int				lines;

	lines = 0;
	map = (t_map *)malloc(sizeof(*map));
	map->map = (char **)malloc(sizeof(char *) * (legend->height + 1));
	map->start = NULL;
	map->ends = 0;
	while (get_next_line(fd, &line) == 1 && lines < legend->height)
	{
		if (!validate_line(line, legend))
		{
			free_map(map);
			return (NULL);
		}
		extract_line(&map, line, legend);
		lines += 1;
		free(line);
		line = NULL;
	}
	map->map[lines] = NULL;
	if (!map->start || !map->ends)
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}
