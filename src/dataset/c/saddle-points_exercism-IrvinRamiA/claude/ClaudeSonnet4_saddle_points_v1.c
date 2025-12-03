#include "saddle_points.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

saddle_points_t *saddle_points(uint8_t rows, uint8_t cols, uint8_t matrix[rows][cols])
{
    saddle_point_t points[10];
    uint8_t total_saddle_points = 0;
    
    // Pre-compute row maximums and column minimums
    uint8_t row_max[rows];
    uint8_t col_min[cols];
    
    // Find maximum in each row
    for (uint8_t i = 0; i < rows; i++)
    {
        row_max[i] = matrix[i][0];
        for (uint8_t j = 1; j < cols; j++)
        {
            if (matrix[i][j] > row_max[i])
                row_max[i] = matrix[i][j];
        }
    }
    
    // Find minimum in each column
    for (uint8_t j = 0; j < cols; j++)
    {
        col_min[j] = matrix[0][j];
        for (uint8_t i = 1; i < rows; i++)
        {
            if (matrix[i][j] < col_min[j])
                col_min[j] = matrix[i][j];
        }
    }
    
    // Check for saddle points
    for (uint8_t i = 0; i < rows; i++)
    {
        for (uint8_t j = 0; j < cols; j++)
        {
            if (matrix[i][j] == row_max[i] && matrix[i][j] == col_min[j])
            {
                points[total_saddle_points].row = i + 1;
                points[total_saddle_points++].column = j + 1;
            }
        }
    }

    saddle_points_t *result = (saddle_points_t *)malloc(sizeof(saddle_points_t));
    if (total_saddle_points > 0)
    {
        result->points = (saddle_point_t *)malloc(total_saddle_points * sizeof(saddle_point_t));
        memcpy(result->points, points, total_saddle_points * sizeof(saddle_point_t));
    }
    else
    {
        result->points = NULL;
    }
    
    result->count = total_saddle_points;
    return result;
}

void free_saddle_points(saddle_points_t *result)
{
    if (result)
    {
        free(result->points);
        free(result);
    }
}