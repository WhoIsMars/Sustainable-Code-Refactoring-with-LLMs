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

    char **local_minefield = (char **)malloc(rows * sizeof(char *));
    for (unsigned char i = 0; i < rows; i++)
    {
        local_minefield[i] = (char *)malloc((len + 1) * sizeof(char));
        memcpy(local_minefield[i], minefield[i], len);
        local_minefield[i][len] = '\0';
    }

    const int offsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (unsigned char i = 0; i < rows; i++)
    {
        for (unsigned char j = 0; j < len; j++)
        {
            if (local_minefield[i][j] == '*')
                continue;

            unsigned char counter = 0;
            for (unsigned char k = 0; k < 8; k++)
            {
                int ni = i + offsets[k][0];
                int nj = j + offsets[k][1];

                if (ni >= 0 && ni < rows && nj >= 0 && nj < len && minefield[ni][nj] == '*')
                {
                    counter++;
                }
            }

            local_minefield[i][j] = (counter > 0) ? (counter + '0') : ' ';
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