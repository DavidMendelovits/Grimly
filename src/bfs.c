/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:11:48 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/26 16:57:20 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

t_coordinate			write_neighbor(t_coordinate *parent, t_map **map, int dir)
{
	WOW();
	t_coordinate			tmp;

	if (dir == UP)
		printf("up\n");
	if (dir == DOWN)
		printf("down\n");
	if (dir == LEFT)
		printf("left\n");
	if (dir == RIGHT)
		printf("right\n");
	if (dir == UP || dir == DOWN)
		tmp.row = (dir == UP) ? parent->row - 1 : parent->row + 1;
	else
		tmp.row = parent->row;
	if (dir == LEFT || dir == RIGHT)
		tmp.column = (dir == LEFT) ? parent->column - 1 : parent->column + 1;
	else
		tmp.column = parent->column;
	write_distance(&tmp, map, (*map)->distances[parent->row][parent->column] + 1);
	return (tmp);
}


void			queue_neighbors(t_list **queue, t_map **map, t_legend *l, t_coordinate *p)
{
	WOW();
	t_coordinate			tmp;

	if (is_inbounds(p->row, p->column, l))
	{
		if (is_inbounds(p->row - 1, p->column, l) && is_empty(p->row - 1, p->column, map, l))
		{
			tmp = write_neighbor(p, map, UP);
			push_back(queue, &tmp, sizeof(tmp));
		}
		if (is_inbounds(p->row, p->column - 1, l) && is_empty(p->row, p->column - 1, map, l))
		{
			tmp = write_neighbor(p, map, LEFT);
			push_back(queue, &tmp, sizeof(tmp));
		}
		if (is_inbounds(p->row + 1, p->column, l) && is_empty(p->row + 1, p->column, map, l))
		{
			tmp = write_neighbor(p, map, DOWN);
			push_back(queue, &tmp, sizeof(tmp));
		}
		if (is_inbounds(p->row, p->column + 1, l) && is_empty(p->row, p->column + 1, map, l))
		{
			tmp = write_neighbor(p, map, RIGHT);
			push_back(queue, &tmp, sizeof(tmp));
		}
	}
}

void			check_neighbors(t_list **queue, t_map **map, t_legend *l)
{
	WOW();
	t_coordinate			*parent;

	while (*queue)
	{
		if (*queue && (*queue)->data)
		{
			parent = pop(queue);
			if ((*map)->map[parent->row][parent->column] == l->end)
			{
				print_matrix((*map)->distances, l->height, l->width);
				trace_path(parent, map, l);
				print_strings((*map)->map, 0);
				break ;
			}	
		}
		queue_neighbors(queue, map, l, parent);
	}
}

int				bfs(t_map **map, t_legend *legend)
{
	t_map			*tmp;
	t_list			*stack;

	tmp = *map;
	stack = NULL;
	push(&stack, tmp->start, sizeof(tmp->start));
	print_coordinate(stack->data);
	write_distance(stack->data, map, 1);
	print_matrix((*map)->distances, legend->height, legend->width);
	check_neighbors(&stack, map, legend);
	return (1);
}
