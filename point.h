#ifndef POINT_H
#define POINT_H

typedef struct point
{
    int obs_y;
    int visited;
} point;

typedef struct s_rowinfo {
    int columns;
    char *add_info;
} rowinfo;

#endif