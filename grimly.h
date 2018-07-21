/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 20:11:42 by dmendelo          #+#    #+#             */
/*   Updated: 2018/07/20 17:56:32 by dmendelo         ###   ########.fr       */
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
    char            entr;
    char            exit;
    char            path;
    char            empty;
    char            fill;
}               t_mapkeys;

typedef struct	s_vertex
{
	int				path;
	int				distance;
	struct s_vertex **children;
	struct s_vertex *parent;
}				t_vertex;

typedef struct	s_graph
{
	int				num_vertices;
	struct s_vertex **graph;
}				t_graph;
	
/* on hold
typedef struct	s_node
{
	struct s_node	*right;
	struct s_node	*left;
	struct s_node	*up;
	struct s_node	*down;
	int		        path_to_source;
    struct s_node   *path2source;
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
*/	

int		validate(int fd);
int		validate_map_keys(int fd, t_mapkeys *map_keys, char ***map);
int     validate_line(char *tmp, t_mapkeys *map_keys);
int		validate_char(char c, t_mapkeys *map_keys);
int     make_mapkeys(t_mapkeys *map_keys, char *keys);
int		get_mapsize(t_mapsize *dimensions, char *tmp);
int		build_map(t_mapsize dim, char *tmp, t_mapkeys *keys, char ***map);

#endif
