/**
 * "GATTACA" -> 'A': 3, 'C': 1, 'G': 1, 'T': 2
 * "INVALID" -> error
 */

#include "nucleotide_count.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *count(const char *dna_strand)
{
    nucleotide_counter_t counter = {0, 0, 0, 0, 0};
    char *result = (char *)malloc(20 * sizeof(char));

    while (*dna_strand != '\0')
    {
        if (*dna_strand == 'A')
        {
            counter.ctr_a++;        
        }
        else if (*dna_strand == 'C')
        {
            counter.ctr_c++;
        }
        else if (*dna_strand == 'G')
        {
            counter.ctr_g++;
        }
        else if (*dna_strand == 'T')
        {
            counter.ctr_t++;
        }
        else
        {
            counter.ctr_other++;
        }

        dna_strand++;
    }

    if (counter.ctr_other)
    {
        // result[0] = '\0';
        strcpy(result, "");
    }
    else
    {
        sprintf(result, "A:%d C:%d G:%d T:%d",
                counter.ctr_a, counter.ctr_c,
                counter.ctr_g, counter.ctr_t);
    }

    return result;
}
