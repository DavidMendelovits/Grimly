/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_range.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:19:36 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/27 21:19:13 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int				atoi_range(char *s, int begin, int end)
{
	char			*tmp;
	int				num;

	tmp = ft_strdup_range(s, begin, end);
	num = atoi(tmp);
	free(tmp);
	return (num);
}

int				is_valid_tile(int row, int column, t_legend *l, t_map **map)
{
	if (is_inbounds(row, column, l) && is_empty(row, column, map, l))
	{
		return (1);
	}
	return (0);
}
