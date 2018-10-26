/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:51:31 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/25 17:08:48 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"
#define WOW() printf("->%s\n", __func__)

void			print_legend(t_legend *legend)
{
	printf("full_char = |%c|\n", legend->full);
	printf("empty_char = |%c|\n", legend->empty);
	printf("path_char = |%c|\n", legend->path);
	printf("start_char = |%c|\n", legend->start);
	printf("end_char = |%c|\n", legend->end);
	printf("dimension = %dx%d\n", legend->height, legend->width);
}

void			print_strings(char **strings, int p)
{
	if (!strings)
		return ;
	if (strings[p])
	{
		printf("%s\n", strings[p]);
	}
	if (strings[p + 1])
	{
		print_strings(strings, p + 1);
	}
}

int				read_keys(t_legend **legend, char *line, int p)
{
	(*legend)->end = line[p--];
	(*legend)->start = line[p--];
	(*legend)->path = line[p--];
	(*legend)->empty = line[p--];
	(*legend)->full = line[p--];
	return (p);
}

int				atoi_range(char *s, int begin, int end)
{
	char			*tmp;
	int				num;

	tmp = ft_strdup_range(s, begin, end);
	num = atoi(tmp);
	free(tmp);
	return (num);
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

int				validate_line(char *line, t_legend *legend)
{
	int				p;

	p = -1;
	while (line[++p])
	{
	//	printf("|%c|\n", line[p]);
		if (line[p] == legend->full || line[p] == legend->empty
		|| line[p] == legend->start || line[p] == legend->end)
		{
			continue ;
		}
		else
			return (0);
	}
	if (p != legend->width)
		return (0);
	return (1);
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

void			print_matrix(int **matrix, int height, int width)
{
	int				x;
	int				y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			printf("%2d", matrix[y][x]);
			x += 1;
		}
		printf("\n");
		y += 1;
	}
	printf("----------------\n");
}

int				**zero_matrix(int height, int width)
{
	int				**matrix;
	int				p;
	int				x;

	p = 0;
	matrix = (int **)malloc(sizeof(int *) * (height));
	while (p < height)
	{
		matrix[p] = (int *)malloc(sizeof(int) * (width));
		x = 0;
		while (x < width)
		{
			matrix[p][x] = 0;
			x += 1;
		}
		p += 1;
	}
	print_matrix(matrix, height, width);
	return (matrix);
}

void			print_coordinate(t_coordinate *point)
{
	printf("[%d]", point->row);
	printf("[%d]\n", point->column);
}

void			push(t_list **head, void *new_data, size_t size)
{
	WOW();
	t_list			*new;

	new = (t_list *)malloc(sizeof(*new));
	new->data = malloc(size);
	ft_memcpy(new->data, new_data, size);
	new->size = size;
	if (!(*head))
	{
		printf("2\n");
		new->next = NULL;
	}
	else
	{
		printf("1\n");
		new->next = *head;
	}
	*head = new;
}

void			push_back(t_list **head, void *new_data, size_t size)
{
	t_list					*new;
	t_list					*tmp;

	new = (t_list *)malloc(sizeof(*new));
	new->data = malloc(size);
	ft_memcpy(new->data, new_data, size);
	new->size = size;
	new->next = NULL;
	tmp = *head;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}


void			write_distance(t_coordinate *point, t_map **map, t_legend *l, int i)
{
	(*map)->distances[point->row][point->column] = i;
}

void			print_coordinates(t_list *queue)
{
	WOW();
	if (queue && queue->data)
	{
		print_coordinate(queue->data);
	}
	if (queue->next)
	{
		print_coordinates(queue->next);
	}
}

void			*pop(t_list **head)
{
	void					*data;
	t_list					*new;

	data = malloc((*head)->size);
	ft_memcpy(data, (*head)->data, (*head)->size);
	new = (*head)->next;
	free((*head)->data);
	free(*head);
	*head = new;
	return (data);
}

void			trace_path(t_coordinate *end, t_map **map, t_legend *legend)
{
	WOW();
	t_coordinate			*path;
	t_coordinate			*tmp;

	path = end;
	tmp = malloc(sizeof(*tmp));
	while ((*map)->map[path->row][path->column] != legend->start)
	{
		if (path->row > 0 && path->row < legend->height && path->column > 0 && path->column < legend->width)
		{
			if (path->row > 0 && (*map)->distances[path->row - 1][path->column] > 0)
			{
				tmp->row = path->row - 1;
				tmp->column = path->column;
			}
			if (path->column > 0
					&&(*map)->distances[path->row][path->column - 1] > 0
				   	&& (*map)->distances[path->row][path->column - 1] < (*map)->distances[tmp->row][tmp->column])
			{
				tmp->row = path->row;
				tmp->column = path->column - 1;
			}
			if (path->column < legend->width - 1
					&& (*map)->distances[path->row][path->column + 1] > 0
					&& (*map)->distances[path->row][path->column + 1] < (*map)->distances[tmp->row][tmp->column])
			{
				tmp->row = path->row;
				tmp->column = path->column + 1;
			}
			if (path->row < legend->height - 1 
					&& (*map)->distances[path->row + 1][path->column] > 0
				    && (*map)->distances[path->row + 1][path->column] < (*map)->distances[tmp->row][tmp->column])
			{
				tmp->row = path->row + 1;
				tmp->column = path->column;
			}
		}
		free(path);
		path = malloc(sizeof(t_coordinate));
		ft_memcpy(path, tmp, sizeof(tmp));
		if ((*map)->map[path->row][path->column] != legend->start)
		{
			(*map)->map[path->row][path->column] = legend->path;
		}
	}
}

int				is_inbounds(int row, int column, t_legend *l)
{
	if (row >= 0 && row < l->height && column >= 0 && column < l->width)
	{
		return (1);
	}
	return (0);

}

int				is_empty(int row, int column, t_map **map, t_legend *l)
{
	if (!(*map)->distances[row][column] && (*map)->map[row][column] != l->full)
	{
		return (1);
	}
	return (0);
}

t_coordinate			write_neighbor(t_coordinate *parent, t_map **map, t_legend *l, int dir)
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
	printf("[%d][%d]\n", tmp.row, tmp.column);
	write_distance(&tmp, map, l, (*map)->distances[parent->row][parent->column] + 1);
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
			tmp = write_neighbor(p, map, l, UP);
			push_back(queue, &tmp, sizeof(tmp));
		}
		if (is_inbounds(p->row, p->column - 1, l) && is_empty(p->row, p->column - 1, map, l))
		{
			tmp = write_neighbor(p, map, l, LEFT);
			push_back(queue, &tmp, sizeof(tmp));
		}
		if (is_inbounds(p->row + 1, p->column, l) && is_empty(p->row + 1, p->column, map, l))
		{
			tmp = write_neighbor(p, map, l, DOWN);
			push_back(queue, &tmp, sizeof(tmp));
		}
		if (is_inbounds(p->row, p->column + 1, l) && is_empty(p->row, p->column + 1, map, l))
		{
			tmp = write_neighbor(p, map, l, RIGHT);
			push_back(queue, &tmp, sizeof(tmp));
		}
	}
}

void			check_neighbors(t_list **queue, t_map **map, t_legend *l)
{
	WOW();
	t_coordinate			*parent;
	t_coordinate			tmp;

//			print_matrix((*map)->distances, l->height, l->width);
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
	//		printf("1\n");
		}
		queue_neighbors(queue, map, l, parent);
	}
//	if (*queue && (*queue)->data)
//	{
//		check_neighbors(queue, map, l);
//	}
//	
//			print_matrix((*map)->distances, l->height, l->width);
}

int				bfs(t_map **map, t_legend *legend)
{
	t_map			*tmp;
	t_list			*stack;

	tmp = *map;
	stack = NULL;
	push(&stack, tmp->start, sizeof(tmp->start));
	print_coordinate(stack->data);
	write_distance(stack->data, map, legend, 1);
	print_matrix((*map)->distances, legend->height, legend->width);
	check_neighbors(&stack, map, legend);
	return (1);
}

int				solve(t_map *map, t_legend *legend)
{
	map->distances = zero_matrix(legend->height, legend->width);
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
		return ;
	print_legend(legend);
	map = read_map(legend, fd);
	if (!map)
		return ;
	print_strings(map->map, 0);	
	if (!solve(map, legend))
	{
		printf("error\n");
		return ;
	}
}

void			read_file(char *filename)
{
	int				fd;
	
	fd = open(filename, O_RDONLY);
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
