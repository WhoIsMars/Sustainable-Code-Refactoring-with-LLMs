#include "saddle_points.h"

#include <stdlib.h>
#include <string.h>

saddle_points_t *saddle_points(size_t row_num, size_t col_num, const void *matrix)
{
    if (row_num == 0 || col_num == 0 || matrix == NULL) {
        return NULL;
    }

    const uint8_t *matrix_p = (const uint8_t *)matrix;
    
    uint8_t *row_max = (uint8_t *)malloc(row_num * sizeof(uint8_t));
    uint8_t *col_min = (uint8_t *)malloc(col_num * sizeof(uint8_t));
    
    if (!row_max || !col_min) {
        free(row_max);
        free(col_min);
        return NULL;
    }

    for (size_t i = 0; i < row_num; i++) {
        row_max[i] = matrix_p[i * col_num];
        for (size_t j = 1; j < col_num; j++) {
            uint8_t val = matrix_p[i * col_num + j];
            if (val > row_max[i]) {
                row_max[i] = val;
            }
        }
    }

    for (size_t j = 0; j < col_num; j++) {
        col_min[j] = matrix_p[j];
        for (size_t i = 1; i < row_num; i++) {
            uint8_t val = matrix_p[i * col_num + j];
            if (val < col_min[j]) {
                col_min[j] = val;
            }
        }
    }

    size_t count = 0;
    for (size_t i = 0; i < row_num; i++) {
        for (size_t j = 0; j < col_num; j++) {
            uint8_t val = matrix_p[i * col_num + j];
            if (val == row_max[i] && val == col_min[j]) {
                count++;
            }
        }
    }

    saddle_points_t *points = (saddle_points_t *)calloc(1, sizeof(saddle_points_t) + count * sizeof(saddle_point_t));
    if (!points) {
        free(row_max);
        free(col_min);
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < row_num; i++) {
        for (size_t j = 0; j < col_num; j++) {
            uint8_t val = matrix_p[i * col_num + j];
            if (val == row_max[i] && val == col_min[j]) {
                points->points[idx].row = i + 1;
                points->points[idx].column = j + 1;
                idx++;
            }
        }
    }

    points->count = count;
    
    free(row_max);
    free(col_min);
    
    return points;
}

void free_saddle_points(saddle_points_t *points)
{
    free(points);
}