/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algoritm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurbane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:39:34 by emurbane          #+#    #+#             */
/*   Updated: 2025/07/16 19:39:38 by emurbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "functions.h"
#include "point.h"

int	g_size;
int	g_dist_x;
int	g_dist_y;

void	loops(point **tab)
{
	int	i;
	int	j;
	int	current;

	i = 0;
	while (i < g_size_y)
	{
		j = 0;
		while (j < g_size_x)
		{
			if (tab[i][j].visited != -1)
			{
				//printf("loop %d - %d\n", i, j);
				find_square(j, i, tab);
			}
			j++;
		}
		i++;
	}
}

void	give_value(point **tab, int index_x, int index_y, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < x)
		{
			if (tab[j + index_y][i + index_x].visited < x)
				tab[j + index_y][i + index_x].visited = x;
			j++;
		}
		i++;
	}
	if (x > g_size || (x == g_size && index_x < g_dist_x)
		|| (x == g_size && index_x == g_dist_x && index_y < g_dist_y))
	{
		//printf("x = %d, dist x = %d, dist y = %d\n", x, index_x, index_y);
		g_size = x;
		g_dist_x = index_x;
		g_dist_y = index_y;
	}
}

void	find_square(int index_x, int index_y, point **tab)
{
	int	y_min;
	int	x;
	int	i;
	int	j;

	x = 0;
	y_min = 1000000000;
	while (x < y_min && (x + index_x) < g_size_x
		&& tab[index_y][index_x + x].visited != -1)
	{
		if (tab[index_y][index_x + x].obs_y < y_min)
			y_min = tab[index_y][index_x + x].obs_y;
		x++;
	}
	if (y_min < x)
		x--;
	give_value(tab, index_x, index_y, x);
}

void	print_board(point **tab)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_size_y)
	{
		j = 0;
		while (j < g_size_x)
		{
			if (tab[i][j].visited == g_size && i < g_dist_y + g_size &&
					i >= g_dist_y && j < g_dist_x + g_size && j >= g_dist_x)
				write(1, "x", 1);
			else if (tab[i][j].visited == -1)
				write(1, "o", 1);
			else if (tab[i][j].visited >= 0)
				write(1, ".", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	find_main(point **tab)
{
	g_size = 0;
	g_dist_x = 0;
	g_dist_y = 0;
	find_obs(tab);
	loops(tab);
	printf("x = %d, dist x = %d, dist y =%d\n", g_size, g_dist_x, g_dist_y);
	// for (int i = 0; i < g_size_y; i++){
	// 	for(int j = 0; j < g_size_x; j++)
	// 		printf("%d ", tab[i][j].visited);
	// 	printf("\n");
	// }
	// printf("full = %c, empty = %c, obsticle = %c\n",
	// 	g_full, g_empty, g_obsticle);
	print_board(tab);
}
