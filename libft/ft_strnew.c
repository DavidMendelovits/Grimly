/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:21:14 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/10 13:23:25 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char		*str;

	if (!(str = (char *)malloc(size + 1)))
	{
		return (NULL);
	}
	ft_bzero(str, size + 1);
	return (str);
}
