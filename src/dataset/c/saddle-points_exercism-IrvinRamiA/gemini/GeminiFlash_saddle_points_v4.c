#include "saddle_points.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

saddle_points_t *saddle_points(uint8_t rows, uint8_t cols, uint8_t matrix[rows][cols]) {
    saddle_point_t *points = (saddle_point_t *)malloc(rows * cols * sizeof(saddle_point_t));
    if (!points) return NULL;

    uint8_t total_saddle_points = 0;

    for (uint8_t i = 0; i < rows; i++) {
        for (uint8_t j = 0; j < cols; j++) {
            bool is_saddle_point = true;

            // Check if greater than or equal to all elements in the row
            for (uint8_t col_index = 0; col_index < cols; col_index++) {
                if (matrix[i][j] < matrix[i][col_index]) {
                    is_saddle_point = false;
                    break;
                }
            }

            if (!is_saddle_point) continue;

            // Check if less than or equal to all elements in the column
            for (uint8_t row_index = 0; row_index < rows; row_index++) {
                if (matrix[i][j] > matrix[row_index][j]) {
                    is_saddle_point = false;
                    break;
                }
            }

            if (is_saddle_point) {
                points[total_saddle_points].row = i + 1;
                points[total_saddle_points].column = j + 1;
                total_saddle_points++;
            }
        }
    }

    saddle_points_t *result = (saddle_points_t *)malloc(sizeof(saddle_points_t));
    if (!result) {
        free(points);
        return NULL;
    }

    result->points = (saddle_point_t *)malloc(total_saddle_points * sizeof(saddle_point_t));
    if (!result->points) {
        free(points);
        free(result);
        return NULL;
    }

    result->count = total_saddle_points;
    memcpy(result->points, points, total_saddle_points * sizeof(saddle_point_t));
    free(points);

    return result;
}

void free_saddle_points(saddle_points_t *result) {
    if (result) {
        free(result->points);
        free(result);
    }
}