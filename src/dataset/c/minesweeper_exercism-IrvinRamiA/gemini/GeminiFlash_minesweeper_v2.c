#include "minesweeper.h"
#include <stdlib.h>
#include <stdio.h>

char **annotate(const char **minefield, const unsigned char rows) {
    if (minefield == NULL || rows == 0) {
        return NULL;
    }

    unsigned char cols = 0;
    while (minefield[0][cols] != '\0') {
        cols++;
    }

    char **local_minefield = (char **)malloc(rows * sizeof(char *));
    if (local_minefield == NULL) {
        return NULL;
    }

    for (unsigned char i = 0; i < rows; i++) {
        local_minefield[i] = (char *)malloc((cols + 1) * sizeof(char));
        if (local_minefield[i] == NULL) {
            // Handle allocation failure: free previously allocated memory
            for (unsigned char j = 0; j < i; j++) {
                free(local_minefield[j]);
            }
            free(local_minefield);
            return NULL;
        }
        strcpy(local_minefield[i], minefield[i]);
    }

    for (unsigned char i = 0; i < rows; i++) {
        for (unsigned char j = 0; j < cols; j++) {
            if (local_minefield[i][j] == '*') continue;

            unsigned char counter = 0;
            for (int k = (i > 0 ? i - 1 : i); k <= (i < rows - 1 ? i + 1 : i); k++) {
                for (int l = (j > 0 ? j - 1 : j); l <= (j < cols - 1 ? j + 1 : j); l++) {
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

void free_annotation(char **annotation, unsigned char rows) {
    if (annotation != NULL) {
        for (unsigned char i = 0; i < rows; i++) {
            free(annotation[i]);
        }
        free(annotation);
    }
}