#include "rna_transcription.h"
#include <string.h>
#include <stdlib.h>

/**
 * @brief Given a DNA strand, return its RNA complement
 *
 * @param dna    input dna
 * @return char* rna string transcription
 *
 * G -> C
 * C -> G
 * T -> A
 * A -> U
 */
char *to_rna(const char *dna)
{
    size_t len = strlen(dna);
    char *rna_output = (char *)malloc((len + 1) * sizeof(char));
    
    if (!rna_output) return NULL;

    static const char translation[256] = {
        ['G'] = 'C',
        ['C'] = 'G',
        ['T'] = 'A',
        ['A'] = 'U'
    };

    for (size_t i = 0; i < len; i++)
    {
        rna_output[i] = translation[(unsigned char)dna[i]];
    }

    rna_output[len] = '\0';

    return rna_output;
}