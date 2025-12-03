#include "saddle_points.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

saddle_points_t *saddle_points(size_t row_num, size_t col_num, const void *matrix) {
    const uint8_t *matrix_p = (const uint8_t *)matrix;

    saddle_point_t *points_temp = (saddle_point_t *)malloc(row_num * col_num * sizeof(saddle_point_t));
    if (points_temp == NULL) {
        return NULL;
    }

    size_t count = 0;

    for (size_t i = 0; i < row_num; ++i) {
        uint8_t row_max = 0;
        size_t col_index_max = 0;

        // Find the maximum value in the current row and its column index
        row_max = matrix_p[i * col_num];
        col_index_max = 0;
        for (size_t j = 1; j < col_num; ++j) {
            if (matrix_p[i * col_num + j] > row_max) {
                row_max = matrix_p[i * col_num + j];
                col_index_max = j;
            }
        }

        // Check if the maximum value in the row is also the minimum in its column
        uint8_t col_min = matrix_p[col_index_max];
        for (size_t k = 0; k < row_num; ++k) {
            if (matrix_p[k * col_num + col_index_max] < col_min) {
                col_min = matrix_p[k * col_num + col_index_max];
                break; // No need to continue if a smaller value is found
            }
        }

        // If the row maximum is also the column minimum, it's a saddle point
        if (row_max == col_min) {
            points_temp[count].row = i + 1;
            points_temp[count].column = col_index_max + 1;
            count++;
        }
    }

    // Allocate memory for the saddle points structure
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
    free(points_temp); // Free temporary array
    points->count = count;

    return points;
}

void free_saddle_points(saddle_points_t *points) {
    if (points) {
        free(points->points);
        free(points);
    }
}