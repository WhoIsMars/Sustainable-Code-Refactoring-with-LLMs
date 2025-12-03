#include "saddle_points.h"

saddle_points_t* saddle_points(int rows, int cols, unsigned char grid[rows][cols])
{
    saddle_points_t* result = malloc(sizeof(saddle_points_t));
    if (!result) return NULL;

    result->points = malloc(rows * cols * sizeof(saddle_point_t));
    if (!result->points)
    {
        free(result);
        return NULL;
    }

    int count = 0;
    unsigned char row_max[rows];
    unsigned char col_min[cols];

    // Precompute row max and column min
    for (int r = 0; r < rows; r++)
    {
        row_max[r] = grid[r][0];
        for (int c = 1; c < cols; c++)
        {
            if (grid[r][c] > row_max[r])
                row_max[r] = grid[r][c];
        }
    }

    for (int c = 0; c < cols; c++)
    {
        col_min[c] = grid[0][c];
        for (int r = 1; r < rows; r++)
        {
            if (grid[r][c] < col_min[c])
                col_min[c] = grid[r][c];
        }
    }

    // Find saddle points
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (grid[r][c] == row_max[r] && grid[r][c] == col_min[c])
            {
                result->points[count].row = r + 1;
                result->points[count].column = c + 1;
                count++;
            }
        }
    }

    result->count = count;
    return result;
}

void free_saddle_points(saddle_points_t *points)
{
    if (points)
    {
        free(points->points);
        free(points);
    }
}