/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 20:17:46 by dmendelo          #+#    #+#             */
/*   Updated: 2018/07/20 18:06:31 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"
#include "get_next_line.h"

int		validate_char(char c, t_mapkeys *map_keys)
{
	if (c == (*map_keys).entr)
		return (1);
	if (c == (*map_keys).exit)
		return (1);
	if (c == (*map_keys).path)
		return (1);
	if (c == (*map_keys).fill)
		return (1);
	if (c == (*map_keys).empty)
		return (1);
	return (0);
}

/*
** validate each character in each line against keys
*/

int     validate_line(char *tmp, t_mapkeys *map_keys)
{
    int     i;

    i = 0;
    while (i <= ft_strlen(tmp) && tmp[i] != '\0')
    {
        if (!validate_char(tmp[i], map_keys))
            return (0);
		i++;
    }
    return (1);
}

/*
** reads from first line of map backwards and stores key
*/

int     make_mapkeys(t_mapkeys *map_keys, char *keys)
{
	int     i;

	i = ft_strlen(keys) - 1;
    	printf("keys: %s\n", keys);
    	printf("exit: %c\n", keys[i]);
    map_keys->exit = keys[i--];
		printf("entr: %c\n", keys[i]);
    map_keys->entr = keys[i--];
		printf("path: %c\n", keys[i]);
    map_keys->path = keys[i--];
		printf("empty: %c\n", keys[i]);
    map_keys->empty = keys[i--];
		printf("fill: %c\n", keys[i]);
    map_keys->fill = keys[i--];

    return (1);
}

/*
** Checks first line and inits mapkeys
*/

int		validate_map_keys(int fd, t_mapkeys *map_keys, char ***map)
{
    char		*tmp;
	t_mapsize	map_dimensions;

	if (get_next_line(fd, &tmp) == -1)
        return (0);
    make_mapkeys(map_keys, tmp);
	get_mapsize(&map_dimensions, tmp);
    while (get_next_line(fd, &tmp) == 1)
    {
        if (!validate_line(tmp, map_keys))
			return (0);
//        printf("tmp: %s\n", tmp);
        if (ft_strlen(tmp) > map_dimensions.x)
            return (0);
		if (!build_map(map_dimensions, tmp, map_keys))
    		return (0);
	}
	free(tmp);
	return (1);
}

/*
** Base function
*/
int     validate(int fd)
{
	int			i;
	int			j;
	char		**map;
	t_mapkeys	map_keys;
	char		*line;
	char		*tmp;

	if (!validate_map_keys(fd, &map_keys, &map))
		return (0);
	return (1);
}

