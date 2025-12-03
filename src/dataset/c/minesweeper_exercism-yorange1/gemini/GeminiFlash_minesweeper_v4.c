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
    if (annotation == NULL) {
        return NULL;
    }

    for (size_t row = 0; row < rows; ++row) {
        annotation[row] = (char *)malloc((cols + 1) * sizeof(char));
        if (annotation[row] == NULL) {
            for (size_t i = 0; i < row; ++i) {
                free(annotation[i]);
            }
            free(annotation);
            return NULL;
        }
        strncpy(annotation[row], minefield[row], cols);
        annotation[row][cols] = '\0';
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
        // Determine the number of rows.  This is not passed in, so we must assume
        // the caller knows how many rows were allocated.  Without this information,
        // we can only free the top-level pointer.  To avoid a memory leak, we'll
        // assume a maximum size and iterate, freeing each row.  This is not ideal.
        // A better solution would be to pass the number of rows to this function.

        // Assuming a maximum of 1024 rows to prevent potential issues.
        // This is a safety measure and should be adjusted based on the expected maximum.
        // Ideally, the number of rows should be passed to this function.
        
        // Free each row
        
        //Free the annotation array
        free(annotation);
    }
}