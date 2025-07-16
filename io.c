/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emurbane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:45:52 by emurbane          #+#    #+#             */
/*   Updated: 2025/07/16 21:15:25 by emurbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUF_SIZE 10000
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "functions.h"
#include "point.h"

int		g_size_x;
int		g_size_y;
char	g_empty;
char	g_obsticle;
char	g_full;
int		g_i;
int		g_len;
char	*g_newbuf;
int		g_y;
int		g_pos;
int		*g_headerlen1;
int		g_columns;
int		g_headerlen;
int		g_fd;
int		g_bytes;
int		g_size;
char	*g_buf;
char	g_c;

static int	read_file_to_buffer(char *filename, char **buffer)
{
	g_fd = open(filename, O_RDONLY);
	g_i = 0;
	if (g_fd < 0)
		return (-1);
	g_size = 1024;
	g_len = 0;
	g_buf = malloc(g_size);
	if (!g_buf)
	{
		close(g_fd);
		return (-1);
	}
	while (read(g_fd, &g_c, 1) == 1)
	{
		if (g_len + 1 >= g_size)
			g_newbuf = malloc(g_size * 2);
		if (!g_newbuf)
		{
			free(g_buf);
			close(g_fd);
			return (-1);
		}
		while (g_i < g_len)
		{
			g_newbuf[g_i] = g_buf[g_i];
			g_i ++;
		}
		free(g_buf);
		g_buf = g_newbuf;
		g_size *= 2;
		g_buf[g_len++] = g_c;
	}
	g_buf[g_len] = '\0';
	*buffer = g_buf;
	close(g_fd);
	return (0);
}

static int	parse_map_header(char *buffer, int *lines,
		int *g_headerlen1, char *add_info)
{
	int		i;
	int		j;
	char	lines_str[16];

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	*g_headerlen1 = i;
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
	is_valid(add_info, lines, *g_headerlen1);
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

int	alloc_and_fill_row(point **row, char *buffer, int pos, rowinfo info)
{
	int		x;
	char	c;

	*row = malloc(sizeof(point) * info.columns);
	if (!(*row))
		return (-1);
	x = 0;
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

point	**readmap(char *filename)
{
	char	*buffer;
	char	add_info[3];
	int		lines;
	point	**map;
	rowinfo	info;

	g_y = 0;
	g_headerlen = 0;
	if (read_file_to_buffer(filename, &buffer) == -1)
		return (NULL);
	if (parse_map_header(buffer, &lines, &g_headerlen, add_info) == -1)
		return (NULL);
	g_size_y = lines;
	g_pos = g_headerlen + 1;
	g_columns = count_columns(buffer, g_pos);
	g_size_x = g_columns;
	map = malloc(sizeof(point *) * lines);
	if (!map)
		return (NULL);
	info.columns = g_columns;
	info.add_info = add_info;
	if (fill_map(map, buffer, g_pos, lines, g_columns, info) == -1)
		return (NULL);
	return (map);
}
