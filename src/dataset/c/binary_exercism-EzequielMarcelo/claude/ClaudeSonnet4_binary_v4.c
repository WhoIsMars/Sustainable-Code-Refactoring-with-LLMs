#include "binary.h"

int convert(const char *input) 
{
    if (input == NULL) 
        return INVALID;

    int decimal = 0;
    const char *ptr = input;
    
    while (*ptr) {
        char c = *ptr++;
        if (c == '1') {
            decimal = (decimal << 1) | 1;
        } else if (c == '0') {
            decimal <<= 1;
        } else {
            return INVALID;
        }
    }
    
    return decimal;
}