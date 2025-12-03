#include "rna_transcription.h"

char *to_rna(const char *dna) 
{
    if (dna == NULL) 
        return NULL;

    size_t length = strlen(dna);
    char *rna = (char *)malloc(length + 1);

    if (rna == NULL) 
        return NULL;

    for (size_t i = 0; dna[i] != '\0'; i++) 
    {
        rna[i] = (dna[i] == 'G') ? 'C' :
                 (dna[i] == 'C') ? 'G' :
                 (dna[i] == 'T') ? 'A' :
                 (dna[i] == 'A') ? 'U' : '\0';
    }

    rna[length] = '\0';
    return rna;
}