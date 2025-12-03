#include "rna_transcription.h"
#include <string.h>
#include <stdlib.h>

char *to_rna(const char *dna) {
    if (!dna) return NULL;
    size_t leng_dna = strlen(dna);
    char *rna = (char *)malloc((leng_dna + 1) * sizeof(char));
    if (!rna) return NULL;

    for (size_t i = 0; i < leng_dna; i++) {
        switch (dna[i]) {
            case 'G': rna[i] = 'C'; break;
            case 'C': rna[i] = 'G'; break;
            case 'T': rna[i] = 'A'; break;
            case 'A': rna[i] = 'U'; break;
            default: free(rna); return NULL;
        }
    }
    rna[leng_dna] = '\0';
    return rna;
}