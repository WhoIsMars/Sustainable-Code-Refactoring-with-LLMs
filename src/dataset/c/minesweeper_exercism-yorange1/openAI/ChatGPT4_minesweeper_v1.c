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
            size_t r = row + i;
            size_t c = col + j;
            if (r < rows && c < cols && annotation[r][c] != '*')
            {
                annotation[r][c] = (annotation[r][c] == ' ') ? '1' : annotation[r][c] + 1;
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