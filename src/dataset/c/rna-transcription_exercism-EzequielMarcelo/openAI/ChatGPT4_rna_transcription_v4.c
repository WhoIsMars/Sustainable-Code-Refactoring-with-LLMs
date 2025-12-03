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
        char nucleotide = dna[i];
        rna[i] = (nucleotide == 'G') ? 'C' :
                 (nucleotide == 'C') ? 'G' :
                 (nucleotide == 'T') ? 'A' :
                 (nucleotide == 'A') ? 'U' : '\0';
        if (rna[i] == '\0') {
            free(rna);
            return NULL;
        }
    }

    rna[length] = '\0';
    return rna;
}