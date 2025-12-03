#include "nucleotide_count.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *count(const char *dna_strand)
{
    int ctr_a = 0, ctr_c = 0, ctr_g = 0, ctr_t = 0;

    for (; *dna_strand; dna_strand++)
    {
        switch (*dna_strand)
        {
        case 'A':
            ctr_a++;
            break;
        case 'C':
            ctr_c++;
            break;
        case 'G':
            ctr_g++;
            break;
        case 'T':
            ctr_t++;
            break;
        default:
            return strdup("");
        }
    }

    char *result = (char *)malloc(32);
    snprintf(result, 32, "A:%d C:%d G:%d T:%d", ctr_a, ctr_c, ctr_g, ctr_t);
    return result;
}