/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:11:48 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/27 15:00:58 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

void			write_parent(t_coordinate *child, t_map **map, int dir)
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

t_coordinate	write_neighbor(t_coordinate *parent, t_map **map, int dir)
{
	t_coordinate			tmp;

	if (dir == UP || dir == DOWN)
		tmp.row = (dir == UP) ? parent->row - 1 : parent->row + 1;
	else
		tmp.row = parent->row;
	if (dir == LEFT || dir == RIGHT)
		tmp.column = (dir == LEFT) ? parent->column - 1 : parent->column + 1;
	else
		tmp.column = parent->column;
	write_parent(&tmp, map, dir);
	write_distance(&tmp, map, (*map)->distances[parent->row][parent->column] + 1);
	return (tmp);
}


void			queue_neighbors(t_list **queue, t_map **map, t_legend *l, t_coordinate *p)
{
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

void			choose_path(t_coordinate **p, t_map **map)
{
	t_coordinate			*tmp;
	t_coordinate			*new;

	new = (t_coordinate *)malloc(sizeof(*new));
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
}

void			print_parents(int **parents, int height, int width)
{
	int						p;
	int						i;

	p = 0;
	while (p < height)
	{
		i = 0;
		while (i < width)
		{
			if (parents[p][i] == UP)
				printf("%2c", '^');
			else if (parents[p][i] == LEFT)
				printf("%2c", '<');
			else if (parents[p][i] == RIGHT)
				printf("%2c", '>');
			else if (parents[p][i] == DOWN)
				printf("%2c", '|');
			else
				printf("%2d", 0);
			i += 1;
		}
		printf("\n");
		p += 1;
	}
	printf("----------------------\n");
}

void			check_neighbors(t_list **queue, t_map **map, t_legend *l)
{
	t_coordinate			*parent;

	while (*queue)
	{
		if (*queue && (*queue)->data)
		{
			parent = pop(queue);
			if ((*map)->map[parent->row][parent->column] == l->end)
			{
				print_coordinate(parent);
				printf("%c\n", (*map)->map[parent->row][parent->column]);
				choose_path(&parent, map);
				(*map)->map[parent->row][parent->column] = l->path;
				trace_path(parent, map, l);
				print_strings((*map)->map, 0);
				return ;
			}	
		}
		queue_neighbors(queue, map, l, parent);
	}
	write_error(MAP_ERROR, sizeof(MAP_ERROR));
}

int				bfs(t_map **map, t_legend *legend)
{
	t_map			*tmp;
	t_list			*stack;

	tmp = *map;
	stack = NULL;
	push(&stack, tmp->start, sizeof(tmp->start));
	write_distance(stack->data, map, 1);
	check_neighbors(&stack, map, legend);
	return (1);
}
