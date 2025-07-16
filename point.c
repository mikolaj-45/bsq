#include <stdlib.h>
#include "functions.h"
#include "point.h"

void free_map(point **map, int lines)
{
    int i = 0;
    if (!map) return;
    while (i < lines && map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

void print_map(point **map, int size_x, int size_y)
{
    int i;
    int j;

    i = 0;
    while (i < size_y)
    {
        j = 0;
        while (j < size_x)
        {
            if (map[i][j].visited == -1)
                write(1, "o", 1);
            else
                write(1, ".", 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
}