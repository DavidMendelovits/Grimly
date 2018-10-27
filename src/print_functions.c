/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:08:01 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/27 16:07:48 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

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

void			print_coordinate(t_coordinate *point)
{
	printf("[%d]", point->row);
	printf("[%d]\n", point->column);
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

void			print_2d(char **s)
{
	int						p;

	p = 0;
	while (s[p])
	{
		b_printf("%s\n", s[p]);
		p += 1;
	}
}

void			print_solution(char **map, int steps, t_legend *l)
{
	b_printf("%ix%i%c%c%c%c%c\n", l->height, l->width, l->full, l->empty, l->path, l->start, l->end);
	print_2d(map);
	ft_putstr("RESULT IN ");
	ft_putnbr_base((unsigned long long)steps, 10);
	ft_putstr(" STEPS!\n");
}

void			*write_error(char *err, size_t size)
{
	write(2, err, size);
	return (NULL);
}
