#include "diamond.h"
#include <stdlib.h>

char **make_diamond(const char letter)
{
    unsigned char length = 2 * (letter - 'A') + 1;
    unsigned char middle_index = length / 2;

    char **diamond = (char **)malloc(length * sizeof(char *));
    if (!diamond) return NULL;

    for (unsigned char i = 0; i < length; i++)
    {
        diamond[i] = (char *)malloc((length + 1) * sizeof(char));
        if (!diamond[i])
        {
            for (unsigned char j = 0; j < i; j++)
            {
                free(diamond[j]);
            }
            free(diamond);
            return NULL;
        }
        diamond[i][length] = '\0';
        for (unsigned char j = 0; j < length; j++)
        {
            diamond[i][j] = ' ';
        }
    }

    for (unsigned char i = 0; i <= middle_index; i++)
    {
        diamond[i][middle_index + i] = 'A' + i;
        diamond[i][middle_index - i] = 'A' + i;
        diamond[length - 1 - i][middle_index + i] = 'A' + i;
        diamond[length - 1 - i][middle_index - i] = 'A' + i;
    }

    return diamond;
}