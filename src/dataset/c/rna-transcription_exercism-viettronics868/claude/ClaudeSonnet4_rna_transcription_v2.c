#include "rna_transcription.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

char *to_rna(const char *dna){
    size_t leng_dna = strlen(dna);
    char *rna = (char *)malloc(leng_dna + 1);
    if(rna == NULL) return NULL;
    
    for (size_t i = 0; i < leng_dna; i++){
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
    rna[leng_dna] = '\0';
    return rna;
}