#include "diamond.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char **make_diamond(const char letter)
{
    size_t width = 2 * (letter - 'A') + 1;
    size_t height = width;

    char **diamond = (char **)malloc(height * sizeof(char *));
    assert(diamond != NULL);

    // Allocate all strings in one block
    char *string_block = (char *)malloc(height * (width + 1));
    assert(string_block != NULL);

    for (size_t i = 0; i < height; i++)
    {
        diamond[i] = string_block + i * (width + 1);
        memset(diamond[i], ' ', width);
        diamond[i][width] = '\0';
    }

    size_t middle = height / 2;

    if (1 == height)
    {
        diamond[0][0] = 'A';
        return diamond;
    }

    // Set top and bottom A's
    diamond[0][middle] = 'A';
    diamond[height - 1][middle] = 'A';
    
    // Set middle row (target letter)
    diamond[middle][0] = letter;
    diamond[middle][width - 1] = letter;

    // Fill upper and lower halves simultaneously
    for (size_t i = 1; i < middle; i++)
    {
        char value = 'A' + i;
        size_t left_pos = middle - i;
        size_t right_pos = middle + i;
        size_t bottom_row = height - 1 - i;
        
        diamond[i][left_pos] = value;
        diamond[i][right_pos] = value;
        diamond[bottom_row][left_pos] = value;
        diamond[bottom_row][right_pos] = value;
    }

    return diamond;
}