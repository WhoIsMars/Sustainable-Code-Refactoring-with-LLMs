#include "matching_brackets.h"

#include <stddef.h>

static inline bool is_opening_bracket(char c)
{
    return c == '(' || c == '[' || c == '{';
}

static inline bool is_closing_bracket(char c)
{
    return c == ')' || c == ']' || c == '}';
}

static inline bool is_match(char opening, char closing)
{
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

bool is_paired(const char *input)
{
    if (!input)
    {
        return true;
    }

    char stack[256];
    size_t sp = 0;
    
    for (const char *p = input; *p; ++p)
    {
        if (is_opening_bracket(*p))
        {
            if (sp >= 256) return false;
            stack[sp++] = *p;
        }
        else if (is_closing_bracket(*p))
        {
            if (sp == 0 || !is_match(stack[--sp], *p))
            {
                return false;
            }
        }
    }

    return sp == 0;
}