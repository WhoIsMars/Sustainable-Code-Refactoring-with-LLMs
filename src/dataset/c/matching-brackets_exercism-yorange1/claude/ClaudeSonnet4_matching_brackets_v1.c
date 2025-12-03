#include "matching_brackets.h"

#include <stddef.h>

static inline bool is_opening(char c)
{
    return c == '(' || c == '[' || c == '{';
}

static inline bool is_closing(char c)
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
    if (input == NULL)
    {
        return false;
    }

    char stack[256];
    size_t sp = 0;

    for (const char *p = input; *p; p++)
    {
        if (is_opening(*p))
        {
            if (sp >= 256) return false;
            stack[sp++] = *p;
        }
        else if (is_closing(*p))
        {
            if (sp == 0 || !is_match(stack[--sp], *p))
            {
                return false;
            }
        }
    }

    return sp == 0;
}