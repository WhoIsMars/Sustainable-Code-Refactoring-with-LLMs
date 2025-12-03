#include <stdlib.h>
#include "pascals_triangle.h"

void free_triangle(uint8_t **triangle, uint8_t rows)
{
    for (uint8_t i = 0; i < rows; i++)
    {
        free(triangle[i]);
    }
    free(triangle);
}

uint8_t **create_triangle(uint8_t rows)
{
    int zero_rows = 0;
    if (rows == 0)
    {
        rows = 1;
        zero_rows = 1;
    }

    /* Memory allocation for the creation of a squared matrix*/
    uint8_t **triangle = (uint8_t **)malloc(rows * sizeof(char *));
    for (uint8_t i = 0; i < rows; i++)
    {
        triangle[i] = (uint8_t *)malloc(rows * sizeof(char));
    }

    for (uint8_t i = 0; i < rows; i++)
    {
        for (uint8_t j = 0; j < rows; j++)
        {
            if (zero_rows)
            {
                triangle[i][j] = 0;
                break;
            }
            if (i == 0 || i == j)
            {
                triangle[i][j] = 1;
            }
            else if (i > j)
            {
                triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
        }
    }

    return triangle;
}
