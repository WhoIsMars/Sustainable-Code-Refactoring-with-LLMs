#include "pascals_triangle.h"

#include <stddef.h>
#include <stdlib.h>

void free_triangle(uint8_t **triangle, size_t rows)
{
    if (triangle)
    {
        for (size_t i = 0; i < rows; i++)
        {
            free(triangle[i]);
        }
        free(triangle);
    }
}

uint8_t **create_triangle(size_t rows)
{
    if (rows == 0)
    {
        uint8_t **triangle = (uint8_t **)calloc(1, sizeof(uint8_t *));
        if (!triangle)
            return NULL;

        triangle[0] = (uint8_t *)calloc(1, sizeof(uint8_t));
        if (!triangle[0])
        {
            free(triangle);
            return NULL;
        }

        return triangle;
    }

    uint8_t **triangle = (uint8_t **)calloc(rows, sizeof(uint8_t *));
    if (!triangle)
        return NULL;

    for (size_t row = 0; row < rows; row++)
    {
        triangle[row] = (uint8_t *)calloc(row + 1, sizeof(uint8_t));
        if (!triangle[row])
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