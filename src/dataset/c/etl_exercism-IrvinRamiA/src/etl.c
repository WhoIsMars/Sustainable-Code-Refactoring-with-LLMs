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
    unsigned char output_length = 0;
    unsigned char output_index = 0;

    /* Calculating output length */
    for (unsigned char i = 0; i < input_len; i++)
    {
        output_length += strlen(input[i].keys);
    }

    /* Memory allocation for output map */
    *output = (new_map *)malloc(output_length * sizeof(new_map));

    /* Checking each character */
    for (unsigned char i = 0; i < input_len; i++)
    {
        for (unsigned j = 0; j < strlen(input[i].keys); j++)
        {
            (*output)[output_index].key = tolower(input[i].keys[j]);
            (*output)[output_index++].value = input[i].value;
        }
    }

    qsort(*output, output_length, sizeof(new_map), compare);

    return output_length;
}
