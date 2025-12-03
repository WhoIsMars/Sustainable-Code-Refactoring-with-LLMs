#include "two_fer.h"
#include <string.h>
#include <stdio.h>

void two_fer(char *buffer, const char *name) {
    if (name) {
        snprintf(buffer, strlen("One for , one for me.") + strlen(name) + 1, "One for %s, one for me.", name);
    } else {
        strcpy(buffer, "One for you, one for me.");
    }
}