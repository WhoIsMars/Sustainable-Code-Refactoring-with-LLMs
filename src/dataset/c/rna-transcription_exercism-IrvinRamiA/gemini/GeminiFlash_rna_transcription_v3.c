#include "rna_transcription.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *to_rna(const char *dna) {
    size_t len = strlen(dna);
    char *rna_output = malloc((len + 1) * sizeof(char));

    if (rna_output == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; ++i) {
        switch (dna[i]) {
            case 'G':
                rna_output[i] = 'C';
                break;
            case 'C':
                rna_output[i] = 'G';
                break;
            case 'T':
                rna_output[i] = 'A';
                break;
            case 'A':
                rna_output[i] = 'U';
                break;
            default:
                free(rna_output);
                return NULL;
        }
    }

    rna_output[len] = '\0';
    return rna_output;
}