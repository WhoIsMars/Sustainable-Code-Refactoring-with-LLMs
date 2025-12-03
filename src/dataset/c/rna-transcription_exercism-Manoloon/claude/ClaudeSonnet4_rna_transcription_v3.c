#include "rna_transcription.h"
#include <stdlib.h>
#include <string.h>

char *to_rna(const char *dna) 
{
    if (dna == NULL) {
        return NULL;
    }
    
    size_t dnaLength = strlen(dna);
    if (dnaLength == 0) {
        char* str = (char*)malloc(1);
        str[0] = '\0';
        return str;
    }
    
    char* str = (char*)malloc(dnaLength + 1);
    if (str == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < dnaLength; i++) {
        switch (dna[i]) {
            case 'G': str[i] = 'C'; break;
            case 'C': str[i] = 'G'; break;
            case 'T': str[i] = 'A'; break;
            case 'A': str[i] = 'U'; break;
            default:
                free(str);
                return NULL;
        }
    }
    str[dnaLength] = '\0';
    return str;
}