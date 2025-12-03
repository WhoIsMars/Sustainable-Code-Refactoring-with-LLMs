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
    size_t output_index = 0;
    
    for (size_t i = 0; i < input_len; i++)
    {
        output_length += strlen(input[i].keys);
    }
    
    *output = (new_map *)malloc(output_length * sizeof(new_map));
    if (!*output) return -1;
    
    for (size_t i = 0; i < input_len; i++)
    {
        const char *keys = input[i].keys;
        const size_t key_len = strlen(keys);
        const int value = input[i].value;
        
        for (size_t j = 0; j < key_len; j++)
        {
            (*output)[output_index].key = tolower((unsigned char)keys[j]);
            (*output)[output_index].value = value;
            output_index++;
        }
    }
    
    qsort(*output, output_length, sizeof(new_map), compare);
    
    return (int)output_length;
}