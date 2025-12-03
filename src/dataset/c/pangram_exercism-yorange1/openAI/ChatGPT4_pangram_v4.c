#include "pangram.h"

#include <ctype.h>
#include <stdint.h>

#define FLAGS_EXCEPT (0x03FFFFFF)

bool is_pangram(const char *sentence)
{
    if (!sentence)
        return false;

    uint32_t flags = 0;

    for (const char *ptr = sentence; *ptr; ++ptr)
    {
        if (isalpha((unsigned char)*ptr))
        {
            flags |= 1U << (tolower((unsigned char)*ptr) - 'a');
            if (flags == FLAGS_EXCEPT)
                return true;
        }
    }

    return false;
}