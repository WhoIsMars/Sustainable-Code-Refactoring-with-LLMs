#include "hamming.h"
#include <string.h>

int compute(const char *lhs, const char *rhs)
{
	int h = 0;
	if (strlen(lhs) != strlen(rhs))
		return -1;

    while (*lhs)
    {
        if (*lhs++ != *rhs++)
            h++;
    }

    return h;
}