#include "rna_transcription.h"
#include <string.h>
#include <stdlib.h>

char *to_rna(const char *dna)
{
    if (!dna) return NULL;
    
    size_t len = strlen(dna);
    char *rna_output = (char *)malloc((len + 1) * sizeof(char));
    
    if (!rna_output) return NULL;
    
    static const char transcription_map[256] = {
        ['G'] = 'C',
        ['C'] = 'G', 
        ['T'] = 'A',
        ['A'] = 'U'
    };
    
    for (size_t i = 0; i < len; i++) {
        rna_output[i] = transcription_map[(unsigned char)dna[i]];
    }
    
    rna_output[len] = '\0';
    
    return rna_output;
}