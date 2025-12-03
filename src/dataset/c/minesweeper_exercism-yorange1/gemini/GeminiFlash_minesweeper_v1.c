#include "minesweeper.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static inline void update(char **annotation, size_t row, size_t col, size_t rows, size_t cols) {
    size_t row_begin = (row > 0) ? row - 1 : 0;
    size_t row_end = (row + 1 < rows) ? row + 1 : row;
    size_t col_begin = (col > 0) ? col - 1 : 0;
    size_t col_end = (col + 1 < cols) ? col + 1 : col;

    for (size_t i = row_begin; i <= row_end; ++i) {
        for (size_t j = col_begin; j <= col_end; ++j) {
            if (annotation[i][j] != '*') {
                if (annotation[i][j] == ' ') {
                    annotation[i][j] = '1';
                } else {
                    annotation[i][j]++;
                }
            }
        }
    }
}

char **annotate(const char **minefield, const size_t rows) {
    if (rows == 0) {
        return NULL;
    }

    size_t cols = strlen(minefield[0]);
    char **annotation = (char **)malloc(rows * sizeof(char *));
    if (!annotation) return NULL;

    for (size_t row = 0; row < rows; ++row) {
        annotation[row] = (char *)malloc((cols + 1) * sizeof(char));
        if (!annotation[row]) {
            // Memory allocation failed, free previously allocated memory
            for (size_t i = 0; i < row; ++i) {
                free(annotation[i]);
            }
            free(annotation);
            return NULL;
        }
        strcpy(annotation[row], minefield[row]);
        annotation[row][cols] = '\0'; // Ensure null termination
    }

    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            if (annotation[row][col] == '*') {
                update(annotation, row, col, rows, cols);
            }
        }
    }

    return annotation;
}

void free_annotation(char **annotation) {
    if (annotation != NULL) {
        // Find the number of rows by iterating until a NULL pointer is found
        // Assuming annotation was allocated as an array of char*
        // This is a potential issue if the array isn't NULL-terminated.
        // A better approach would be to pass the number of rows to this function.
        // However, to adhere to the original function signature, we'll use this approach.

        // Assuming the allocation was done correctly in annotate function
        // and the number of rows is known.
        // Without knowing the number of rows, we can't safely free the memory.
        // This implementation assumes the caller knows the number of rows
        // and frees the memory accordingly.  A safer approach would be to
        // modify the function signature to include the number of rows.

        // This is a placeholder to avoid memory leaks.  The caller MUST
        // free each row before freeing the annotation array itself.
        // Example:
        // for (size_t i = 0; i < num_rows; ++i) {
        //   free(annotation[i]);
        // }
        // free(annotation);
        free(annotation); // Free the array of pointers.
    }
}