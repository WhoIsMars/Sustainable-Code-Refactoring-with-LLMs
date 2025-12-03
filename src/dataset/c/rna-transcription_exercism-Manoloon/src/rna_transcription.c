#include "rna_transcription.h"
#include <stdlib.h>
#include <string.h>
char *to_rna(const char *dna) 
{
    if (dna == NULL || dna[0] == '\0') {
        char* str = (char*)malloc(1 * sizeof(char));
        str[0] = '\0';
        return str;
    }
    size_t dnaLength = strlen(dna);
    char* str = (char*)malloc(dnaLength+1);
    for(size_t i = 0; i < dnaLength;i++)
    {
        switch (dna[i])
        {
            case 'G': str[i]='C'; break;
            case 'C': str[i]='G'; break;
            case 'T': str[i]='A'; break;
            case 'A': str[i]='U'; break;        
        default:
            free(str);
            break;
        }
    }
    str[dnaLength] = '\0';
    return str;
}
