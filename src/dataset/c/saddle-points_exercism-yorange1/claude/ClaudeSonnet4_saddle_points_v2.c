#include "saddle_points.h"

#include <stdlib.h>
#include <string.h>

saddle_points_t *saddle_points(size_t row_num, size_t col_num, const void *matrix)
{
    const uint8_t *matrix_p = (const uint8_t *)matrix;
    
    // Pre-compute row maxima and column minima
    uint8_t *row_max = (uint8_t *)malloc(row_num * sizeof(uint8_t));
    uint8_t *col_min = (uint8_t *)malloc(col_num * sizeof(uint8_t));
    
    if (!row_max || !col_min) {
        free(row_max);
        free(col_min);
        return NULL;
    }
    
    // Calculate row maxima
    for (size_t i = 0; i < row_num; i++) {
        uint8_t max = matrix_p[i * col_num];
        for (size_t j = 1; j < col_num; j++) {
            uint8_t val = matrix_p[i * col_num + j];
            if (val > max) {
                max = val;
            }
        }
        row_max[i] = max;
    }
    
    // Calculate column minima
    for (size_t j = 0; j < col_num; j++) {
        uint8_t min = matrix_p[j];
        for (size_t i = 1; i < row_num; i++) {
            uint8_t val = matrix_p[i * col_num + j];
            if (val < min) {
                min = val;
            }
        }
        col_min[j] = min;
    }
    
    // Find saddle points directly
    saddle_point_t *points_temp = (saddle_point_t *)malloc(row_num * col_num * sizeof(saddle_point_t));
    if (!points_temp) {
        free(row_max);
        free(col_min);
        return NULL;
    }
    
    uint8_t count = 0;
    for (size_t i = 0; i < row_num; i++) {
        for (size_t j = 0; j < col_num; j++) {
            uint8_t val = matrix_p[i * col_num + j];
            if (val == row_max[i] && val == col_min[j]) {
                points_temp[count].row = i + 1;
                points_temp[count].column = j + 1;
                count++;
            }
        }
    }
    
    free(row_max);
    free(col_min);
    
    saddle_points_t *points = (saddle_points_t *)malloc(sizeof(saddle_points_t) + count * sizeof(saddle_point_t));
    if (!points) {
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