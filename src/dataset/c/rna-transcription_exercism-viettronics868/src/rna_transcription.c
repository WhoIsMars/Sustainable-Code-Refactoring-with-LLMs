#include "rna_transcription.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

char *to_rna(const char *dna){
    size_t leng_dna = strlen(dna);
    char *rna = (char *)calloc(leng_dna, sizeof(char));
    if(rna == NULL) return NULL;
    for (size_t i = 0; i < leng_dna; i++){
        switch (dna[i]){
            case 'G': {rna[i] = 'C'; break;}
            case 'C': {rna[i] = 'G'; break;}
            case 'T': {rna[i] = 'A'; break;}
            case 'A': {rna[i] = 'U'; break;}
            default: {free(rna); return NULL;}
        }
    }
    return rna;
}