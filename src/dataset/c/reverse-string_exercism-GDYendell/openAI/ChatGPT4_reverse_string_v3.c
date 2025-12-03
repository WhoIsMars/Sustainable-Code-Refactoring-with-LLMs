#include "reverse_string.h"

#include <string.h>
#include <stdlib.h>

char* reverse(const char* string) {
    size_t length = strlen(string);
    char* new_string = malloc(length + 1);
    if (!new_string) return NULL;

    for (size_t i = 0; i < length; ++i) {
        new_string[i] = string[length - 1 - i];
    }
    new_string[length] = '\0';

    return new_string;
}