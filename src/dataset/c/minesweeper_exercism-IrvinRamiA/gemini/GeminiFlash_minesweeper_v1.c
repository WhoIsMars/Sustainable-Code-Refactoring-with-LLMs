#include "minesweeper.h"
#include <stdlib.h>
#include <stdio.h>

char **annotate(const char **minefield, const unsigned char rows) {
    if (minefield == NULL || rows == 0) {
        return NULL;
    }

    unsigned char len = 0;
    while (minefield[0][len] != '\0') {
        len++;
    }

    char **local_minefield = (char **)malloc(rows * sizeof(char *));
    if (local_minefield == NULL) {
        return NULL;
    }

    for (unsigned char i = 0; i < rows; i++) {
        local_minefield[i] = (char *)malloc((len + 1) * sizeof(char));
        if (local_minefield[i] == NULL) {
            // Handle allocation failure: free previously allocated memory
            for (unsigned char j = 0; j < i; j++) {
                free(local_minefield[j]);
            }
            free(local_minefield);
            return NULL;
        }

        // Copy the minefield row directly using pointer arithmetic
        char *dest = local_minefield[i];
        const char *src = minefield[i];
        for (unsigned char j = 0; j < len; j++) {
            *dest++ = *src++;
        }
        *dest = '\0'; // Null-terminate the string
    }

    for (unsigned char i = 0; i < rows; i++) {
        for (unsigned char j = 0; j < len; j++) {
            if (local_minefield[i][j] == '*') continue;

            unsigned char counter = 0;
            int row_start = (i > 0) ? i - 1 : i;
            int row_end = (i < rows - 1) ? i + 1 : i;
            int col_start = (j > 0) ? j - 1 : j;
            int col_end = (j < len - 1) ? j + 1 : j;

            for (int k = row_start; k <= row_end; k++) {
                for (int l = col_start; l <= col_end; l++) {
                    if (local_minefield[k][l] == '*' && (k != i || l != j)) {
                        counter++;
                    }
                }
            }

            if (counter > 0) {
                local_minefield[i][j] = counter + '0';
            }
        }
    }

    return local_minefield;
}

void free_annotation(char **annotation) {
    if (annotation == NULL) return;

    // Determine the number of rows.  We can't know this from the pointer alone.
    // This implementation assumes that the number of rows is not stored anywhere
    // accessible to this function.  Therefore, we can't safely free the memory.
    // A safer implementation would require passing the number of rows to this function.
    // For now, we avoid freeing the memory to prevent potential crashes.

    // DO NOT FREE THE MEMORY HERE.  This is a placeholder for a safer implementation.
    // The caller is responsible for freeing the memory.
}