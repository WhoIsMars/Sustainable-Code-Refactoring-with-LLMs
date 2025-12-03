#include "isogram.h"

bool is_isogram(const char phrase[]) 
{
    if (phrase == NULL) 
        return false;

    uint32_t seen = 0;

    for (const char *p = phrase; *p != '\0'; ++p) 
    {
        if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z')) 
        {
            char c = *p | 0x20;
            uint32_t bit = 1U << (c - 'a');
            
            if (seen & bit) 
                return false;
        
            seen |= bit;
        }
    }

    return true;
}