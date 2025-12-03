#include "pascals_triangle.h"

#include <stddef.h>
#include <stdlib.h>

void free_triangle(uint8_t **triangle, size_t rows)
{
    if (triangle == NULL) return;
    
    for (size_t i = 0; i < rows; i++)
    {
        free(triangle[i]);
    }
    free(triangle);
}

uint8_t **create_triangle(size_t rows)
{
    if (rows < 1)
    {
        uint8_t **triangle = malloc(sizeof(uint8_t *));
        if (triangle == NULL) return NULL;
        
        triangle[0] = malloc(sizeof(uint8_t));
        if (triangle[0] == NULL)
        {
            free(triangle);
            return NULL;
        }
        triangle[0][0] = 0;
        return triangle;
    }

    uint8_t **triangle = malloc(rows * sizeof(uint8_t *));
    if (triangle == NULL) return NULL;

    for (size_t row = 0; row < rows; row++)
    {
        size_t row_len = row + 1;
        triangle[row] = malloc(row_len * sizeof(uint8_t));
        if (triangle[row] == NULL)
        {
            free_triangle(triangle, row);
            return NULL;
        }

        triangle[row][0] = 1;
        triangle[row][row] = 1;

        for (size_t i = 1; i < row; i++)
        {
            triangle[row][i] = triangle[row - 1][i - 1] + triangle[row - 1][i];
        }
    }

    return triangle;
}