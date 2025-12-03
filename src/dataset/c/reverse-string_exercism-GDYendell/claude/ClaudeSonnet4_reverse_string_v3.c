#include "reverse_string.h"

#include <string.h>
#include <stdlib.h>

char* reverse(const char* string) {
    if (!string) return NULL;
    
    size_t len = strlen(string);
    char* new_string = malloc(len + 1);
    
    if (!new_string) return NULL;
    
    const char* src = string + len - 1;
    char* dst = new_string;
    
    while (src >= string) {
        *dst++ = *src--;
    }
    
    *dst = '\0';
    
    return new_string;
}