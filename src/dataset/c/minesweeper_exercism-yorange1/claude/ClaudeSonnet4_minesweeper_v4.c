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
    if (rows == 0)
    {
        return NULL;
    }

    size_t cols = strlen(minefield[0]);
    size_t total_size = rows * sizeof(char *) + rows * (cols + 1);
    char **annotation = (char **)malloc(total_size);
    assert(annotation != NULL);

    char *data = (char *)(annotation + rows);
    
    for (size_t row = 0; row < rows; row++)
    {
        annotation[row] = data + row * (cols + 1);
        memcpy(annotation[row], minefield[row], cols);
        annotation[row][cols] = '\0';
    }

    for (size_t row = 0; row < rows; row++)
    {
        const char *current_row = annotation[row];
        for (size_t col = 0; col < cols; col++)
        {
            if (current_row[col] == '*')
            {
                update(annotation, row, col, rows, cols);
            }
        }
    }

    return annotation;
}

void free_annotation(char **annotation)
{
    if (annotation != NULL)
    {
        free(annotation);
    }
}