#include "rna_transcription.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

char *to_rna(const char *dna)
{
    if (!dna)
    {
        return NULL;
    }

    size_t length = strlen(dna);
    char *ret_str = (char *)malloc(length + 1);
    if (!ret_str)
    {
        return NULL;
    }

    for (size_t i = 0; i < length; i++)
    {
        switch (dna[i])
        {
        case 'G':
            ret_str[i] = 'C';
            break;
        case 'C':
            ret_str[i] = 'G';
            break;
        case 'T':
            ret_str[i] = 'A';
            break;
        case 'A':
            ret_str[i] = 'U';
            break;
        default:
            free(ret_str);
            return NULL;
        }
    }

    ret_str[length] = '\0';
    return ret_str;
}