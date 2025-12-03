#include "diamond.h"
#include <stdlib.h>
#include <string.h>

char **make_diamond(const char letter)
{
    const unsigned char length = 2 * (letter - 'A') + 1;
    const unsigned char middle_index = length / 2;

    char **diamond = (char **)malloc(length * sizeof(char *));
    if (!diamond) return NULL;

    for (unsigned char i = 0; i < length; i++)
    {
        diamond[i] = (char *)malloc((length + 1) * sizeof(char));
        if (!diamond[i]) {
            for (unsigned char k = 0; k < i; k++) free(diamond[k]);
            free(diamond);
            return NULL;
        }
        
        memset(diamond[i], ' ', length);
        diamond[i][length] = '\0';
    }

    for (unsigned char i = 0; i <= middle_index; i++)
    {
        const char current_letter = 'A' + i;
        const unsigned char left_pos = middle_index - i;
        const unsigned char right_pos = middle_index + i;
        
        diamond[i][left_pos] = current_letter;
        if (left_pos != right_pos) {
            diamond[i][right_pos] = current_letter;
        }
        
        if (i != middle_index) {
            const unsigned char mirror_row = length - 1 - i;
            diamond[mirror_row][left_pos] = current_letter;
            if (left_pos != right_pos) {
                diamond[mirror_row][right_pos] = current_letter;
            }
        }
    }

    return diamond;
}