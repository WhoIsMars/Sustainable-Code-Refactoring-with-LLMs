#include "diamond.h"
#include <stdlib.h>
#include <string.h>

char **make_diamond(const char letter)
{
    unsigned char length = 2 * (letter - 'A') + 1;
    unsigned char middle_index = length / 2;

    /* Allocate memory for diamond matrix */
    char **diamond = (char **)malloc(length * sizeof(char *));
    if (!diamond)
        return NULL;

    for (unsigned char i = 0; i < length; i++)
    {
        diamond[i] = (char *)malloc((length + 1) * sizeof(char));
        if (!diamond[i])
        {
            for (unsigned char k = 0; k < i; k++)
                free(diamond[k]);
            free(diamond);
            return NULL;
        }
        memset(diamond[i], ' ', length); // Initialize row with spaces
        diamond[i][length] = '\0';       // Null-terminate each row
    }

    /* Fill in diamond matrix */
    for (unsigned char i = 0; i <= middle_index; i++)
    {
        diamond[i][middle_index + i] = 'A' + i;
        diamond[i][middle_index - i] = 'A' + i;
        if (i != middle_index)
        {
            memcpy(diamond[length - i - 1], diamond[i], length + 1); // Mirror rows
        }
    }

    return diamond;
}