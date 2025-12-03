#include "diamond.h"
#include <stdlib.h>

char **make_diamond(const char letter)
{
    unsigned char length = 2 * (letter - 'A') + 1;
    unsigned char middle_index = length / 2;

    /* Memory allocation for diamond matrix */
    char **diamond = (char **)malloc(length * sizeof(char *));
    for (unsigned char i = 0; i < length; i++)
    {
        diamond[i] = (char *)malloc((length + 1) * sizeof(char));
    }

    /* Initialize diamond matrix */
    for (unsigned char i = 0; i < length; i++)
    {
        for (unsigned char j = 0; j < length + 1; j++)
        {
            if (j == length)
            {
                diamond[i][j] = '\0';
            }
            else
            {
                diamond[i][j] = ' ';
            }
        }
    }

    /* Fill in diamond matrix */
    for (unsigned char i = 0; i < length; i++)
    {
        for (unsigned char j = 0; j < length; j++)
        {
            if (i <= middle_index)
            {
                if (j == middle_index + i || j == middle_index - i)
                {
                    diamond[i][j] = 'A' + i;
                }
            }
            else
            {
                diamond[i][j] = diamond[2 * middle_index - i][j];
            }
        }
    }

    return diamond;
}
