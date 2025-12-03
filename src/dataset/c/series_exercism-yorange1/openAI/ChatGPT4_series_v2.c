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

    if (len < substring_length || substring_length == 0)
    {
        return (slices_t){0, NULL};
    }

    result.substring_count = len - substring_length + 1;
    result.substring = malloc(result.substring_count * sizeof(char *));
    assert(result.substring != NULL);

    for (size_t i = 0; i < result.substring_count; i++)
    {
        result.substring[i] = strndup(&input_text[i], substring_length);
        assert(result.substring[i] != NULL);
    }

    return result;
}