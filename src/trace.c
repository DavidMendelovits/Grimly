/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:14:21 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/27 15:01:45 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int				is_better_path(int **matrix, t_coordinate *path, t_coordinate *tmp, int dir)
{
	t_coordinate			*new;

	print_coordinate(tmp);
	new = malloc(sizeof(*new));
//	if (dir == UP)
//		printf("up\n");
//	if (dir == DOWN)
//		printf("down\n");
//	if (dir == RIGHT)
//		printf("right\n");
//	if (dir == LEFT)
//		printf("left\n");
	if (dir == UP || dir == DOWN)
		new->row = (dir == UP) ? path->row - 1 : path->row + 1;
	else
		new->row = path->row;
	if (dir == LEFT || dir == RIGHT)
		new->column = (dir == LEFT) ? path->column - 1 : path->column + 1;
	else
		new->column = path->column;
	if (matrix[new->row][new->column]
	&& matrix[new->row][new->column] < matrix[tmp->row][tmp->column])
	{
		free(new);
		return (1);
	}
	free(new);
	return (0);
}

void			write_coordinate(t_coordinate **point, int row, int column)
{
	(*point)->row = row;
	(*point)->column = column;
}

void			trace_path(t_coordinate *end, t_map **map, t_legend *legend)
{
	t_coordinate			*path;
	t_coordinate			*tmp;

	path = end;
	tmp = malloc(sizeof(*tmp));
	write_coordinate(&tmp, path->row, path->column);
	while ((*map)->map[path->row][path->column] != legend->start)
	{
		if (is_inbounds(path->row, path->column, legend))
		{
			if (path->row > 0 && (*map)->distances[path->row - 1][path->column] > 0)
				write_coordinate(&tmp, path->row - 1, path->column);
	print_coordinate(tmp);
			if (path->column > 0 && is_better_path((*map)->distances, path, tmp, LEFT))
				write_coordinate(&tmp, path->row, path->column - 1);
	print_coordinate(tmp);
			if (path->column < legend->width - 1 && is_better_path((*map)->distances, path, tmp, RIGHT))
				write_coordinate(&tmp, path->row, path->column + 1);
	print_coordinate(tmp);
			if (path->row < legend->height - 1 && is_better_path((*map)->distances, path, tmp, DOWN)) 
				write_coordinate(&tmp, path->row + 1, path->column);
	print_coordinate(tmp);
		}
		free(path);
		path = malloc(sizeof(t_coordinate));
		ft_memcpy(path, tmp, sizeof(tmp));
		if ((*map)->map[path->row][path->column] != legend->start)
			(*map)->map[path->row][path->column] = legend->path;
	}
}
