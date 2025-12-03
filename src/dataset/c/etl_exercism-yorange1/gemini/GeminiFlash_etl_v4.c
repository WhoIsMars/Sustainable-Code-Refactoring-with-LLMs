#include "etl.h"

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA_NUM (26)

int convert(const legacy_map *input, const size_t input_len, new_map **output)
{
    size_t count = 0;
    int map_table[ALPHA_NUM] = {0};

    for (size_t i = 0; i < input_len; i++)
    {
        const char *keys = input[i].keys;
        for (const char *key = keys; *key; ++key)
        {
            char lower_key = tolower((unsigned char)*key);
            if (lower_key >= 'a' && lower_key <= 'z')
            {
                if (map_table[lower_key - 'a'] == 0)
                {
                    count++;
                }
                map_table[lower_key - 'a'] = input[i].value;
            }
        }
    }

    *output = (new_map *)malloc(count * sizeof(new_map));
    if (*output == NULL)
    {
        return 0;
    }

    size_t output_index = 0;
    for (size_t i = 0; i < ALPHA_NUM; i++)
    {
        if (map_table[i] != 0)
        {
            (*output)[output_index].key = 'a' + i;
            (*output)[output_index].value = map_table[i];
            output_index++;
        }
    }

    return count;
}