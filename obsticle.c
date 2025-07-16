#include <stdio.h>
#include "functions.h"
#include "point.h"

void	find_obs(point **t)
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
