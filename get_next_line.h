/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <dmendelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:47:09 by dmendelo          #+#    #+#             */
/*   Updated: 2018/07/16 20:17:00 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFF_SIZE 1024

# define NULLCHECK(x) if (!x) return (-1);

typedef struct	s_int
{
	int		i;
	int		ret;
}				t_int;

int				get_next_line(const int fd, char **line);
int				copy_until(char **dest, char *source, char c);
char			*concatenate_str(const char *buf, char *content);
char			*shift_overflow(char *content, int i);

#endif
