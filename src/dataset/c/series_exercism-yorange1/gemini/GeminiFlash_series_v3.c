#include "series.h"

#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

slices_t slices(char *input_text, unsigned int substring_length)
{
    assert(input_text != NULL);

    slices_t result = {0};
    size_t len = strlen(input_text);

    if (len < substring_length || 0 == len || 0 == substring_length)
    {
        return (slices_t){0, NULL};
    }

    result.substring_count = (len - (substring_length - 1));
    result.substring = malloc(result.substring_count * sizeof(char *));
    if (result.substring == NULL) return (slices_t){0, NULL};

    for (size_t i = 0; i < result.substring_count; i++)
    {
        result.substring[i] = malloc(substring_length + 1);
        if (result.substring[i] == NULL) {
            // Cleanup allocated memory in case of failure
            for (size_t j = 0; j < i; j++) {
                free(result.substring[j]);
            }
            free(result.substring);
            return (slices_t){0, NULL};
        }

        strncpy(result.substring[i], &input_text[i], substring_length);
        result.substring[i][substring_length] = '\0';
    }

    return result;
}