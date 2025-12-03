#ifndef SADDLE_POINTS_H
#define SADDLE_POINTS_H
#include <stdlib.h>
#include <stdint.h>

typedef struct saddle_point_t
{
    int row,column;
}saddle_point_t;

typedef struct saddle_points_t
{
    saddle_point_t* points;
    int count;
}saddle_points_t;

saddle_points_t* saddle_points(int rows, int cols, unsigned char grid[rows][cols]);
void free_saddle_points(saddle_points_t* points);
#endif
