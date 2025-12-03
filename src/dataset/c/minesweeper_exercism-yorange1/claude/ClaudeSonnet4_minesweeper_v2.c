#include "minesweeper.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void update(char **annotation, size_t row, size_t col, size_t rows, size_t cols)
{
    size_t row_begin = row > 0 ? row - 1 : 0;
    size_t row_end = row + 1 < rows ? row + 1 : row;
    size_t col_begin = col > 0 ? col - 1 : 0;
    size_t col_end = col + 1 < cols ? col + 1 : col;

    for (size_t i = row_begin; i <= row_end; i++)
    {
        char *row_ptr = annotation[i];
        for (size_t j = col_begin; j <= col_end; j++)
        {
            char cell = row_ptr[j];
            if (cell != '*')
            {
                row_ptr[j] = (cell == ' ') ? '1' : cell + 1;
            }
        }
    }
}

char **annotate(const char **minefield, const size_t rows)
{
    if (0 == rows)
    {
        return NULL;
    }

    size_t cols = strlen(minefield[0]);
    char **annotation = (char **)malloc(rows * sizeof(char *));
    assert(annotation != NULL);

    for (size_t row = 0; row < rows; row++)
    {
        annotation[row] = (char *)malloc(cols + 1);
        assert(annotation[row] != NULL);
        memcpy(annotation[row], minefield[row], cols + 1);
    }

    for (size_t row = 0; row < rows; row++)
    {
        const char *row_ptr = annotation[row];
        for (size_t col = 0; col < cols; col++)
        {
            if ('*' == row_ptr[col])
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
    free(annotation);
}