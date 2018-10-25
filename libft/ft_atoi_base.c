/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 12:04:50 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/04 12:09:00 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				get_num(char c, char *base)
{
	int			i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
		{
			return (i);
		}
		i += 1;
	}
	return (-1);
}

int						ft_atoi_base(char *_int, char *base)
{
	int			p;
	int			i;
	int			radix;
	int			sign;
	int			place;

	radix = ft_strlen(base);
	p = ft_strlen(_int) - 1;
	i = 0;
	place = 1;
	sign = 1;
	if (_int[0] == '-')
	{
		sign = -1;
	}
	while (p >= 0)
	{
		if (p == 0 && _int[p] == '-')
			break ;
		i += get_num(_int[p], base) * place;
		p -= 1;
		place *= radix;
	}
	return (i * sign);
}
