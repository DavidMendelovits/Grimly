/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 20:17:46 by dmendelo          #+#    #+#             */
/*   Updated: 2018/07/16 23:26:16 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"
#include "get_next_line.h"

int     validate(int fd)
{
	int			i;
	int			j;
	t_mapkeys	*map_keys;
	char		*line;
	char		*tmp;

	if (!validate_map_keys(fd, &map_keys))
		return (0);
	return (1);
}

int     make_mapkeys(t_mapkeys **map_keys, char *keys)
{
    int     i;
//    char    *map_height;
    char    *map_width;

    map_keys = malloc(sizeof(t_mapkeys));
    i = ft_strlen(keys) - 1;
    map_width = (char*)malloc(sizeof(char) * (i - 5));
    printf("keys: %s\n", keys);
    printf("key[i]: %c\n", keys[i]);
    (*map_keys)->exit = &keys[i--];
    printf("key[i]: %c\n", keys[i]);
    (*map_keys)->entr = &keys[i--];
    (*map_keys)->path = &keys[i--];
    (*map_keys)->empty = &keys[i--];
    (*map_keys)->fill = &keys[i--];
    while (keys[i] != 'x')
    {
       *map_width++ = keys[i--];
    }
    *map_width = '\0';
    return (1);
}
int     validate_line(char **tmp, t_mapkeys **map_keys)
{
    int     i;

    i = 0;
    while (i <= ft_strlen(*tmp))
    {
        if (tmp[i] != (*map_keys)->entr || tmp[i] != (*map_keys)->exit ||
            tmp[i] != (*map_keys)->path || tmp[i] != (*map_keys)->fill ||
            tmp[i] != (*map_keys)->empty)
            return (-1);
    }
    return (1);
}

int		validate_map_keys(int fd, t_mapkeys **map_keys)
{
	char	*tmp;

	if (get_next_line(fd, &tmp) == -1)
        return (-1);
//	printf("map_keys: %s\n", tmp);
    make_mapkeys(map_keys, tmp);
    while (get_next_line(fd, &tmp) == 1)
    {
        validate_line(&tmp, map_keys);
        printf("tmp: %s\n", tmp);
    }
	free(tmp);
	return (1);
}
