#include "binary.h"

int convert(const char *input)
{
    int result = 0;

    for (; *input != '\0'; input++)
    {
        if (*input == '1')
        {
            result = (result << 1) | 1;
        }
        else if (*input == '0')
        {
            result <<= 1;
        }
        else
        {
            return INVALID;
        }
    }

    return result;
}