#include "series.h"

#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

slices_t slices(char *input_text, unsigned int substring_length)
{
    assert(input_text != NULL);

    if (substring_length == 0) {
        return (slices_t){0, NULL};
    }

    size_t len = strlen(input_text);
    
    if (len < substring_length) {
        return (slices_t){0, NULL};
    }

    slices_t result;
    result.substring_count = len - substring_length + 1;
    
    result.substring = malloc(result.substring_count * sizeof(char *));
    assert(result.substring != NULL);

    char *buffer = malloc(result.substring_count * (substring_length + 1));
    assert(buffer != NULL);

    for (size_t i = 0; i < result.substring_count; i++) {
        result.substring[i] = buffer + i * (substring_length + 1);
        memcpy(result.substring[i], &input_text[i], substring_length);
        result.substring[i][substring_length] = '\0';
    }

    return result;
}