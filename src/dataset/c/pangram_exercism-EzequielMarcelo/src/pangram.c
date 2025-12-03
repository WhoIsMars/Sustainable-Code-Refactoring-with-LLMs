#include "pangram.h"

bool is_pangram(const char *sentence) 
{
    if (sentence == NULL) 
        return false; 

    bool seen[ALPHABET_COUNT] = {false};

    while (*sentence) 
    {
        char c = tolower(*sentence); 

        if (c >= 'a' && c <= 'z') 
            seen[c - 'a'] = true; 
        
        sentence++;
    }

    for (int i = 0; i < ALPHABET_COUNT; i++) 
    {
        if (!seen[i]) 
            return false; 
    }

    return true;
}