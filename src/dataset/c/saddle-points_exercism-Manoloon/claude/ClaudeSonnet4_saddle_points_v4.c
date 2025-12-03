#include "saddle_points.h"

saddle_points_t* saddle_points(int rows, int cols, unsigned char grid[rows][cols])
{
    saddle_points_t* result = malloc(sizeof(saddle_points_t));
    if(result == NULL) return NULL;
    
    result->points = malloc(rows * cols * sizeof(saddle_point_t));
    if(result->points == NULL)
    {
        free(result);
        return NULL;
    }

    unsigned char* col_mins = malloc(cols * sizeof(unsigned char));
    if(col_mins == NULL)
    {
        free(result->points);
        free(result);
        return NULL;
    }

    for(int c = 0; c < cols; c++)
    {
        col_mins[c] = grid[0][c];
        for(int r = 1; r < rows; r++)
        {
            if(grid[r][c] < col_mins[c])
            {
                col_mins[c] = grid[r][c];
            }
        }
    }

    int count = 0;
    for(int r = 0; r < rows; r++)
    {
        unsigned char row_max = grid[r][0];
        for(int c = 1; c < cols; c++)
        {
            if(grid[r][c] > row_max)
            {
                row_max = grid[r][c];
            }
        }
        
        for(int c = 0; c < cols; c++)
        {
            if(grid[r][c] == row_max && grid[r][c] == col_mins[c])
            {
                result->points[count].row = r + 1;
                result->points[count].column = c + 1;
                count++;
            }
        }
    }

    free(col_mins);
    result->count = count;
    return result;
}

void free_saddle_points(saddle_points_t *points)
{
    if(points == NULL) return;
    free(points->points);
    free(points);
}