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
    int counters[4] = {0}; // A, C, G, T
    const char *ptr = dna_strand;
    
    // Single pass validation and counting
    while (*ptr) {
        switch (*ptr) {
            case 'A': counters[0]++; break;
            case 'C': counters[1]++; break;
            case 'G': counters[2]++; break;
            case 'T': counters[3]++; break;
            default:
                {
                    char *result = (char *)malloc(1);
                    result[0] = '\0';
                    return result;
                }
        }
        ptr++;
    }
    
    char *result = (char *)malloc(20);
    sprintf(result, "A:%d C:%d G:%d T:%d", 
            counters[0], counters[1], counters[2], counters[3]);
    
    return result;
}