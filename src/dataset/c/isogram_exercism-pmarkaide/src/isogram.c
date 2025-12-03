#include "isogram.h"
#include <stdio.h>
#include <ctype.h>

bool is_isogram(const char phrase[])
{
    if(phrase == NULL)
        return false;
    
    int index[26] = {0}; // create emtpy list of counters
    int i = 0;
    int c = 0;

    while (phrase[i] != '\0')
    {
        if (isalpha(phrase[i]))
        {
            c = tolower(phrase[i]) - 'a';
            if (index[c] > 0)
                return false;
            index[c]++;
        }
        i++;
    }
    return true;
}