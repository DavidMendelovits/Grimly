/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_range.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:19:36 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/26 16:19:44 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int				atoi_range(char *s, int begin, int end)
{
	char			*tmp;
	int				num;

	tmp = ft_strdup_range(s, begin, end);
	num = atoi(tmp);
	free(tmp);
	return (num);
}
