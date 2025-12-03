#include "two_fer.h"
#include <string.h>

void two_fer(char *buffer, const char *name) {
    if (name && *name) {
        size_t name_len = strnlen(name, 90);
        snprintf(buffer, 100, "One for %.*s, one for me.", (int)name_len, name);
    } else {
        strcpy(buffer, "One for you, one for me.");
    }
}