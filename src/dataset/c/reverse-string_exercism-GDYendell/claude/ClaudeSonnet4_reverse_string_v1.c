#include "reverse_string.h"

#include <string.h>
#include <stdlib.h>

char* reverse(const char* string) {
    size_t len = strlen(string);
    char* new_string = malloc(len + 1);
    
    if (!new_string) return NULL;
    
    new_string[len] = '\0';
    
    for (size_t i = 0; i < len; ++i) {
        new_string[i] = string[len - 1 - i];
    }

    return new_string;
}