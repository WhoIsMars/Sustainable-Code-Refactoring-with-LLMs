#include "reverse_string.h"

#include <string.h>
#include <stdlib.h>

char* reverse(const char* string) {
    int len = strlen(string);
    char* new_string = malloc(len + 1);
    
    new_string[len] = '\0';
    
    for (int i = 0; i < len; ++i) {
        new_string[i] = string[len - 1 - i];
    }

    return new_string;
}