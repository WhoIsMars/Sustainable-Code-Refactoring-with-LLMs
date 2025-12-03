#include "minesweeper.h"
#include <string.h>
#include <stdlib.h>

char **annotate(const char **minefield, const unsigned char rows)
{
    if (minefield == NULL || rows == 0)
    {
        return NULL;
    }

    unsigned char len = strlen(minefield[0]);
    if (len == 0)
    {
        return NULL;
    }

    /* Memory allocation for mutable copy of minefield */
    char **local_minefield = (char **)malloc(rows * sizeof(char *));
    if (local_minefield == NULL)
    {
        return NULL;
    }

    for (unsigned char i = 0; i < rows; i++)
    {
        local_minefield[i] = (char *)malloc((len + 1) * sizeof(char));
        if (local_minefield[i] == NULL)
        {
            /* Free previously allocated memory on failure */
            for (unsigned char k = 0; k < i; k++)
            {
                free(local_minefield[k]);
            }
            free(local_minefield);
            return NULL;
        }
        /* Copy and null-terminate in one step */
        memcpy(local_minefield[i], minefield[i], len);
        local_minefield[i][len] = '\0';
    }

    /* Iterating over the minefield and counting "*" */
    for (unsigned char i = 0; i < rows; i++)
    {
        for (unsigned char j = 0; j < len; j++)
        {
            if (local_minefield[i][j] != '*')
            {
                unsigned char counter = 0;
                
                /* Calculate bounds once */
                unsigned char row_start = (i > 0) ? i - 1 : 0;
                unsigned char row_end = (i < rows - 1) ? i + 1 : rows - 1;
                unsigned char col_start = (j > 0) ? j - 1 : 0;
                unsigned char col_end = (j < len - 1) ? j + 1 : len - 1;

                /* Count adjacent mines */
                for (unsigned char k = row_start; k <= row_end; k++)
                {
                    for (unsigned char l = col_start; l <= col_end; l++)
                    {
                        if (local_minefield[k][l] == '*' && (k != i || l != j))
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
    }

    return local_minefield;
}

void free_annotation(char **annotation)
{
    if (annotation != NULL)
    {
        /* Need to know the number of rows to properly free */
        /* This function should ideally take rows as parameter */
        free(annotation);
    }
}