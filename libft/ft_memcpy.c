/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 18:37:43 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/24 18:41:08 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;

	d = (unsigned char *)dest;
	while (n--)
	{
		*d++ = *((unsigned char *)src++);
	}
	return (dest);
}
