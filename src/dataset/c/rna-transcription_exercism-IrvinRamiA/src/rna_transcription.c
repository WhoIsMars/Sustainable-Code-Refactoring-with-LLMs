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
    unsigned char len = strlen(dna);
    char *rna_output = (char *)malloc(len * sizeof(char));

    for (unsigned char i = 0; i < len; i++)
    {
        switch (*(dna + i))
        {
        case 'G':
            *(rna_output + i) = 'C';
            break;
        case 'C':
            *(rna_output + i) = 'G';
            break;
        case 'T':
            *(rna_output + i) = 'A';
            break;
        case 'A':
            *(rna_output + i) = 'U';
            break;
        default:
            break;
        }
    }

    rna_output[len] = '\0';

    return rna_output;
}
