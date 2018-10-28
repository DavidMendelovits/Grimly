/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:11:48 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/27 21:19:52 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

void			write_parent(t_point *child, t_map **map, int dir)
{
	if (dir == UP)
		(*map)->parents[child->row][child->column] = DOWN;
	else if (dir == LEFT)
		(*map)->parents[child->row][child->column] = RIGHT;
	else if (dir == RIGHT)
		(*map)->parents[child->row][child->column] = LEFT;
	else if (dir == DOWN)
		(*map)->parents[child->row][child->column] = UP;
}

t_point			write_neighbor(t_point *p, t_map **map, int dir)
{
	t_point			tmp;

	if (dir == UP || dir == DOWN)
		tmp.row = (dir == UP) ? p->row - 1 : p->row + 1;
	else
		tmp.row = p->row;
	if (dir == LEFT || dir == RIGHT)
		tmp.column = (dir == LEFT) ? p->column - 1 : p->column + 1;
	else
		tmp.column = p->column;
	write_parent(&tmp, map, dir);
	write_distance(&tmp, map, (*map)->distances[p->row][p->column] + 1);
	return (tmp);
}

void			q_neighbors(t_list **q, t_map **m, t_legend *l, t_point *p)
{
	t_point			tmp;

	if (is_valid_tile(p->row - 1, p->column, l, m))
	{
		tmp = write_neighbor(p, m, UP);
		push_back(q, &tmp, sizeof(tmp));
	}
	if (is_valid_tile(p->row, p->column - 1, l, m))
	{
		tmp = write_neighbor(p, m, LEFT);
		push_back(q, &tmp, sizeof(tmp));
	}
	if (is_valid_tile(p->row + 1, p->column, l, m))
	{
		tmp = write_neighbor(p, m, DOWN);
		push_back(q, &tmp, sizeof(tmp));
	}
	if (is_valid_tile(p->row, p->column + 1, l, m))
	{
		tmp = write_neighbor(p, m, RIGHT);
		push_back(q, &tmp, sizeof(tmp));
	}
}

void			choose_path(t_point **p, t_map **map)
{
	t_point			*tmp;
	t_point			*new;

	new = (t_point *)malloc(sizeof(*new));
	tmp = *p;
	if ((*map)->parents[tmp->row][tmp->column] == UP
	|| (*map)->parents[tmp->row][tmp->column] == DOWN)
		new->row = ((*map)->parents[tmp->row][tmp->column] == UP) ?
		tmp->row - 1 :
		tmp->row + 1;
	else
		new->row = tmp->row;
	if ((*map)->parents[tmp->row][tmp->column] == LEFT
	|| (*map)->parents[tmp->row][tmp->column] == RIGHT)
		new->column = ((*map)->parents[tmp->row][tmp->column] == LEFT) ?
		tmp->column - 1 :
		tmp->column + 1;
	else
		new->column = tmp->column;
	free(tmp);
	*p = new;
	(*map)->steps = 1;
}

int				check_neighbors(t_list **queue, t_map **map, t_legend *l)
{
	t_point			*parent;

	while (*queue)
	{
		if (*queue && (*queue)->data)
		{
			parent = pop(queue);
			if ((*map)->map[parent->row][parent->column] == l->end)
			{
				choose_path(&parent, map);
				if ((*map)->map[parent->row][parent->column] != l->start)
				{
					(*map)->map[parent->row][parent->column] = l->path;
					trace_path(parent, map, l);
					print_solution((*map)->map, (*map)->steps, l);
				}
				else
					print_solution((*map)->map, (*map)->steps, l);
				return (1);
			}
		}
		if (is_inbounds(parent->row, parent->column, l))
			q_neighbors(queue, map, l, parent);
	}
	return (0);
}
