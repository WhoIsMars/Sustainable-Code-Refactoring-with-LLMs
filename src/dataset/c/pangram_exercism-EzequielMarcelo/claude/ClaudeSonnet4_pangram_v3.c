#include "pangram.h"

bool is_pangram(const char *sentence) 
{
    if (sentence == NULL) 
        return false; 

    uint32_t seen = 0;
    const uint32_t all_letters = (1U << ALPHABET_COUNT) - 1;

    while (*sentence) 
    {
        char c = *sentence;
        
        if (c >= 'A' && c <= 'Z') 
            seen |= 1U << (c - 'A');
        else if (c >= 'a' && c <= 'z') 
            seen |= 1U << (c - 'a');
        
        if (seen == all_letters)
            return true;
            
        sentence++;
    }

    return seen == all_letters;
}