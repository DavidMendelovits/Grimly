/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:08:49 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/27 21:27:31 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int				read_keys(t_legend **legend, char *line, int *p)
{
	int				ret;

	*p = ft_strlen(line) - 1;
	ret = *p;
	(*legend)->end = line[(*p)--];
	(*legend)->start = line[(*p)--];
	(*legend)->path = line[(*p)--];
	(*legend)->empty = line[(*p)--];
	(*legend)->full = line[(*p)--];
	return (ret);
}

t_legend		*read_first_line(int fd)
{
	char			*line;
	t_legend		*legend;
	int				p;
	int				end;

	legend = (t_legend *)malloc(sizeof(*legend));
	get_next_line(fd, &line);
	end = read_keys(&legend, line, &p);
	while (p >= 0 && ft_is_digit(line[p]) && line[p] != 'x')
		p -= 1;
	if (p <= 0 || line[p] != 'x')
		return (terminate_object((free), line));
	legend->width = atoi_range(line, p + 1, end);
	end = --p;
	while (p > 0 && ft_is_digit(line[p]))
		p -= 1;
	if (p)
		return (terminate_object((free), line));
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
		(*map)->start = (t_point *)malloc(sizeof(t_point));
		(*map)->start->row = p;
		(*map)->start->column = x;
	}
	else if (line[0] == legend->end || (x = ft_strchr_index(line, legend->end)))
	{
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
			return (terminate_object((t_terminate)(free_map), map));
		extract_line(&map, line, legend);
		lines += 1;
		free(line);
		line = NULL;
	}
	map->map[lines] = NULL;
	if (!map->start || !map->ends)
		return (terminate_object((t_terminate)(free_map), map));
	return (map);
}
