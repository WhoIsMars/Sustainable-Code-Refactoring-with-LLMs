#include "rna_transcription.h"

#include <string.h>
#include <stdlib.h>

char *to_rna(const char *dna)
{
    if (!dna) return NULL;
    
    const size_t len = strlen(dna);
    char *rna = malloc(len + 1);
    if (!rna) return NULL;
    
    static const char translation[256] = {
        ['G'] = 'C',
        ['C'] = 'G',
        ['T'] = 'A',
        ['A'] = 'U'
    };
    
    for (size_t i = 0; i < len; ++i) {
        rna[i] = translation[(unsigned char)dna[i]];
    }
    rna[len] = '\0';
    
    return rna;
}