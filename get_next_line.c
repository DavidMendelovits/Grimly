/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 09:10:16 by dmendelo          #+#    #+#             */
/*   Updated: 2018/07/18 18:00:10 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./libft/libft.h"
#include "grimly.h"

int				copy_until(char **dest, char *source, char c)
{
	int		i;
	int		count;
	int		pos;
	char	*tmp;

	i = -1;
	count = 0;
	while (source[++i])
		if (source[i] == c)
			break ;
	pos = i;
	while (source[count] && count < i)
	{
		tmp = ft_strjoinch(*dest, source[count]);
		free(*dest);
		*dest = tmp;
		if (!dest)
			return (0);
		count++;
	}
	return (pos);
}

static t_gnl	*find_in_rolodex(t_gnl **file, int fd)
{
	t_gnl		*temp;

	temp = *file;
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	temp = (t_gnl *)malloc(sizeof(t_list));
	temp->content = ft_strnew(1);
	temp->fd = fd;
	ft_fd_lstadd(file, temp);
	temp = *file;
	return (temp);
}

char			*concatenate_str(const char *buf, char *content)
{
	char		*temp;
	char		*trash;

	trash = content;
	temp = ft_strjoin(content, buf);
	free(trash);
	return (temp);
}

char			*shift_overflow(char *content, int i)
{
	char	*temp;
	char	*trash;
	char	*empty;

	temp = ft_strnew(1);
	empty = temp;
	temp = ft_strjoin(empty, content);
	content -= (i + 1);
	trash = content;
	free(trash);
	free(empty);
	return (temp);
}

int				get_next_line(const int fd, char **line)
{
	t_int			var;
	static t_gnl	*file;
	t_gnl			*current;
	char			buf[BUFF_SIZE + 1];
	char			*temp;

	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	current = find_in_rolodex(&file, fd);
	*line = ft_strnew(1);
	while ((var.ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[var.ret] = '\0';
		temp = current->content;
		NULLCHECK((current->content = concatenate_str(buf, temp)));
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (var.ret < BUFF_SIZE && !ft_strlen(current->content))
		return (0);
	var.i = copy_until(line, current->content, '\n');
	(var.i < (int)ft_strlen(current->content))
	? current->content = shift_overflow(&current->content[var.i + 1], var.i)
	: ft_strclr(current->content);
	return (1);
}
