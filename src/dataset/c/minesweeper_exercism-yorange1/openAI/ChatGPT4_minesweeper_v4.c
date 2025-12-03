#include "minesweeper.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void update(char **annotation, size_t row, size_t col, size_t rows, size_t cols)
{
    for (size_t i = (row > 0 ? row - 1 : 0); i <= (row + 1 < rows ? row + 1 : row); i++)
    {
        for (size_t j = (col > 0 ? col - 1 : 0); j <= (col + 1 < cols ? col + 1 : col); j++)
        {
            if (annotation[i][j] == '*') continue;
            annotation[i][j] = (annotation[i][j] == ' ') ? '1' : annotation[i][j] + 1;
        }
    }
}

char **annotate(const char **minefield, const size_t rows)
{
    if (rows == 0) return NULL;

    size_t cols = strlen(minefield[0]);
    char **annotation = (char **)malloc(rows * sizeof(char *));
    assert(annotation);

    for (size_t row = 0; row < rows; row++)
    {
        annotation[row] = (char *)malloc((cols + 1) * sizeof(char));
        assert(annotation[row]);
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
    assert(annotation);
    free(annotation);
}