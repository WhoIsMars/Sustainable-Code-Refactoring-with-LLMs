#include "series.h"

#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

slices_t slices(char *input_text, unsigned int substring_length)
{
    assert(input_text != NULL);

    size_t len = strlen(input_text);
    if (len < substring_length || substring_length == 0)
    {
        return (slices_t){0, NULL};
    }

    size_t substring_count = len - substring_length + 1;
    char **substrings = malloc(substring_count * sizeof(char *));
    assert(substrings != NULL);

    for (size_t i = 0; i < substring_count; i++)
    {
        substrings[i] = strndup(&input_text[i], substring_length);
        assert(substrings[i] != NULL);
    }

    return (slices_t){substring_count, substrings};
}