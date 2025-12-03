#include "rna_transcription.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

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

    static const char translation[256] = {
        ['G'] = 'C',
        ['C'] = 'G', 
        ['T'] = 'A',
        ['A'] = 'U'
    };

    for (size_t i = 0; i < length; i++)
    {
        char translated = translation[(unsigned char)dna[i]];
        if (translated == 0)
        {
            free(ret_str);
            return NULL;
        }
        ret_str[i] = translated;
    }

    ret_str[length] = '\0';
    return ret_str;
}