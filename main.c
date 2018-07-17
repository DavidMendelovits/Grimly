/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 18:07:00 by dmendelo          #+#    #+#             */
/*   Updated: 2018/07/16 23:05:14 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"
#include "get_next_line.h"

int		main(int argc, char **argv)
{
	int		i;
	int		fd;

	if (argc < 2)
	{
		write(2, "Not enough arguments.\n", 22);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		fd = open(argv[i++], O_RDONLY);
		if (!validate(fd))
			write(2, "Invalid Map\n", 12);
		close(fd);
	}
	return (0);
}
