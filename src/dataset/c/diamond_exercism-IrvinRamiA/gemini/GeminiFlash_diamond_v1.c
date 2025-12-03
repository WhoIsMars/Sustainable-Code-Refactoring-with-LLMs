#include "diamond.h"
#include <stdlib.h>
#include <string.h>

char **make_diamond(const char letter)
{
    unsigned char length = 2 * (letter - 'A') + 1;
    unsigned char middle_index = length / 2;

    /* Memory allocation for diamond matrix */
    char **diamond = (char **)malloc(length * sizeof(char *));
    if (!diamond) return NULL;

    for (unsigned char i = 0; i < length; i++)
    {
        diamond[i] = (char *)malloc((length + 1) * sizeof(char));
        if (!diamond[i]) {
            // Handle allocation failure: free previously allocated memory
            for (unsigned char j = 0; j < i; j++) {
                free(diamond[j]);
            }
            free(diamond);
            return NULL;
        }
    }

    /* Initialize diamond matrix */
    for (unsigned char i = 0; i < length; i++)
    {
        memset(diamond[i], ' ', length); // Initialize with spaces using memset
        diamond[i][length] = '\0';       // Null-terminate the string
    }

    /* Fill in diamond matrix */
    for (unsigned char i = 0; i <= middle_index; i++)
    {
        diamond[i][middle_index + i] = 'A' + i;
        diamond[i][middle_index - i] = 'A' + i;
    }

    for (unsigned char i = middle_index + 1; i < length; i++)
    {
        memcpy(diamond[i], diamond[2 * middle_index - i], length + 1);
    }

    return diamond;
}