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
        memset(diamond[i], ' ', length);
        diamond[i][length] = '\0';
    }

    /* Fill in diamond matrix */
    for (unsigned char i = 0; i <= middle_index; i++)
    {
        char current_letter = 'A' + i;
        diamond[i][middle_index - i] = current_letter;
        diamond[i][middle_index + i] = current_letter;
        
        if (i != middle_index)
        {
            memcpy(diamond[length - 1 - i], diamond[i], length + 1);
        }
    }

    return diamond;
}