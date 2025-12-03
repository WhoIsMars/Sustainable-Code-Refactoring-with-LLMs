#include "diamond.h"
#include <stdlib.h>
#include <string.h>

char **make_diamond(const char letter)
{
    unsigned char length = 2 * (letter - 'A') + 1;
    unsigned char middle_index = length / 2;

    /* Memory allocation for diamond matrix */
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
        memset(diamond[i], ' ', length); // Initialize row with spaces
        diamond[i][length] = '\0';      // Null-terminate the row
    }

    /* Fill in diamond matrix */
    for (unsigned char i = 0; i <= middle_index; i++)
    {
        char ch = 'A' + i;
        diamond[i][middle_index - i] = ch;
        diamond[i][middle_index + i] = ch;
        if (i != middle_index)
        {
            memcpy(diamond[length - i - 1], diamond[i], length + 1);
        }
    }

    return diamond;
}