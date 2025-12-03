#include "rna_transcription.h"
#include <string.h>
#include <stdlib.h>

char *to_rna(const char *dna)
{
    size_t len = strlen(dna);
    char *rna_output = malloc(len + 1);
    
    if (!rna_output) return NULL;
    
    static const char lookup[256] = {
        ['G'] = 'C',
        ['C'] = 'G', 
        ['T'] = 'A',
        ['A'] = 'U'
    };
    
    for (size_t i = 0; i < len; i++) {
        rna_output[i] = lookup[(unsigned char)dna[i]];
    }
    
    rna_output[len] = '\0';
    return rna_output;
}