#include "series.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

slices_t slices(char *input_text, unsigned int substring_length)
{
    slices_t result = {0};
    
    if (!input_text || substring_length == 0) {
        return result;
    }
    
    size_t len = strlen(input_text);
    
    if (len < substring_length) {
        return result;
    }
    
    size_t total_substrings = len - substring_length + 1;
    
    result.substring = (char **)malloc(total_substrings * sizeof(char *));
    if (!result.substring) {
        return result;
    }
    
    char *bulk_memory = (char *)malloc(total_substrings * (substring_length + 1));
    if (!bulk_memory) {
        free(result.substring);
        result.substring = NULL;
        return result;
    }
    
    for (size_t i = 0; i < total_substrings; i++) {
        result.substring[i] = bulk_memory + i * (substring_length + 1);
        memcpy(result.substring[i], input_text + i, substring_length);
        result.substring[i][substring_length] = '\0';
        result.substring_count++;
    }
    
    return result;
}