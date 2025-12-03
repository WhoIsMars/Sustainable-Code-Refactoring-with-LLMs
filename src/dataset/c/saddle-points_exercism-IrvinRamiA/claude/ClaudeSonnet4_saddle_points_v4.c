#include "saddle_points.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

saddle_points_t *saddle_points(uint8_t rows, uint8_t cols, uint8_t matrix[rows][cols])
{
    if (rows == 0 || cols == 0) {
        saddle_points_t *result = malloc(sizeof(saddle_points_t));
        result->count = 0;
        result->points = NULL;
        return result;
    }

    uint8_t *row_max = malloc(rows * sizeof(uint8_t));
    uint8_t *col_min = malloc(cols * sizeof(uint8_t));
    
    for (uint8_t i = 0; i < rows; i++) {
        row_max[i] = matrix[i][0];
        for (uint8_t j = 1; j < cols; j++) {
            if (matrix[i][j] > row_max[i]) {
                row_max[i] = matrix[i][j];
            }
        }
    }
    
    for (uint8_t j = 0; j < cols; j++) {
        col_min[j] = matrix[0][j];
        for (uint8_t i = 1; i < rows; i++) {
            if (matrix[i][j] < col_min[j]) {
                col_min[j] = matrix[i][j];
            }
        }
    }
    
    saddle_point_t points[10];
    uint8_t total_saddle_points = 0;
    
    for (uint8_t i = 0; i < rows && total_saddle_points < 10; i++) {
        for (uint8_t j = 0; j < cols && total_saddle_points < 10; j++) {
            if (matrix[i][j] == row_max[i] && matrix[i][j] == col_min[j]) {
                points[total_saddle_points].row = i + 1;
                points[total_saddle_points].column = j + 1;
                total_saddle_points++;
            }
        }
    }
    
    free(row_max);
    free(col_min);
    
    saddle_points_t *result = malloc(sizeof(saddle_points_t));
    result->count = total_saddle_points;
    
    if (total_saddle_points > 0) {
        result->points = malloc(total_saddle_points * sizeof(saddle_point_t));
        memcpy(result->points, points, total_saddle_points * sizeof(saddle_point_t));
    } else {
        result->points = NULL;
    }
    
    return result;
}

void free_saddle_points(saddle_points_t *result)
{
    if (result) {
        free(result->points);
        free(result);
    }
}