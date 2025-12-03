#include "series.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

slices_t slices(char *input_text, unsigned int substring_length)
{
    slices_t result = {0};
    if (substring_length == 0 || !input_text) return result;

    uint8_t len = strlen(input_text);
    if (substring_length > len) return result;

    uint8_t total_substrings = len - substring_length + 1;

    result.substring = (char **)malloc(total_substrings * sizeof(char *));
    if (!result.substring) return result;

    for (uint8_t i = 0; i < total_substrings; i++)
    {
        result.substring[i] = strndup(input_text + i, substring_length);
        if (!result.substring[i])
        {
            for (uint8_t j = 0; j < i; j++) free(result.substring[j]);
            free(result.substring);
            result.substring = NULL;
            return result;
        }
        result.substring_count++;
    }

    return result;
}