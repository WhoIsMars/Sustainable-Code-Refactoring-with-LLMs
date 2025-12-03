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

    while (*ptr && flags != FLAGS_EXCEPT)
    {
        if (isalpha(*ptr))
        {
            flags |= 1 << (tolower(*ptr) - 'a');
        }
        ptr++;
    }

    return (flags == FLAGS_EXCEPT);
}