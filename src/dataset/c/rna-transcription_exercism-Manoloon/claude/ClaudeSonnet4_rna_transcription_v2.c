#include "rna_transcription.h"
#include <stdlib.h>
#include <string.h>

char *to_rna(const char *dna) 
{
    if (dna == NULL || dna[0] == '\0') {
        char* str = (char*)malloc(1);
        str[0] = '\0';
        return str;
    }
    
    size_t dnaLength = strlen(dna);
    char* str = (char*)malloc(dnaLength + 1);
    
    for(size_t i = 0; i < dnaLength; i++)
    {
        char nucleotide = dna[i];
        if (nucleotide == 'G') str[i] = 'C';
        else if (nucleotide == 'C') str[i] = 'G';
        else if (nucleotide == 'T') str[i] = 'A';
        else if (nucleotide == 'A') str[i] = 'U';
        else {
            free(str);
            return NULL;
        }
    }
    str[dnaLength] = '\0';
    return str;
}