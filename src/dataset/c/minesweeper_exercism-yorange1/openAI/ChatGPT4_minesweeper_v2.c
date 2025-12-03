#include "minesweeper.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void update(char **annotation, size_t row, size_t col, size_t rows, size_t cols)
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            size_t new_row = row + i;
            size_t new_col = col + j;

            if (new_row < rows && new_col < cols && annotation[new_row][new_col] != '*')
            {
                if (annotation[new_row][new_col] == ' ')
                {
                    annotation[new_row][new_col] = '1';
                }
                else
                {
                    annotation[new_row][new_col]++;
                }
            }
        }
    }
}

char **annotate(const char **minefield, const size_t rows)
{
    if (rows == 0 || minefield == NULL)
    {
        return NULL;
    }

    size_t cols = strlen(minefield[0]);
    char **annotation = (char **)malloc(rows * sizeof(char *));
    assert(annotation != NULL);

    for (size_t row = 0; row < rows; row++)
    {
        annotation[row] = (char *)malloc((cols + 1) * sizeof(char));
        assert(annotation[row] != NULL);
        memcpy(annotation[row], minefield[row], cols + 1);
    }

    for (size_t row = 0; row < rows; row++)
    {
        for (size_t col = 0; col < cols; col++)
        {
            if (annotation[row][col] == '*')
            {
                update(annotation, row, col, rows, cols);
            }
        }
    }

    return annotation;
}

void free_annotation(char **annotation)
{
    assert(annotation != NULL);

    for (size_t i = 0; annotation[i] != NULL; i++)
    {
        free(annotation[i]);
    }
    free(annotation);
}