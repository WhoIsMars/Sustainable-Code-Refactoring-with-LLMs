#include "reverse_string.h"

#include <string.h>
#include <stdlib.h>

char* reverse(const char* string) {
    char* new_string = malloc(sizeof(char) * strlen(string));

    int end = strlen(string) - 1;
    for (int i = 0; i <= end; ++i) {
        new_string[i] = string[end - i];
    }

    return new_string;
}
