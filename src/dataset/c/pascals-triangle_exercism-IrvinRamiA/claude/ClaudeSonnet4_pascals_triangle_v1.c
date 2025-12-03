#include <stdlib.h>
#include "pascals_triangle.h"

void free_triangle(uint8_t **triangle, uint8_t rows)
{
    if (triangle == NULL) return;
    
    for (uint8_t i = 0; i < rows; i++)
    {
        free(triangle[i]);
    }
    free(triangle);
}

uint8_t **create_triangle(uint8_t rows)
{
    if (rows == 0)
    {
        uint8_t **triangle = (uint8_t **)malloc(sizeof(uint8_t *));
        triangle[0] = (uint8_t *)calloc(1, sizeof(uint8_t));
        return triangle;
    }

    /* Memory allocation for triangular structure */
    uint8_t **triangle = (uint8_t **)malloc(rows * sizeof(uint8_t *));
    
    for (uint8_t i = 0; i < rows; i++)
    {
        triangle[i] = (uint8_t *)malloc((i + 1) * sizeof(uint8_t));
        
        /* Set edge values */
        triangle[i][0] = 1;
        if (i > 0) triangle[i][i] = 1;
        
        /* Calculate internal values */
        for (uint8_t j = 1; j < i; j++)
        {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }

    return triangle;
}