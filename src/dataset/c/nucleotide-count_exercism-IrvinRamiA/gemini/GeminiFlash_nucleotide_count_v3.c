#include "nucleotide_count.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *count(const char *dna_strand)
{
    nucleotide_counter_t counter = {0, 0, 0, 0, 0};
    char *result = (char *)malloc(20 * sizeof(char));

    if (!result) return NULL;

    while (*dna_strand != '\0')
    {
        switch (*dna_strand)
        {
        case 'A':
            counter.ctr_a++;
            break;
        case 'C':
            counter.ctr_c++;
            break;
        case 'G':
            counter.ctr_g++;
            break;
        case 'T':
            counter.ctr_t++;
            break;
        default:
            counter.ctr_other++;
            break;
        }

        dna_strand++;
    }

    if (counter.ctr_other)
    {
        result[0] = '\0';
    }
    else
    {
        snprintf(result, 20, "A:%d C:%d G:%d T:%d",
                counter.ctr_a, counter.ctr_c,
                counter.ctr_g, counter.ctr_t);
    }

    return result;
}