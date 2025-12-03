#include "matching_brackets.h"

#include <stddef.h>

bool is_paired(const char *input)
{
    if (NULL == input)
    {
        return false;
    }

    char stack[256];  // Fixed size stack for typical use cases
    size_t sp = 0;
    
    for (const char *p = input; *p; p++)
    {
        char c = *p;
        
        if (c == '(' || c == '[' || c == '{')
        {
            stack[sp++] = c;
        }
        else if (c == ')' || c == ']' || c == '}')
        {
            if (sp == 0)
            {
                return false;
            }
            
            char left = stack[--sp];
            
            if ((c == ')' && left != '(') ||
                (c == ']' && left != '[') ||
                (c == '}' && left != '{'))
            {
                return false;
            }
        }
    }

    return (0 == sp);
}