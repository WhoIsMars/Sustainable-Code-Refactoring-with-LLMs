#include "rna_transcription.h"

#include <stdlib.h>
#include <stddef.h>

// G -> C
// C -> G
// T -> A
// A -> U

static const char transcription_map[256] = {
    ['G'] = 'C',
    ['C'] = 'G',
    ['T'] = 'A',
    ['A'] = 'U'
};

char *to_rna(const char *dna)
{
    if (NULL == dna)
    {
        return NULL;
    }

    const char *p = dna;
    size_t length = 0;
    
    // Calculate length and validate in single pass
    while (*p)
    {
        char transcribed = transcription_map[(unsigned char)*p];
        if (transcribed == 0)
        {
            return NULL;
        }
        length++;
        p++;
    }

    char *ret_str = (char *)malloc(length + 1);
    if (!ret_str)
    {
        return NULL;
    }

    // Transcribe characters
    for (size_t i = 0; i < length; i++)
    {
        ret_str[i] = transcription_map[(unsigned char)dna[i]];
    }
    
    ret_str[length] = '\0';
    return ret_str;
}