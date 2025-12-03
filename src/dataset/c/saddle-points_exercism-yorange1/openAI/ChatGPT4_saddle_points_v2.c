#include "saddle_points.h"

#include <stdlib.h>
#include <string.h>

static void find_max_row(size_t row_num, size_t col_num, const uint8_t *matrix_p, uint8_t *max_row_values)
{
    for (size_t i = 0; i < row_num; i++)
    {
        uint8_t max = matrix_p[i * col_num];
        for (size_t j = 1; j < col_num; j++)
        {
            if (matrix_p[i * col_num + j] > max)
            {
                max = matrix_p[i * col_num + j];
            }
        }
        max_row_values[i] = max;
    }
}

static void find_min_col(size_t row_num, size_t col_num, const uint8_t *matrix_p, uint8_t *min_col_values)
{
    for (size_t i = 0; i < col_num; i++)
    {
        uint8_t min = matrix_p[i];
        for (size_t j = 1; j < row_num; j++)
        {
            if (matrix_p[j * col_num + i] < min)
            {
                min = matrix_p[j * col_num + i];
            }
        }
        min_col_values[i] = min;
    }
}

saddle_points_t *saddle_points(size_t row_num, size_t col_num, const void *matrix)
{
    if (row_num == 0 || col_num == 0)
    {
        saddle_points_t *points = (saddle_points_t *)calloc(1, sizeof(saddle_points_t));
        return points;
    }

    const uint8_t *matrix_p = (const uint8_t *)matrix;

    uint8_t *max_row_values = (uint8_t *)malloc(row_num * sizeof(uint8_t));
    uint8_t *min_col_values = (uint8_t *)malloc(col_num * sizeof(uint8_t));
    if (!max_row_values || !min_col_values)
    {
        free(max_row_values);
        free(min_col_values);
        return NULL;
    }

    find_max_row(row_num, col_num, matrix_p, max_row_values);
    find_min_col(row_num, col_num, matrix_p, min_col_values);

    uint8_t count = 0;
    saddle_point_t *points_temp = (saddle_point_t *)malloc(row_num * col_num * sizeof(saddle_point_t));
    if (!points_temp)
    {
        free(max_row_values);
        free(min_col_values);
        return NULL;
    }

    for (size_t i = 0; i < row_num; i++)
    {
        for (size_t j = 0; j < col_num; j++)
        {
            if (matrix_p[i * col_num + j] == max_row_values[i] && matrix_p[i * col_num + j] == min_col_values[j])
            {
                points_temp[count].row = i + 1;
                points_temp[count].column = j + 1;
                count++;
            }
        }
    }

    saddle_points_t *points = (saddle_points_t *)calloc(1, sizeof(saddle_points_t) + count * sizeof(saddle_point_t));
    if (points)
    {
        memcpy(points->points, points_temp, count * sizeof(saddle_point_t));
        points->count = count;
    }

    free(max_row_values);
    free(min_col_values);
    free(points_temp);

    return points;
}

void free_saddle_points(saddle_points_t *points)
{
    free(points);
}