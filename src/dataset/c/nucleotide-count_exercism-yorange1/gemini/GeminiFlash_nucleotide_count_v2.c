#include "nucleotide_count.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE (50)

char *count(const char *dna_strand) {
    if (dna_strand == NULL) {
        return NULL;
    }

    size_t length = 0;
    while (dna_strand[length] != '\0') {
        length++;
    }

    int counts[4] = {0};
    char *ret = (char *)malloc(BUFFER_SIZE);

    if (ret == NULL) {
        return NULL;
    }

    bool valid = true;
    for (size_t i = 0; i < length; i++) {
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
            default:
                valid = false;
                break;
        }
        if (!valid) break;
    }

    if (!valid) {
        ret[0] = '\0';
        return ret;
    }

    int written = snprintf(ret, BUFFER_SIZE, "A:%d C:%d G:%d T:%d", counts[0], counts[1], counts[2], counts[3]);

    if (written >= BUFFER_SIZE) {
        free(ret);
        return NULL;
    }

    return ret;
}