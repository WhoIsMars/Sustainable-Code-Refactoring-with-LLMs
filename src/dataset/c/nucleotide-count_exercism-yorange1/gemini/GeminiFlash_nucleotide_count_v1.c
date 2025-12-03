#include "nucleotide_count.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define BUFFER_SIZE (50)

char *count(const char *dna_strand) {
    if (dna_strand == NULL) {
        return NULL;
    }

    int counts[4] = {0};
    size_t i = 0;
    while (dna_strand[i] != '\0') {
        switch (dna_strand[i]) {
            case 'A':
                counts[0]++;
                break;
            case 'C':
                counts[1]++;
                break;
            case 'G':
                counts[2]++;
                break;
            case 'T':
                counts[3]++;
                break;
            default: {
                char *ret = (char *)calloc(1, BUFFER_SIZE);
                if (ret == NULL) return NULL;
                return ret;
            }
        }
        i++;
    }

    char *ret = (char *)malloc(BUFFER_SIZE);
    if (ret == NULL) {
        return NULL;
    }

    int sprintf_result = sprintf(ret, "A:%d C:%d G:%d T:%d", counts[0], counts[1], counts[2], counts[3]);

    if (sprintf_result < 0 || sprintf_result >= BUFFER_SIZE) {
        free(ret);
        return NULL;
    }

    return ret;
}