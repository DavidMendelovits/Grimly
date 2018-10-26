/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:08:49 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/26 16:11:16 by dmendelo         ###   ########.fr       */
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
	printf("first line = %s\n", line);
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
	printf("height = %d\n", legend->height);
	free(line);
	return (legend);
}

void			extract_line(t_map **map, char *line, t_legend *legend)
{
	static int		p = 0;
	int				x;

	if ((x = ft_strchr_index(line, legend->start))) 
	{
		(*map)->start = (t_coordinate *)malloc(sizeof(t_coordinate));
		(*map)->start->row = p;
		(*map)->start->column = x;
		printf("start at [%d][%d]\n", (*map)->start->row, (*map)->start->column);
	}
	(*map)->map[p] = ft_strdup(line);
	printf("extracted: %s\n", (*map)->map[p]);
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
	while (get_next_line(fd, &line) == 1 && lines < legend->height)
	{
		printf("len = %d\n", ft_strlen(line));
		printf("width = %u\n", legend->width);
		if (!validate_line(line, legend))
		{
			printf("noooo\n");
			free(map);
			return (NULL);
		}
		extract_line(&map, line, legend);
		lines += 1;
		printf("line num = %d\n", lines);
		free(line);
		line = NULL;
	}
	map->map[lines] = NULL;
	return (map);
}
