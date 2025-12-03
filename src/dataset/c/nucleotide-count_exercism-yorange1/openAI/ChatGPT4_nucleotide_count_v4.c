#include "nucleotide_count.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE (50)

char *count(const char *dna_strand)
{
    if (!dna_strand)
    {
        return NULL;
    }

    int count[4] = {0};
    for (const char *ptr = dna_strand; *ptr; ++ptr)
    {
        switch (*ptr)
        {
        case 'A':
            count[0]++;
            break;
        case 'C':
            count[1]++;
            break;
        case 'G':
            count[2]++;
            break;
        case 'T':
            count[3]++;
            break;
        default:
            return NULL;
        }
    }

    char *ret = (char *)malloc(BUFFER_SIZE);
    if (!ret)
    {
        return NULL;
    }

    snprintf(ret, BUFFER_SIZE, "A:%d C:%d G:%d T:%d", count[0], count[1], count[2], count[3]);
    return ret;
}