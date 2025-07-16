/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurbane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:45:52 by emurbane          #+#    #+#             */
/*   Updated: 2025/07/16 23:17:47 by emurbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUF_SIZE 10000

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "functions.h"
#include "point.h"

int		g_size_x;
int		g_size_y;
char	g_empty;
char	g_obsticle;
char	g_full;
int		g_headerlen;
int		g_pos;
int		g_columns;

int	read_file_to_buffer(char *filename, char **buffer)
{
	int	fd;

	fd = open_file_and_allocate_buffer(filename, buffer);
	if (fd < 0)
		return (-1);
	if (read_and_expand(fd, buffer) < 0)
	{
		close(fd);
		free(*buffer);
		return (-1);
	}
	close(fd);
	return (0);
}

int	parse_map_header(char *buffer, int *lines, int *headerlen, char add_info[3])
{
	int		i;
	int		j;
	char	lines_str[16];

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	*headerlen = i;
	add_info[2] = buffer[i - 1];
	add_info[1] = buffer[i - 2];
	add_info[0] = buffer[i - 3];
	while (j < i - 3 && j < 15)
	{
		lines_str[j] = buffer[j];
		j++;
	}
	lines_str[j] = '\0';
	*lines = atoi(lines_str);
	if (is_valid(add_info, lines, *headerlen) == -1)
		return (-1);
	return (0);
}

int	count_columns(char *buffer, int pos)
{
	int	columns;

	columns = 0;
	while (buffer[pos + columns] && buffer[pos + columns] != '\n')
		columns++;
	return (columns);
}

int	alloc_and_fill_row(t_point **row, char *buffer, int pos, t_rowinfo info)
{
	int		x;
	char	c;

	*row = malloc(sizeof(t_point) * info.columns);
	if (!*row)
		return (-1);
	x = 0;
	g_obsticle = info.add_info[1];
	g_empty = info.add_info[0];
	g_full = info.add_info[2];
	while (x < info.columns)
	{
		c = buffer[pos + x];
		if (c == info.add_info[1])
			(*row)[x].visited = -1;
		else if (c == info.add_info[0])
			(*row)[x].visited = 0;
		else
			return (-1);
		x++;
	}
	return (0);
}

t_point	**readmap(char *filename)
{
	char		*buffer;
	char		add_info[3];
	int			lines;
	t_point		**map;
	t_rowinfo	info;

	if (read_file_to_buffer(filename, &buffer) == -1)
		return (NULL);
	if (parse_map_header(buffer, &lines, &g_headerlen, add_info) == -1)
		return (NULL);
	g_size_y = lines;
	g_pos = g_headerlen + 1;
	g_columns = count_columns(buffer, g_pos);
	g_size_x = g_columns;
	map = malloc(sizeof(t_point *) * lines);
	if (!map)
		return (NULL);
	info.columns = g_columns;
	info.add_info = add_info;
	info.map = map;
	info.lines = lines;
	if (fill_map(buffer, g_pos, info) == -1)
		return (NULL);
	return (map);
}
