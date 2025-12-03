#include "diamond.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

char **make_diamond(const char letter)
{
    size_t size = letter - 'A' + 1;
    size_t width = 2 * size - 1;

    char **diamond = (char **)malloc(size * sizeof(char *));
    assert(diamond != NULL);

    for (size_t i = 0; i < size; i++)
    {
        diamond[i] = (char *)malloc(width + 1);
        assert(diamond[i] != NULL);
        memset(diamond[i], ' ', width);
        diamond[i][width] = '\0';

        char value = 'A' + i;
        diamond[i][size - 1 - i] = value;
        diamond[i][size - 1 + i] = value;

        if (i > 0)
        {
            diamond[2 * size - 2 - i] = diamond[i];
        }
    }

    return diamond;
}