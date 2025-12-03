#include "binary.h"
#include <string.h>

int convert(const char *input)
{
    if (!input || *input == '\0') {
        return 0;
    }
    
    int result = 0;
    const char *ptr = input;
    
    while (*ptr != '\0') {
        if (*ptr == '1') {
            result = (result << 1) | 1;
        } else if (*ptr == '0') {
            result <<= 1;
        } else {
            return INVALID;
        }
        ptr++;
    }
    
    return result;
}