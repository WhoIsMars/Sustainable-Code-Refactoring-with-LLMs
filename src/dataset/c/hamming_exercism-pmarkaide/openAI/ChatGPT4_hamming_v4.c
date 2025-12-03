#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
    int h = 0;

    for (; *lhs && *rhs; lhs++, rhs++)
    {
        h += (*lhs != *rhs);
    }

    return (*lhs || *rhs) ? -1 : h;
}