#include "series.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

slices_t slices(char *input_text, unsigned int substring_length)
{
    uint8_t len = strlen(input_text);
    slices_t result = {0};
    uint8_t total_substrings = (len - substring_length) + 1;

    /* Memory allocation for output substrings */
    result.substring = (char **)malloc(total_substrings * sizeof(char *));

    for (uint8_t i = 0; i < total_substrings; i++)
    {
        result.substring[i] = (char *)malloc((substring_length + 1) * sizeof(char));
    }

    /* Assigning slices in output structure */
    if (substring_length != 0)
    {
        for (uint8_t i = 0; i < total_substrings; i++)
        {
            strncpy(result.substring[result.substring_count++], input_text, substring_length);
            result.substring[result.substring_count - 1][substring_length] = '\0';

            input_text++;
        }
    }

    return result;
}

/*
For example, the string "49142" (len = 5) has the following 3-digit series:
    "491"
    "914"
    "142"
len - subtring_len = 5 - 3 = 2 -> iterations from index 0 to index 2

And the following 4-digit series:
    "4914"
    "9142"
len - subtring_len = 5 - 4 = 1 -> iterations from index 0 to index 1
*/
