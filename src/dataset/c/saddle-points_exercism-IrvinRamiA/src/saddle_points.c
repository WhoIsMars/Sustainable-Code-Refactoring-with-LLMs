#include "saddle_points.h"
#include <stdbool.h>
#include <string.h>

saddle_points_t *saddle_points(uint8_t rows, uint8_t cols, uint8_t matrix[rows][cols])
{
    saddle_point_t points[10];
    uint8_t total_saddle_points = 0;
    bool is_greater_in_row = true;
    bool is_less_in_col = true;

    for (uint8_t i = 0; i < rows; i++)
    {
        for (uint8_t j = 0; j < cols; j++)
        {
            for (uint8_t col_index = 0; col_index < cols; col_index++)
            {
                if (matrix[i][j] < matrix[i][col_index])
                {
                    is_greater_in_row = false;
                    break;
                }
            }

            for (uint8_t row_index = 0; row_index < rows; row_index++)
            {
                if (matrix[i][j] > matrix[row_index][j])
                {
                    is_less_in_col = false;
                    break;
                }
            }

            if (is_greater_in_row && is_less_in_col)
            {
                points[total_saddle_points].row = i + 1;
                points[total_saddle_points++].column = j + 1;
            }

            is_greater_in_row = true;
            is_less_in_col = true;
        }
    }

    saddle_points_t *result = (saddle_points_t *)malloc(sizeof(saddle_points_t));
    result->points = (saddle_point_t *)malloc(total_saddle_points * sizeof(saddle_point_t));

    result->count = total_saddle_points;
    memcpy(result->points, points, total_saddle_points * sizeof(saddle_point_t));

    return result;
}

void free_saddle_points(saddle_points_t *result)
{
    free(result->points);
    free(result);
}
