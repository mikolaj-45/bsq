/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurbane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:03:20 by emurbane          #+#    #+#             */
/*   Updated: 2025/07/16 22:03:23 by emurbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "functions.h"
#include "point.h"

void	free_map(t_point **map, int lines)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < lines && map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	print_map(t_point **map, int size_x, int size_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < size_y)
	{
		j = 0;
		while (j < size_x)
		{
			if (map[i][j].visited == -1)
				write(1, &g_obsticle, 1);
			else
				write(1, &g_empty, 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
