/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 15:14:34 by dmendelo          #+#    #+#             */
/*   Updated: 2018/07/18 20:12:06 by dmendelo         ###   ########.fr       */
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
//	printf("variables passed to f_strncpy: _len: %s[%i] tmp: %s i: %i\n", _len, (i + 1), tmp, i); 
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

char	*f_strncpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}


