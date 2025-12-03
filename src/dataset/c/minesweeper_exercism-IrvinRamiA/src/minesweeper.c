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
    unsigned char counter = 0;

    /* Memory allocation for mutable copy of minefiled */
    char **local_minefield = (char **)malloc(rows * sizeof(char *));

    for (unsigned char i = 0; i < rows; i++)
    {
        local_minefield[i] = (char *)malloc((len + 1) * sizeof(char));
    }

    /* Copying minefield to local_minefield */
    for (unsigned char i = 0; i < rows; i++)
    {
        for (unsigned char j = 0; j < len + 1; j++)
        {
            if (j == len)
            {
                local_minefield[i][j] = '\0';
            }
            else
            {
                local_minefield[i][j] = minefield[i][j];
            }
        }
    }

    /* Iterating over the minefield and counting "*" */
    for (unsigned char i = 0; i < rows; i++)
    {
        for (unsigned char j = 0; j < len; j++)
        {
            if (local_minefield[i][j] != '*')
            {
                unsigned char row_init = (i == 0) ? 0: i - 1;
                unsigned char row_end = (i == rows - 1) ? rows - 1 : i + 1;
                unsigned char col_init = (j == 0) ? 0: j - 1;
                unsigned char col_end = (j == len - 1) ? len - 1 : j + 1;

                for (unsigned char k = row_init; k <= row_end; k++)
                {
                    for (unsigned char l = col_init; l <= col_end; l++)
                    {
                        // printf("K, L\n");
                        // printf("[%d][%d]\n", k, l);
                        if (local_minefield[k][l] == '*' && (i != k || j != l))
                        {
                            counter++;
                        }
                    }
                }
                if (counter != 0)
                {
                    local_minefield[i][j] = counter + '0';
                    counter = 0;
                }
            }
        }
    }

    return local_minefield;
}

void free_annotation(char **annotation)
{
    free(annotation);
}