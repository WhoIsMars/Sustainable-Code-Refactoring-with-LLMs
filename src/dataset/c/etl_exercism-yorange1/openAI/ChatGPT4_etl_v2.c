#include "etl.h"

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA_NUM (26)

int convert(const legacy_map *input, const size_t input_len, new_map **output)
{
    int map_table[ALPHA_NUM] = {0};
    size_t count = 0;

    for (size_t i = 0; i < input_len; i++)
    {
        for (const char *keys = input[i].keys; *keys != '\0'; keys++)
        {
            int index = tolower(*keys) - 'a';
            if (map_table[index] == 0) // Avoid overwriting existing values
            {
                map_table[index] = input[i].value;
                count++;
            }
        }
    }

    *output = (new_map *)malloc(count * sizeof(new_map)); // Allocate only required memory
    if (*output == NULL)
    {
        return -1; // Return error if memory allocation fails
    }

    count = 0;
    for (int i = 0; i < ALPHA_NUM; i++)
    {
        if (map_table[i] != 0)
        {
            (*output)[count].key = 'a' + i;
            (*output)[count].value = map_table[i];
            count++;
        }
    }

    return count;
}