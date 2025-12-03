#include "series.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

slices_t slices(char *input_text, unsigned int substring_length)
{
    slices_t result = {0};
    
    if (substring_length == 0) {
        return result;
    }
    
    size_t len = strlen(input_text);
    
    if (len < substring_length) {
        return result;
    }
    
    size_t total_substrings = len - substring_length + 1;
    
    /* Single memory allocation for all substring pointers */
    result.substring = (char **)malloc(total_substrings * sizeof(char *));
    if (!result.substring) {
        return result;
    }
    
    /* Single memory allocation for all substring data */
    char *data_block = (char *)malloc(total_substrings * (substring_length + 1));
    if (!data_block) {
        free(result.substring);
        result.substring = NULL;
        return result;
    }
    
    /* Assign pointers and copy data efficiently */
    for (size_t i = 0; i < total_substrings; i++) {
        result.substring[i] = data_block + i * (substring_length + 1);
        memcpy(result.substring[i], input_text + i, substring_length);
        result.substring[i][substring_length] = '\0';
        result.substring_count++;
    }
    
    return result;
}