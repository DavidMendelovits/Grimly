/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:17:53 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/26 16:51:59 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

void			write_distance(t_coordinate *point, t_map **map, int i)
{
	(*map)->distances[point->row][point->column] = i;
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

