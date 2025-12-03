#include "rna_transcription.h"
#include <stdlib.h>
#include <string.h>

char *to_rna(const char *dna) {
    if (dna == NULL || dna[0] == '\0') {
        char *str = (char *)malloc(1);
        if (str != NULL) {
            str[0] = '\0';
        }
        return str;
    }

    size_t dnaLength = strlen(dna);
    char *rna = (char *)malloc(dnaLength + 1);
    if (rna == NULL) {
        return NULL; // Handle memory allocation failure
    }

    for (size_t i = 0; i < dnaLength; i++) {
        switch (dna[i]) {
            case 'G':
                rna[i] = 'C';
                break;
            case 'C':
                rna[i] = 'G';
                break;
            case 'T':
                rna[i] = 'A';
                break;
            case 'A':
                rna[i] = 'U';
                break;
            default:
                free(rna);
                return NULL; // Or handle the error as appropriate
        }
    }

    rna[dnaLength] = '\0';
    return rna;
}