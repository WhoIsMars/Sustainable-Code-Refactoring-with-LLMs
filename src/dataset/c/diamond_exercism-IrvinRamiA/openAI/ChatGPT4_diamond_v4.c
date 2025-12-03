#include "diamond.h"
#include <stdlib.h>
#include <string.h>

char **make_diamond(const char letter)
{
    unsigned char length = 2 * (letter - 'A') + 1;
    unsigned char middle_index = length / 2;

    char **diamond = (char **)malloc(length * sizeof(char *));
    if (!diamond)
        return NULL;

    for (unsigned char i = 0; i < length; i++)
    {
        diamond[i] = (char *)malloc((length + 1) * sizeof(char));
        if (!diamond[i])
        {
            while (i > 0)
                free(diamond[--i]);
            free(diamond);
            return NULL;
        }
        memset(diamond[i], ' ', length);
        diamond[i][length] = '\0';
    }

    for (unsigned char i = 0; i <= middle_index; i++)
    {
        diamond[i][middle_index + i] = 'A' + i;
        diamond[i][middle_index - i] = 'A' + i;
        if (i != middle_index)
        {
            memcpy(diamond[length - i - 1], diamond[i], length);
        }
    }

    return diamond;
}