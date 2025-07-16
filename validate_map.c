#include "point.h"
#include <unistd.h>
#include "functions.h"

int    is_valid(char *add_info, int *lines, int header_len)
{
    if (add_info[0] < 32 || add_info[0] > 126 ||
        add_info[1] < 32 || add_info[1] > 126 ||
        add_info[2] < 32 || add_info[2] > 126)
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

int fill_map(point **map, char *buffer, int pos, int lines, int columns, rowinfo info)
{
    int y;

    y = 0;
    while (y < lines)
    {
        if (count_columns(buffer, pos) != columns)
        {
            write(1, "map error\n", 10);
            return (-1);
        }
        if (alloc_and_fill_row(&map[y], buffer, pos, info) == -1)
            return (-1);
        pos += columns;
        if (buffer[pos] == '\n')
            pos++;
        y++;
    }
    return (0);
}