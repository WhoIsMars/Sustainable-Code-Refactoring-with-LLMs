#include "two_fer.h"
#include <string.h>

void two_fer(char *buffer, const char *name) {
    if (name) {
        sprintf(buffer, "One for %s, one for me.", name);
    } else {
        strcpy(buffer, "One for you, one for me.");
    }
}