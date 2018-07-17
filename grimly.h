/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 20:11:42 by dmendelo          #+#    #+#             */
/*   Updated: 2018/07/17 00:12:11 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRIMLY_H
# define GRIMLY_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct  s_mapsize
{
    int             y;
    int             x;
}               t_mapsize;

typedef struct  s_mapkeys
{
    char            *entr;
    char            *exit;
    char            *path;
    char            *empty;
    char            *fill;
}               t_mapkeys;

typedef struct	s_node
{
	struct s_node	*east;
	struct s_node	*west;
	struct s_node	*north;
	struct s_node	*south;
	int		        path_to_source;
	int		        distance;
}               t_node;

typedef struct	s_entr
{
	struct s_node	*path;
}				t_entr;

typedef struct	s_exit
{
	int	    	    min_distance;
	struct s_node	*path;
}				t_exit;
	

int		validate(int fd);
int		validate_map_keys(int fd, t_mapkeys **map_keys);
int     validate_line(char **tmp, t_mapkeys **map_keys);
int     make_mapkeys(t_mapkeys ** map_keys, char *keys);
#endif
