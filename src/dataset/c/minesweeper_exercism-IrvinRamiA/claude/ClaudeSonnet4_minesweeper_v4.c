#include "minesweeper.h"
#include <string.h>
#include <stdlib.h>

char **annotate(const char **minefield, const unsigned char rows)
{
    if (minefield == NULL || rows == 0)
    {
        return NULL;
    }

    const unsigned char len = strlen(minefield[0]);
    if (len == 0)
    {
        return NULL;
    }

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
            for (unsigned char k = 0; k < i; k++)
            {
                free(local_minefield[k]);
            }
            free(local_minefield);
            return NULL;
        }
        memcpy(local_minefield[i], minefield[i], len);
        local_minefield[i][len] = '\0';
    }

    for (unsigned char i = 0; i < rows; i++)
    {
        for (unsigned char j = 0; j < len; j++)
        {
            if (local_minefield[i][j] != '*')
            {
                unsigned char counter = 0;
                const unsigned char row_start = (i > 0) ? i - 1 : 0;
                const unsigned char row_end = (i < rows - 1) ? i + 1 : rows - 1;
                const unsigned char col_start = (j > 0) ? j - 1 : 0;
                const unsigned char col_end = (j < len - 1) ? j + 1 : len - 1;

                for (unsigned char k = row_start; k <= row_end; k++)
                {
                    for (unsigned char l = col_start; l <= col_end; l++)
                    {
                        if (local_minefield[k][l] == '*' && (i != k || j != l))
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
        free(annotation);
    }
}