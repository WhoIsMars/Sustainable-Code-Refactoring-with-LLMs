#include "minesweeper.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static inline void update_cell(char *cell)
{
    if (*cell != '*') {
        *cell = (*cell == ' ') ? '1' : *cell + 1;
    }
}

static void update(char **annotation, size_t row, size_t col, size_t rows, size_t cols)
{
    const size_t row_start = (row > 0) ? row - 1 : 0;
    const size_t row_end = (row + 1 < rows) ? row + 1 : rows - 1;
    const size_t col_start = (col > 0) ? col - 1 : 0;
    const size_t col_end = (col + 1 < cols) ? col + 1 : cols - 1;

    for (size_t i = row_start; i <= row_end; i++) {
        char *row_ptr = annotation[i];
        for (size_t j = col_start; j <= col_end; j++) {
            update_cell(&row_ptr[j]);
        }
    }
}

char **annotate(const char **minefield, const size_t rows)
{
    if (rows == 0) {
        return NULL;
    }

    const size_t cols = strlen(minefield[0]);
    const size_t total_size = rows * sizeof(char *) + rows * (cols + 1);
    
    char **annotation = (char **)malloc(total_size);
    assert(annotation != NULL);

    char *data = (char *)(annotation + rows);
    
    for (size_t row = 0; row < rows; row++) {
        annotation[row] = data + row * (cols + 1);
        memcpy(annotation[row], minefield[row], cols);
        annotation[row][cols] = '\0';
    }

    for (size_t row = 0; row < rows; row++) {
        const char *row_ptr = annotation[row];
        for (size_t col = 0; col < cols; col++) {
            if (row_ptr[col] == '*') {
                update(annotation, row, col, rows, cols);
            }
        }
    }

    return annotation;
}

void free_annotation(char **annotation)
{
    if (annotation != NULL) {
        free(annotation);
    }
}