#include "rna_transcription.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// G -> C
// C -> G
// T -> A
// A -> U

char *to_rna(const char *dna)
{
    if (NULL == dna)
    {
        return NULL;
    }

    size_t length = strlen(dna);
    char *ret_str = (char *)malloc(length + 1);
    
    if (NULL == ret_str)
    {
        return NULL;
    }

    for (size_t i = 0; i < length; i++)
    {
        char nucleotide = dna[i];
        if (nucleotide == 'G')
            ret_str[i] = 'C';
        else if (nucleotide == 'C')
            ret_str[i] = 'G';
        else if (nucleotide == 'T')
            ret_str[i] = 'A';
        else if (nucleotide == 'A')
            ret_str[i] = 'U';
        else
        {
            free(ret_str);
            return NULL;
        }
    }

    ret_str[length] = '\0';
    return ret_str;
}