#include "isogram.h"

bool is_isogram(const char phrase[]) 
{
    if (phrase == NULL) 
        return false;

    bool seen[26] = {false};

    for (const char *p = phrase; *p != '\0'; ++p) 
    {
        if (isalpha(*p)) 
        {
            char c = tolower(*p);
            
            if (seen[c - 'a']) 
                return false;
        
            seen[c - 'a'] = true;
        }
    }

    return true;
}
