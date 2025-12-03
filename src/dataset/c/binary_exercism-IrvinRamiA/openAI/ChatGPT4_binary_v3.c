#include "binary.h"

int convert(const char *input)
{
    int result = 0;

    for (; *input != '\0'; input++)
    {
        result <<= 1;
        if (*input == '1')
        {
            result |= 1;
        }
        else if (*input != '0')
        {
            return INVALID;
        }
    }

    return result;
}