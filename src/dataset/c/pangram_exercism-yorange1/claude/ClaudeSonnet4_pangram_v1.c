#include "pangram.h"

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>

#define FLAGS_EXCEPT (0x03FFFFFF)

bool is_pangram(const char *sentence)
{
    if (NULL == sentence)
        return false;

    uint32_t flags = 0;
    const char *ptr = sentence;

    while (*ptr)
    {
        if ((*ptr >= 'a' && *ptr <= 'z'))
        {
            flags |= 1 << (*ptr - 'a');
        }
        else if ((*ptr >= 'A' && *ptr <= 'Z'))
        {
            flags |= 1 << (*ptr - 'A');
        }
        
        if (flags == FLAGS_EXCEPT)
            return true;
            
        ptr++;
    }

    return false;
}