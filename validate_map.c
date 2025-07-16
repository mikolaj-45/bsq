/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurbane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:00:00 by emurbane          #+#    #+#             */
/*   Updated: 2025/07/16 22:00:00 by emurbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "point.h"
#include "functions.h"

int	is_valid(char *add_info, int *lines, int header_len)
{
	if (add_info[0] < 32 || add_info[0] > 126
		|| add_info[1] < 32 || add_info[1] > 126
		|| add_info[2] < 32 || add_info[2] > 126)
	{
		write(1, "map error\n", 10);
		return (-1);
	}
	if (*lines <= 0)
	{
		write(1, "map error\n", 10);
		return (-1);
	}
	if (header_len < 4)
	{
		write(1, "map error\n", 10);
		return (-1);
	}
	return (0);
}

int	fill_map(char *buffer, int pos, rowinfo info)
{
	int	y;

	y = 0;
	while (y < info.lines)
	{
		if (count_columns(buffer, pos) != info.columns)
		{
			write(1, "map error\n", 10);
			return (-1);
		}
		if (alloc_and_fill_row(&info.map[y], buffer, pos, info) == -1)
			return (-1);
		pos += info.columns;
		if (buffer[pos] == '\n')
			pos++;
		y++;
	}
	return (0);
}
