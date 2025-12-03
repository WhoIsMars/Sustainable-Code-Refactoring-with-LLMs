#include "pangram.h"

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>

#define ALL_LETTERS_MASK (0x03FFFFFF)

bool is_pangram(const char *sentence)
{
    if (NULL == sentence)
        return false;

    uint32_t flags = 0;
    const char *ptr = sentence;

    while (*ptr && flags != ALL_LETTERS_MASK)
    {
        char c = *ptr;
        if ((c >= 'a' && c <= 'z'))
        {
            flags |= 1U << (c - 'a');
        }
        else if ((c >= 'A' && c <= 'Z'))
        {
            flags |= 1U << (c - 'A');
        }
        ptr++;
    }

    return flags == ALL_LETTERS_MASK;
}