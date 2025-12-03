#include "matching_brackets.h"

#include <stddef.h>
#include <string.h>

static inline bool is_match(char left, char right)
{
    return (left == '(' && right == ')') || 
           (left == '[' && right == ']') || 
           (left == '{' && right == '}');
}

bool is_paired(const char *input)
{
    if (!input)
    {
        return false;
    }

    char stack[256];
    size_t sp = 0;

    for (const char *c = input; *c; ++c)
    {
        if (*c == '(' || *c == '[' || *c == '{')
        {
            if (sp >= sizeof(stack))
            {
                return false;
            }
            stack[sp++] = *c;
        }
        else if (*c == ')' || *c == ']' || *c == '}')
        {
            if (sp == 0 || !is_match(stack[--sp], *c))
            {
                return false;
            }
        }
    }

    return sp == 0;
}