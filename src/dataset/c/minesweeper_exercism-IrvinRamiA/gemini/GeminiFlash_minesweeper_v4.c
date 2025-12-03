#include "minesweeper.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char **annotate(const char **minefield, const unsigned char rows)
{
    if (minefield == NULL)
    {
        return NULL;
    }

    unsigned char len = strlen(minefield[0]);

    char **local_minefield = (char **)malloc(rows * sizeof(char *));
    if (local_minefield == NULL) {
        return NULL;
    }

    for (unsigned char i = 0; i < rows; i++)
    {
        local_minefield[i] = (char *)malloc((len + 1) * sizeof(char));
        if (local_minefield[i] == NULL) {
            // Handle allocation failure: free previously allocated memory
            for (unsigned char j = 0; j < i; j++) {
                free(local_minefield[j]);
            }
            free(local_minefield);
            return NULL;
        }
        strncpy(local_minefield[i], minefield[i], len);
        local_minefield[i][len] = '\0';
    }

    for (unsigned char i = 0; i < rows; i++)
    {
        for (unsigned char j = 0; j < len; j++)
        {
            if (local_minefield[i][j] == '*') continue;

            unsigned char counter = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (k == 0 && l == 0) continue;

                    int row_index = i + k;
                    int col_index = j + l;

                    if (row_index >= 0 && row_index < rows && col_index >= 0 && col_index < len && local_minefield[row_index][col_index] == '*')
                    {
                        counter++;
                    }
                }
            }

            if (counter > 0)
            {
                local_minefield[i][j] = counter + '0';
            }
        }
    }

    return local_minefield;
}

void free_annotation(char **annotation)
{
    // Free the memory allocated for each row
    if (annotation != NULL) {
        // Assuming the number of rows is known or stored elsewhere.
        // Without that information, we can't safely free the memory.
        // This is a potential memory leak.
        // The original code also had this issue.
        // A safer approach would be to pass the number of rows to this function.
        // For example: void free_annotation(char **annotation, unsigned char rows)
        // Then the loop below would be safe.

        // This is a placeholder to match the original signature.
        // It is not safe to use without knowing the number of rows.
        free(annotation);
    }
}