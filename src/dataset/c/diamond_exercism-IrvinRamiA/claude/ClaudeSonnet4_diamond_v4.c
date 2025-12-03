#include "diamond.h"
#include <stdlib.h>
#include <string.h>

char **make_diamond(const char letter)
{
    const unsigned char length = 2 * (letter - 'A') + 1;
    const unsigned char middle_index = length / 2;

    char **diamond = (char **)malloc(length * sizeof(char *));
    
    for (unsigned char i = 0; i <= middle_index; i++)
    {
        diamond[i] = (char *)malloc((length + 1) * sizeof(char));
        memset(diamond[i], ' ', length);
        diamond[i][length] = '\0';
        
        diamond[i][middle_index - i] = 'A' + i;
        if (i > 0)
        {
            diamond[i][middle_index + i] = 'A' + i;
        }
    }
    
    for (unsigned char i = middle_index + 1; i < length; i++)
    {
        unsigned char mirror_index = 2 * middle_index - i;
        diamond[i] = (char *)malloc((length + 1) * sizeof(char));
        memcpy(diamond[i], diamond[mirror_index], length + 1);
    }

    return diamond;
}