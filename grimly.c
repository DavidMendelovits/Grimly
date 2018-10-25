/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:51:31 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/25 08:56:36 by dmendelo         ###   ########.fr       */
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
		printf("|%c|\n", line[p]);
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
	(*map)->visited[point->row][point->column] = 1;
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

void			check_neighbors(t_list **queue, t_map **map, t_legend *l)
{
	WOW();
	t_coordinate			*parent;
	t_coordinate			tmp;

	if (*queue && (*queue)->data)
	{
		parent = pop(queue);	
		printf("1\n");
	}
	if (parent->row >= 0 && parent->row < l->height
		&& parent->column >= 0 && parent->column < l->width)
	{
		printf("hmm\n");
		if (parent->row > 0 && !(*map)->distances[parent->row - 1][parent->column]
							&& (*map)->map[parent->row - 1][parent->column] != l->full)
		{
			tmp.row = parent->row - 1;
			tmp.column = parent->column;
			write_distance(&tmp, map, l, (*map)->distances[parent->row][parent->column] + 1);
			push_back(queue, &tmp, sizeof(tmp));
			print_coordinates(*queue);
		}
		if (parent->column > 0 && !(*map)->distances[parent->row][parent->column - 1]
								&& (*map)->map[parent->row][parent->column - 1] != l->full)
		{
			tmp.row = parent->row;
			tmp.column = parent->column - 1;
			write_distance(&tmp, map, l, (*map)->distances[parent->row][parent->column] + 1);
			push_back(queue, &tmp, sizeof(tmp));
			print_coordinates(*queue);
		}
		if (parent->row < l->height - 1 && !(*map)->distances[parent->row + 1][parent->column]
						&& (*map)->map[parent->row + 1][parent->column ] != l->full)
		{
			printf("y\n");
			tmp.row = parent->row + 1;
			tmp.column = parent->column;
			write_distance(&tmp, map, l, (*map)->distances[parent->row][parent->column] + 1);
			push_back(queue, &tmp, sizeof(tmp));
			print_coordinates(*queue);
		}
		if (parent->column < l->width - 1&& !(*map)->distances[parent->row][parent->column + 1]
						&& (*map)->map[parent->row][parent->column + 1] != l->full)
		{
			tmp.row = parent->row;
			tmp.column = parent->column + 1;
			write_distance(&tmp, map, l, (*map)->distances[parent->row][parent->column] + 1);
			push_back(queue, &tmp, sizeof(tmp));
			print_coordinates(*queue);
		}
			print_matrix((*map)->distances, l->height, l->width);
			print_matrix((*map)->visited, l->height, l->width);
	}
	if (*queue && (*queue)->data)
	{
		check_neighbors(queue, map, l);
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
	write_distance(stack->data, map, legend, 1);
	print_matrix((*map)->distances, legend->height, legend->width);
	print_matrix((*map)->visited, legend->height, legend->width);
	check_neighbors(&stack, map, legend);
	return (1);
}

int				solve(t_map *map, t_legend *legend)
{
	map->visited = zero_matrix(legend->height, legend->width);
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
