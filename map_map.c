/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 15:14:34 by dmendelo          #+#    #+#             */
/*   Updated: 2018/07/20 18:06:14 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"
#include "get_next_line.h"

int		get_mapsize(t_mapsize *dimensions, char *tmp)
{
	char	*_wid;
	char	*_len;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (tmp[i] != 'x')
		i++;
	_len = (char*)malloc(sizeof(char) * (i + 1));
	printf("tmp: %s\n", tmp);
	copy_until(&_len, tmp, 'x');
	printf("_len: %s\n", _len);
	i = ft_strlen(tmp) - ft_strlen(_len) - 6;
	_wid = (char*)malloc(sizeof(char) * (i + 1));
	i = ft_strlen(tmp) - 5;
	j = ft_strlen(_len) + 1;
	k = -1;
	printf("i: %i\n", i);
	printf("j: %i\n", j);
	printf("k: %i\n", k);	
	while (j < i)
		_wid[++k] = tmp[j++];
	printf("_len: %s\n", _len);
	printf("_wid: %s\n", _wid);
	dimensions->y = atoi(_len);
	dimensions->x = atoi(_wid);
	printf("height: %i\n", dimensions->x);
	printf("width: %i\n", dimensions->y);
	return (1);
}

int		build_map(t_mapsize dim, char *tmp, t_mapkeys *keys)
{
	int				x;
    int             i;
	char		    graph[dim.y][dim.x];
    char            map[dim.y][dim.x];
	static int  	y = 0;

	x = 0;
    i = 0;

    while (i < dim.x)
    {
        map[y][x] = tmp[i++];
        ft_putchar(map[y][x++]);
    }
    y++;
    ft_putchar('\n');
    if (y == dim.y)
    {
        y = 0;
        while (y < dim.y)
        {
            x = 0;
            while (x < dim.x)
                ft_putchar(map[y][x++]);
            ft_putchar('\n');
            y++;
        }
    }
    make_adj_list(&graph, keys, map);
//	while (x < dim.x)
//	{
//        
//	}
//	if (y != 0)
//	{
//
//	}
//	while (i < dim.x)
//		**(map++) = tmp[i++];
	return (1);
}

