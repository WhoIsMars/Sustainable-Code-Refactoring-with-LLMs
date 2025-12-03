#include "minesweeper.h"
#include <string.h>
#include <stdlib.h>

char **annotate(const char **minefield, const unsigned char rows)
{
    if (minefield == NULL || rows == 0 || strlen(minefield[0]) == 0)
    {
        return NULL;
    }

    unsigned char len = strlen(minefield[0]);

    /* Memory allocation for mutable copy of minefield */
    char **local_minefield = (char **)malloc(rows * sizeof(char *));
    for (unsigned char i = 0; i < rows; i++)
    {
        local_minefield[i] = (char *)malloc((len + 1) * sizeof(char));
        strcpy(local_minefield[i], minefield[i]);
    }

    /* Iterating over the minefield and counting "*" */
    for (unsigned char i = 0; i < rows; i++)
    {
        for (unsigned char j = 0; j < len; j++)
        {
            if (local_minefield[i][j] != '*')
            {
                unsigned char counter = 0;
                for (char k = -1; k <= 1; k++)
                {
                    for (char l = -1; l <= 1; l++)
                    {
                        unsigned char ni = i + k, nj = j + l;
                        if (k == 0 && l == 0) continue;
                        if (ni < rows && nj < len && local_minefield[ni][nj] == '*')
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
    if (annotation)
    {
        for (unsigned char i = 0; annotation[i] != NULL; i++)
        {
            free(annotation[i]);
        }
        free(annotation);
    }
}