#include "pangram.h"

bool is_pangram(const char *sentence) 
{
    if (sentence == NULL) 
        return false; 

    unsigned int seen = 0;
    const unsigned int all_letters = (1U << ALPHABET_COUNT) - 1;

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