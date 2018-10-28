/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:14:21 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/27 21:42:53 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int				is_better_path(int **matrix, t_point *p, t_point *tmp, int dir)
{
	t_point			*new;

	new = malloc(sizeof(*new));
	if (dir == UP || dir == DOWN)
		new->row = (dir == UP) ? p->row - 1 : p->row + 1;
	else
		new->row = p->row;
	if (dir == LEFT || dir == RIGHT)
		new->column = (dir == LEFT) ? p->column - 1 : p->column + 1;
	else
		new->column = p->column;
	if (matrix[new->row][new->column]
	&& matrix[new->row][new->column] < matrix[tmp->row][tmp->column])
	{
		free(new);
		return (1);
	}
	free(new);
	return (0);
}

void			write_coordinate(t_point **point, int row, int column)
{
	(*point)->row = row;
	(*point)->column = column;
}

void			get_best_path(t_point **tmp, t_point *p, int **d, t_legend *l)
{
	if (p->row > 0 && d[p->row - 1][p->column] > 0)
		write_coordinate(tmp, p->row - 1, p->column);
	if (p->column > 0 && is_better_path(d, p, *tmp, LEFT))
		write_coordinate(tmp, p->row, p->column - 1);
	if (p->column < l->width - 1 && is_better_path(d, p, *tmp, RIGHT))
		write_coordinate(tmp, p->row, p->column + 1);
	if (p->row < l->height - 1 && is_better_path(d, p, *tmp, DOWN))
		write_coordinate(tmp, p->row + 1, p->column);
}

void			trace_path(t_point *end, t_map **map, t_legend *legend)
{
	t_point			*path;
	t_point			*tmp;

	path = end;
	tmp = malloc(sizeof(*tmp));
	write_coordinate(&tmp, path->row, path->column);
	while ((*map)->map[path->row][path->column] != legend->start)
	{
		if (is_inbounds(path->row, path->column, legend))
			get_best_path(&tmp, path, (*map)->distances, legend);
		free(path);
		path = malloc(sizeof(t_point));
		ft_memcpy(path, tmp, sizeof(tmp));
		if ((*map)->map[path->row][path->column] != legend->start)
		{
			(*map)->map[path->row][path->column] = legend->path;
			(*map)->steps += 1;
		}
	}
}
