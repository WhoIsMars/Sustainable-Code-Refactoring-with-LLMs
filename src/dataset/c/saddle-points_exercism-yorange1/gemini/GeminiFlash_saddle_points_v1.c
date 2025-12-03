#include "saddle_points.h"

#include <stdlib.h>
#include <limits.h>

saddle_points_t *saddle_points(size_t row_num, size_t col_num, const void *matrix) {
    const uint8_t *matrix_p = (const uint8_t *)matrix;

    saddle_point_t *points_temp = (saddle_point_t *)malloc(row_num * col_num * sizeof(saddle_point_t));
    if (points_temp == NULL) {
        return NULL;
    }

    size_t count = 0;

    for (size_t i = 0; i < row_num; ++i) {
        uint8_t max_val = matrix_p[i * col_num];
        size_t max_col_index = 0;

        // Find the maximum value in the row and its column index
        for (size_t j = 1; j < col_num; ++j) {
            if (matrix_p[i * col_num + j] > max_val) {
                max_val = matrix_p[i * col_num + j];
                max_col_index = j;
            }
        }

        // Check if the maximum value is also the minimum in its column
        uint8_t min_val = matrix_p[max_col_index];
        bool is_saddle_point = true;

        for (size_t k = 0; k < row_num; ++k) {
            if (matrix_p[k * col_num + max_col_index] < max_val) {
                is_saddle_point = false;
                break;
            }
        }

        if (is_saddle_point) {
            points_temp[count].row = i + 1;
            points_temp[count].column = max_col_index + 1;
            count++;
        }
    }

    saddle_points_t *points = (saddle_points_t *)malloc(sizeof(saddle_points_t));
    if (points == NULL) {
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
    points->count = count;

    free(points_temp);
    return points;
}

void free_saddle_points(saddle_points_t *points) {
    if (points) {
        free(points->points);
        free(points);
    }
}