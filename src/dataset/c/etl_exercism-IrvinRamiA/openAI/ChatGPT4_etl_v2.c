#include "etl.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static int compare(const void *a, const void *b)
{
    return ((new_map *)a)->key - ((new_map *)b)->key;
}

int convert(const legacy_map *input, const size_t input_len, new_map **output)
{
    size_t output_length = 0;

    // Calculate output length and allocate memory in one pass
    for (size_t i = 0; i < input_len; i++)
    {
        output_length += strlen(input[i].keys);
    }

    *output = (new_map *)malloc(output_length * sizeof(new_map));
    if (!*output)
    {
        return 0; // Return 0 if memory allocation fails
    }

    size_t output_index = 0;

    // Populate output map
    for (size_t i = 0; i < input_len; i++)
    {
        const char *keys = input[i].keys;
        size_t keys_len = strlen(keys);

        for (size_t j = 0; j < keys_len; j++)
        {
            (*output)[output_index].key = tolower(keys[j]);
            (*output)[output_index].value = input[i].value;
            output_index++;
        }
    }

    // Sort the output map
    qsort(*output, output_length, sizeof(new_map), compare);

    return (int)output_length;
}