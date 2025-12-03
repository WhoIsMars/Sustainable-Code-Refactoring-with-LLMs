#include "reverse_string.h"

#include <string.h>
#include <stdlib.h>

char* reverse(const char* string) {
    size_t len = strlen(string);
    char* new_string = malloc(sizeof(char) * (len + 1));

    if (new_string == NULL) {
        return NULL; // Handle allocation failure
    }

    for (size_t i = 0; i < len; ++i) {
        new_string[i] = string[len - 1 - i];
    }

    new_string[len] = '\0'; // Null-terminate the string

    return new_string;
}