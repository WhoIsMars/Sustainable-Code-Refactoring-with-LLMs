#include "saddle_points.h"
#include <stdbool.h>
#include <stdlib.h>

saddle_points_t *saddle_points(uint8_t rows, uint8_t cols, uint8_t matrix[rows][cols]) {
    saddle_point_t *points = NULL;
    uint8_t total_saddle_points = 0;

    // Dynamically allocate memory for saddle points. Start with a small size and reallocate if needed.
    size_t points_capacity = 2;
    points = (saddle_point_t *)malloc(points_capacity * sizeof(saddle_point_t));
    if (!points) return NULL; // Handle allocation failure

    for (uint8_t i = 0; i < rows; i++) {
        for (uint8_t j = 0; j < cols; j++) {
            bool is_saddle_point = true;

            // Check if matrix[i][j] is the greatest in its row
            for (uint8_t col_index = 0; col_index < cols; col_index++) {
                if (matrix[i][j] < matrix[i][col_index]) {
                    is_saddle_point = false;
                    break;
                }
            }

            if (is_saddle_point) {
                // Check if matrix[i][j] is the smallest in its column
                for (uint8_t row_index = 0; row_index < rows; row_index++) {
                    if (matrix[i][j] > matrix[row_index][j]) {
                        is_saddle_point = false;
                        break;
                    }
                }
            }

            if (is_saddle_point) {
                // Add the saddle point to the array
                if (total_saddle_points >= points_capacity) {
                    points_capacity *= 2;
                    saddle_point_t *temp = (saddle_point_t *)realloc(points, points_capacity * sizeof(saddle_point_t));
                    if (!temp) {
                        free(points);
                        return NULL; // Handle reallocation failure
                    }
                    points = temp;
                }
                points[total_saddle_points].row = i + 1;
                points[total_saddle_points].column = j + 1;
                total_saddle_points++;
            }
        }
    }

    saddle_points_t *result = (saddle_points_t *)malloc(sizeof(saddle_points_t));
    if (!result) {
        free(points);
        return NULL; // Handle allocation failure
    }

    // Allocate only the required memory for the saddle points
    result->points = (saddle_point_t *)malloc(total_saddle_points * sizeof(saddle_point_t));
    if (!result->points) {
        free(points);
        free(result);
        return NULL; // Handle allocation failure
    }

    result->count = total_saddle_points;

    // Copy the saddle points to the result
    for (uint8_t i = 0; i < total_saddle_points; i++) {
        result->points[i] = points[i];
    }

    free(points); // Free the temporary array

    return result;
}

void free_saddle_points(saddle_points_t *result) {
    if (result) {
        free(result->points);
        free(result);
    }
}