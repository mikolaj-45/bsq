/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurbane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:21:18 by emurbane          #+#    #+#             */
/*   Updated: 2025/07/16 19:33:58 by emurbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		k;
	point	**map;

	k = 1;
	while (k < argc)
	{
		if (k != 1)
			write(1, "\n", 1);
		map = readmap(argv[k]);
		if (!map)
		{
			write(1, "map error\n", 10);
			k++;
			continue ;
		}
		printf("%d %d\n", g_size_x, g_size_y);
		print_map(map, g_size_x, g_size_y);
		printf("aaa\n");
		find_main(map);
		free_map(map, g_size_y);
		k++;
	}
    /*if (argc == 1)
    {
        
    }*/
}
