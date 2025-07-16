#define BUF_SIZE 10000
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "point.h"

int     g_size_x;
int     g_size_y;
char    g_empty;
char    g_obsticle;
char    g_full;


static int	read_terminal_to_buffer(char *argv, char *buffer)
{
	int fd;
	int bytes;

	fd = argv;
	if (fd < 0)
		return (-1);
	if (bytes < 0) {
		close(fd);
		return (-1);
	}
	buffer[bytes] = '\0';
	close(fd);
	return (0);
}

static int parse_map_header(char *buffer, int *lines, int *header_len, char *add_info)
{
    int i;
    int j;
    char lines_str[16];

    i = 0;
    j = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (i < 4)
        return (-1);
    *header_len = i;
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
    if (*lines <= 0)
        return (-1);
    return (0);
}

static int count_columns(char *buffer, int pos)
{
    int columns;

	columns = 0;
    while (buffer[pos + columns] && buffer[pos + columns] != '\n')
        columns++;
    return (columns);
}

static int alloc_and_fill_row(point **row, char *buffer, int pos, rowinfo info)
{
    int x;
    char c;

    *row = malloc(sizeof(point) * info.columns);
    if (!(*row))
        return -1;
    x = 0;
    while (x < info.columns)
    {
        c = buffer[pos + x];
        if (c == info.add_info[1])
            (*row)[x].visited = -1;
        else if (c == info.add_info[0])
            (*row)[x].visited = 0;
        else
            return -1;
        x++;
    }
    return 0;
}

point **readmap(char *filename)
{
    char buffer[BUF_SIZE];
    char add_info[3];
    int lines;
    int header_len;

    if (read_file_to_buffer(filename, buffer) == -1)
        return (NULL);
    if (parse_map_header(buffer, &lines, &header_len, add_info) == -1)
        return (NULL);
    g_size_y = lines;
    int pos = header_len + 1;
    int columns = count_columns(buffer, pos);
    g_size_x = columns;
    point **map = malloc(sizeof(point *) * lines);
    if (!map)
        return (NULL);
    int y = 0;
    rowinfo info;
    info.columns = columns;
    info.add_info = add_info;

    while (y < lines)
    {
        if (count_columns(buffer, pos) != columns)
            return NULL;
        if (alloc_and_fill_row(&map[y], buffer, pos, info) == -1)
            return NULL;
        pos += columns;
        if (buffer[pos] == '\n')
            pos++;
        y++;
    }
    return (map);
}