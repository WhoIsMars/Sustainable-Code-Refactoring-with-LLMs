#include "saddle_points.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

saddle_points_t *saddle_points(size_t row_num, size_t col_num, const void *matrix)
{
    const uint8_t *matrix_p = (const uint8_t *)matrix;

    saddle_point_t *points_temp = (saddle_point_t *)malloc(row_num * col_num * sizeof(saddle_point_t));
    if (!points_temp) return NULL;

    size_t count = 0;

    for (size_t i = 0; i < row_num; ++i)
    {
        uint8_t max_val = 0;
        size_t max_col_index = 0;

        // Find the maximum value in the current row and its column index
        for (size_t j = 0; j < col_num; ++j)
        {
            uint8_t current_val = matrix_p[i * col_num + j];
            if (j == 0 || current_val >= max_val)
            {
                max_val = current_val;
                max_col_index = j;
            }
        }

        // Check if the maximum value in the row is also the minimum in its column
        uint8_t min_in_col = max_val;
        for (size_t k = 0; k < row_num; ++k)
        {
            uint8_t current_val = matrix_p[k * col_num + max_col_index];
            if (current_val < min_in_col)
            {
                min_in_col = current_val;
            }
        }

        // If the maximum value in the row is also the minimum in its column, it's a saddle point
        if (max_val == min_in_col)
        {
            points_temp[count].row = i + 1;
            points_temp[count].column = max_col_index + 1;
            count++;
        }
    }

    saddle_points_t *points = (saddle_points_t *)malloc(sizeof(saddle_points_t));
    if (NULL == points)
    {
        free(points_temp);
        return NULL;
    }

    points->points = (saddle_point_t *)malloc(count * sizeof(saddle_point_t));
    if (points->points == NULL) {
        free(points_temp);
        free(points);
        return NULL;
    }

    memcpy(points->points, points_temp, count * sizeof(saddle_point_t));
    free(points_temp);
    points->count = count;

    return points;
}

void free_saddle_points(saddle_points_t *points)
{
    if (points) {
        free(points->points);
        free(points);
    }
}