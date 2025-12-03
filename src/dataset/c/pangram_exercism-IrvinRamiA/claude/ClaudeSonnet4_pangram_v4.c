#include "pangram.h"
#include <stdint.h>

bool is_pangram(const char *sentence)
{
    if (sentence == NULL)
    {
        return false;
    }

    uint32_t alphabet_mask = 0;
    const uint32_t complete_mask = 0x3FFFFFF;

    while (*sentence != '\0')
    {
        char c = *sentence;
        if (c >= 'A' && c <= 'Z')
        {
            alphabet_mask |= (1U << (c - 'A'));
        }
        else if (c >= 'a' && c <= 'z')
        {
            alphabet_mask |= (1U << (c - 'a'));
        }
        
        if (alphabet_mask == complete_mask)
        {
            return true;
        }
        
        sentence++;
    }

    return alphabet_mask == complete_mask;
}