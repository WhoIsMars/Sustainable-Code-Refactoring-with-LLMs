#include "series.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

slices_t slices(char *input_text, unsigned int substring_length)
{
    uint8_t len = strlen(input_text);
    slices_t result = {0};

    if (substring_length == 0 || substring_length > len)
    {
        result.substring = NULL;
        return result;
    }

    uint8_t total_substrings = len - substring_length + 1;

    /* Memory allocation for output substrings */
    result.substring = (char **)malloc(total_substrings * sizeof(char *));
    if (!result.substring)
        return result;

    for (uint8_t i = 0; i < total_substrings; i++)
    {
        result.substring[i] = input_text + i;
    }

    result.substring_count = total_substrings;

    return result;
}