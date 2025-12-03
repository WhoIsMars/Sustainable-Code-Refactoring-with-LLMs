/**
 * "GATTACA" -> 'A': 3, 'C': 1, 'G': 1, 'T': 2
 * "INVALID" -> error
 */

#include "nucleotide_count.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *count(const char *dna_strand) {
    nucleotide_counter_t counter = {0, 0, 0, 0, 0};
    const char *ptr = dna_strand;

    while (*ptr) {
        switch (*ptr) {
            case 'A': counter.ctr_a++; break;
            case 'C': counter.ctr_c++; break;
            case 'G': counter.ctr_g++; break;
            case 'T': counter.ctr_t++; break;
            default:  counter.ctr_other++; break;
        }
        ptr++;
    }

    char *result = (char *)malloc(20 * sizeof(char));
    if (!result) return NULL; // Handle potential allocation failure

    if (counter.ctr_other) {
        result[0] = '\0'; // More efficient than strcpy for empty string
    } else {
        int written = snprintf(result, 20, "A:%d C:%d G:%d T:%d",
                               counter.ctr_a, counter.ctr_c,
                               counter.ctr_g, counter.ctr_t);
        if (written >= 20) {
            free(result);
            return NULL; // Or handle the error as appropriate
        }
    }

    return result;
}