#include "rna_transcription.h"

char *to_rna(const char *dna) 
{
    if (dna == NULL) 
        return NULL;

    size_t length = strlen(dna);
    char *rna = (char *)malloc(length + 1);
    if (rna == NULL) 
        return NULL;

    for (size_t i = 0; i < length; i++) 
    {
        if (dna[i] == 'G') rna[i] = 'C';
        else if (dna[i] == 'C') rna[i] = 'G';
        else if (dna[i] == 'T') rna[i] = 'A';
        else if (dna[i] == 'A') rna[i] = 'U';
        else {
            free(rna);
            return NULL;
        }
    }

    rna[length] = '\0';
    return rna;
}