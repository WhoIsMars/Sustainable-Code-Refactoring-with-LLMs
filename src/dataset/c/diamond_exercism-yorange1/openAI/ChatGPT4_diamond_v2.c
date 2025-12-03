#include "diamond.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char **make_diamond(const char letter)
{
    size_t width = 2 * (letter - 'A') + 1;

    char **diamond = (char **)malloc(width * sizeof(char *));
    assert(diamond != NULL);

    size_t middle = width / 2;

    for (size_t i = 0; i < width; i++)
    {
        diamond[i] = (char *)malloc(width + 1);
        assert(diamond[i] != NULL);
        memset(diamond[i], ' ', width);
        diamond[i][width] = '\0';

        size_t offset = (i <= middle) ? i : width - i - 1;
        char value = 'A' + offset;
        diamond[i][middle - offset] = value;
        diamond[i][middle + offset] = value;
    }

    return diamond;
}