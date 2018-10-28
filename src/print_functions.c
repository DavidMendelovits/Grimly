/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:08:01 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/27 21:48:04 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

void			print_2d(char **s)
{
	int						p;

	p = 0;
	while (s[p])
	{
		ft_putstr(s[p]);
		ft_putstr("\n");
		p += 1;
	}
}

void			print_solution(char **map, int steps, t_legend *l)
{
	ft_putnbr_base((unsigned long long)l->height, 10);
	ft_putchar('x');
	ft_putnbr_base((unsigned long long)l->width, 10);
	ft_putchar(l->full);
	ft_putchar(l->empty);
	ft_putchar(l->path);
	ft_putchar(l->start);
	ft_putchar(l->end);
	write(1, "\n", 1);
	print_2d(map);
	ft_putstr("RESULT IN ");
	ft_putnbr_base((unsigned long long)steps, 10);
	ft_putstr(" STEPS!\n");
}

void			*write_error(char *err, size_t size)
{
	write(2, err, size);
	return (NULL);
}
