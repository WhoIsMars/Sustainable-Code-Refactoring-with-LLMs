#include "pangram.h"

bool is_pangram(const char *sentence) 
{
    if (sentence == NULL) 
        return false; 

    int seen_count = 0;
    bool seen[ALPHABET_COUNT] = {false};

    while (*sentence && seen_count < ALPHABET_COUNT) 
    {
        char c = *sentence;
        
        if (c >= 'A' && c <= 'Z') 
            c += 32;
        
        if (c >= 'a' && c <= 'z') 
        {
            int index = c - 'a';
            if (!seen[index]) 
            {
                seen[index] = true;
                seen_count++;
            }
        }
        
        sentence++;
    }

    return seen_count == ALPHABET_COUNT;
}