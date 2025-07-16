/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obsticle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurbane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:03:03 by emurbane          #+#    #+#             */
/*   Updated: 2025/07/16 22:58:10 by emurbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "functions.h"
#include "point.h"

void	find_obs(t_point **t)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < g_size_y)
	{
		j = 0;
		while (j < g_size_x)
		{
			if (t[i][j].visited == -1)
				t[i][j].obs_y = -1;
			else
			{
				k = 1;
				while ((i + k) < g_size_y && t[i + k][j].visited != -1)
					k++;
				t[i][j].obs_y = k;
			}
			j++;
		}
		i++;
	}
}
