#include "hamming.h"
#include <stddef.h>

int compute(const char *lhs, const char *rhs)
{
    if (!lhs || !rhs)
        return -1;

    int h = 0;
    for (size_t i = 0; lhs[i] && rhs[i]; i++)
    {
        if (lhs[i] != rhs[i])
            h++;
    }

    return (lhs[h] || rhs[h]) ? -1 : h;
}