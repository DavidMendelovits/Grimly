/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:15:18 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/26 17:24:49 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int				validate_line(char *line, t_legend *legend)
{
	int				p;

	p = -1;
	while (line[++p])
	{
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
