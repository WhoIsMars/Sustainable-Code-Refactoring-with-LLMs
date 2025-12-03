#include <string.h>
#include <stdio.h>
#include "hamming.h"

int compute(const char *lhs, const char *rhs)
{
    unsigned char lenght1 = strlen(lhs);
    unsigned char lenght2 = strlen(rhs);

    if (lenght1 != lenght2)
    {
        return -1;
    }

    unsigned char counter = 0;
    for(unsigned char i = 0; i < lenght1; i++)
    {
        if(*(lhs + i) != *(rhs + i))
        {
            counter++;
        }
    }

    return counter;
}

/*
int compute(const char *lhs, const char *rhs)
{
    unsigned char lenght1 = strlen(lhs);
    unsigned char lenght2 = strlen(rhs);

    if(lenght1 != lenght2)
    {
        return -1;
    }

    unsigned char counter = 0;
    for(unsigned char i = 0; i < lenght1; i++)
    {
        if(lhs[i] != rhs[i])
        {
            counter++;
        }
    }

    return counter;
}
*/