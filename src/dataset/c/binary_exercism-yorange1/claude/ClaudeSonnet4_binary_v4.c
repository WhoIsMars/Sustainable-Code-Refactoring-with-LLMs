#include "binary.h"

#include <stddef.h>

int convert(const char *input)
{
    if (!input) return INVALID;
    
    int result = 0;
    const char *ptr = input;
    
    while (*ptr) {
        char c = *ptr++;
        if (c != '0' && c != '1') {
            return INVALID;
        }
        result = (result << 1) | (c & 1);
    }
    
    return result;
}