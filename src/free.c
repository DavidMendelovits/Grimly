/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:13:39 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/27 21:20:17 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

void			free_map(t_map *map)
{
	if (map)
	{
		if (map->map)
		{
			free_2d(map->map);
		}
		if (map->start)
		{
			free(map->start);
		}
		free(map);
	}
}

void			*terminate_object(void (*f)(void *content), void *ptr)
{
	if (ptr)
		(*f)(ptr);
	return (NULL);
}

void			free_2d(char **ptrs)
{
	int				p;

	p = 0;
	while (ptrs[p])
	{
		free(ptrs[p]);
		p += 1;
	}
	free(ptrs);
}
