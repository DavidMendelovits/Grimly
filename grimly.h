/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:41:40 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/24 16:35:36 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <stdio.h>
#include "libft/libft.h"

typedef struct	s_legend
{
	char			full;
	char			empty;
	char			path;
	char			start;
	char			end;
	unsigned		height;
	unsigned		width;
}				t_legend;

typedef struct	s_coordinate
{
	int				row;
	int				column;
}				t_coordinate;

typedef struct s_list
{
	void			*data;
	size_t			size;
	struct s_list	*next;
}				t_list;


typedef struct	s_map
{
	char			**map;
	int				**visited;
	int				**distances;
	t_coordinate	*start;
	t_list			*end;
}				t_map;


