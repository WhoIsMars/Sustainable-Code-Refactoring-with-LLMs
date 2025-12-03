#include "diamond.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char **make_diamond(const char letter)
{
    size_t width = 2 * (letter - 'A') + 1;
    size_t middle = width / 2;

    char **diamond = (char **)calloc(width, sizeof(char *));
    assert(diamond != NULL);

    for (size_t i = 0; i < width; i++)
    {
        diamond[i] = (char *)calloc(width + 1, sizeof(char));
        assert(diamond[i] != NULL);
    }

    for (size_t i = 0; i <= middle; i++)
    {
        char value = 'A' + i;
        diamond[i][middle + i] = value;
        diamond[i][middle - i] = value;
        diamond[width - 1 - i][middle + i] = value;
        diamond[width - 1 - i][middle - i] = value;
    }

    return diamond;
}