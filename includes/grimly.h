/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:41:40 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/27 16:50:49 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRIMLY_H
# define GRIMLY_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <stdio.h>
# include "../libft/libft.h"

# define WOW() printf("->%s\n", __func__)
# define MAP_ERROR "MAP ERROR\n"

typedef struct	s_legend
{
	char			full;
	char			empty;
	char			path;
	char			start;
	char			end;
	int				height;
	int				width;
}				t_legend;

typedef struct	s_coordinate
{
	int				row;
	int				column;
}				t_coordinate;

typedef struct	s_list
{
	void			*data;
	size_t			size;
	struct s_list	*next;
}				t_list;

typedef struct	s_map
{
	char			**map;
	int				**distances;
	int				**parents;
	t_coordinate	*start;
	int				ends;
	int				steps;
}				t_map;

typedef enum
{
	NONE,
	UP,
	LEFT,
	RIGHT,
	DOWN
}	t_directions;

typedef void	(*t_terminate)(void *);

void			read_file(char *filename);
void			read_vallidate_map(int fd);
int				solve(t_map *map, t_legend *legend);
int				bfs(t_map **map, t_legend *legend);
int				check_neighbrs(t_list **queue, t_map **map, t_legend *l);
void			queue_neighbors(t_list **queue, t_map **map, t_legend *l, t_coordinate *p);
t_coordinate	write_neighbor(t_coordinate *parent, t_map **map, int dir);
int				is_empty(int row, int column, t_map **map, t_legend *l);
void			trace_path(t_coordinate *end, t_map **map, t_legend *legend);
void			write_coordinate(t_coordinate **point, int row, int column);
int				is_better_path(int **matrix, t_coordinate *path, t_coordinate *tmp, int dir);
int				is_inbounds(int row, int column, t_legend *l);
void			*pop(t_list **head);
void			print_coordinates(t_list *queue);
void			write_distance(t_coordinate *point, t_map **map, int i);
void			push_back(t_list **head, void *new_data, size_t size);
void			push(t_list **head, void *new_data, size_t size);
void			print_coordinate(t_coordinate *point);
int				**zero_matrix(int height, int width);
void			print_matrix(int **matrix, int height, int width);
t_map			*read_map(t_legend *legend, int fd);
void			extract_line(t_map **map, char *line, t_legend *legend);
int				validate_line(char *line, t_legend *legend);
t_legend		*read_first_line(int fd);
int				atoi_range(char *s, int begin, int end);
int				read_keys(t_legend **legend, char *line, int *p);
void			print_strings(char **strings, int p);
void			print_legend(t_legend *legend);
void			free_2d(char **ptrs);
void			free_map(t_map *map);
void			*write_error(char *err, size_t size);
void			print_solution(char **map, int steps, t_legend *l);
void			*terminate_object(void (*f)(void *content), void *ptr);
#endif
