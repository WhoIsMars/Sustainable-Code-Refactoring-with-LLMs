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
            int bit_pos = (*p & 0x1F) - 1;
            
            if (seen & (1U << bit_pos)) 
                return false;
        
            seen |= (1U << bit_pos);
        }
    }

    return true;
}