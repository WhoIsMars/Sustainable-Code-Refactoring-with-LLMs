#include "saddle_points.h"

#include <stdlib.h>
#include <string.h>

static uint8_t max_row(size_t row, size_t col_num, const uint8_t *matrix_p)
{
    uint8_t max = matrix_p[row * col_num];
    const uint8_t *row_start = matrix_p + row * col_num;

    for (size_t i = 1; i < col_num; i++)
    {
        if (row_start[i] > max)
        {
            max = row_start[i];
        }
    }

    return max;
}

static uint8_t min_col(size_t col, size_t row_num, size_t col_num, const uint8_t *matrix_p)
{
    uint8_t min = matrix_p[col];

    for (size_t i = 1; i < row_num; i++)
    {
        uint8_t val = matrix_p[i * col_num + col];
        if (val < min)
        {
            min = val;
        }
    }

    return min;
}

saddle_points_t *saddle_points(size_t row_num, size_t col_num, const void *matrix)
{
    if (row_num == 0 || col_num == 0)
    {
        saddle_points_t *points = (saddle_points_t *)calloc(1, sizeof(saddle_points_t));
        return points;
    }

    const uint8_t *matrix_p = (const uint8_t *)matrix;
    uint8_t *row_max_flags = (uint8_t *)calloc(row_num * col_num, sizeof(uint8_t));
    if (!row_max_flags)
    {
        return NULL;
    }

    for (size_t i = 0; i < row_num; i++)
    {
        uint8_t max = max_row(i, col_num, matrix_p);
        for (size_t j = 0; j < col_num; j++)
        {
            if (matrix_p[i * col_num + j] == max)
            {
                row_max_flags[i * col_num + j] = 1;
            }
        }
    }

    uint8_t count = 0;
    saddle_point_t *points_temp = (saddle_point_t *)malloc(row_num * col_num * sizeof(saddle_point_t));
    if (!points_temp)
    {
        free(row_max_flags);
        return NULL;
    }

    for (size_t i = 0; i < col_num; i++)
    {
        uint8_t min = min_col(i, row_num, col_num, matrix_p);
        for (size_t j = 0; j < row_num; j++)
        {
            if (matrix_p[j * col_num + i] == min && row_max_flags[j * col_num + i] == 1)
            {
                points_temp[count].row = j + 1;
                points_temp[count].column = i + 1;
                count++;
            }
        }
    }

    free(row_max_flags);

    saddle_points_t *points = (saddle_points_t *)calloc(1, sizeof(saddle_points_t) + count * sizeof(saddle_point_t));
    if (!points)
    {
        free(points_temp);
        return NULL;
    }

    memcpy(points->points, points_temp, count * sizeof(saddle_point_t));
    points->count = count;

    free(points_temp);
    return points;
}

void free_saddle_points(saddle_points_t *points)
{
    free(points);
}