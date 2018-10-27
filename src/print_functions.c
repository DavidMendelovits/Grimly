/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:08:01 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/26 17:25:25 by dmendelo         ###   ########.fr       */
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
