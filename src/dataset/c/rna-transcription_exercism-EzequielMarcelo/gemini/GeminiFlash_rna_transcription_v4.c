#include "rna_transcription.h"

char *to_rna(const char *dna) {
    if (dna == NULL) {
        return NULL;
    }

    size_t length = strlen(dna);
    char *rna = (char *)malloc((length + 1) * sizeof(char));

    if (rna == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; i++) {
        char nucleotide = dna[i];
        if (nucleotide == 'G') {
            rna[i] = 'C';
        } else if (nucleotide == 'C') {
            rna[i] = 'G';
        } else if (nucleotide == 'T') {
            rna[i] = 'A';
        } else if (nucleotide == 'A') {
            rna[i] = 'U';
        } else {
            free(rna);
            return NULL;
        }
    }

    rna[length] = '\0';
    return rna;
}