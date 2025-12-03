#include "diamond.h"
#include <stdlib.h>
#include <string.h>

char **make_diamond(const char letter)
{
    unsigned char length = 2 * (letter - 'A') + 1;
    unsigned char middle_index = length / 2;

    /* Memory allocation for diamond matrix */
    char **diamond = (char **)malloc(length * sizeof(char *));
    for (unsigned char i = 0; i < length; i++)
    {
        diamond[i] = (char *)malloc((length + 1) * sizeof(char));
        /* Initialize with spaces and null terminator in one go */
        memset(diamond[i], ' ', length);
        diamond[i][length] = '\0';
    }

    /* Fill in diamond matrix - top half and middle */
    for (unsigned char i = 0; i <= middle_index; i++)
    {
        char current_letter = 'A' + i;
        diamond[i][middle_index - i] = current_letter;
        if (i > 0)
        {
            diamond[i][middle_index + i] = current_letter;
        }
    }

    /* Mirror top half to bottom half */
    for (unsigned char i = middle_index + 1; i < length; i++)
    {
        memcpy(diamond[i], diamond[length - 1 - i], length);
    }

    return diamond;
}