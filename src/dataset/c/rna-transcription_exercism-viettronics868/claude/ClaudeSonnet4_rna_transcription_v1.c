#include "rna_transcription.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

char *to_rna(const char *dna){
    size_t leng_dna = strlen(dna);
    char *rna = (char *)malloc(leng_dna + 1);
    if(rna == NULL) return NULL;
    
    static const char translation[256] = {
        ['G'] = 'C',
        ['C'] = 'G', 
        ['T'] = 'A',
        ['A'] = 'U'
    };
    
    for (size_t i = 0; i < leng_dna; i++){
        char translated = translation[(unsigned char)dna[i]];
        if (translated == 0) {
            free(rna);
            return NULL;
        }
        rna[i] = translated;
    }
    rna[leng_dna] = '\0';
    return rna;
}