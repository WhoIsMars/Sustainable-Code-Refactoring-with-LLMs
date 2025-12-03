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

    // Calculate output length
    for (size_t i = 0; i < input_len; i++)
    {
        output_length += strlen(input[i].keys);
    }

    // Allocate memory for output map
    *output = (new_map *)malloc(output_length * sizeof(new_map));
    if (!*output)
    {
        return 0; // Return 0 if memory allocation fails
    }

    // Populate output map
    size_t output_index = 0;
    for (size_t i = 0; i < input_len; i++)
    {
        const char *keys = input[i].keys;
        int value = input[i].value;
        for (const char *p = keys; *p; p++)
        {
            (*output)[output_index].key = tolower((unsigned char)*p);
            (*output)[output_index].value = value;
            output_index++;
        }
    }

    // Sort the output map
    qsort(*output, output_length, sizeof(new_map), compare);

    return (int)output_length;
}