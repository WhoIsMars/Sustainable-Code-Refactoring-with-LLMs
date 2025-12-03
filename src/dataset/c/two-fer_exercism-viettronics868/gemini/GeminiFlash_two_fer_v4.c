#include "two_fer.h"
#include <string.h>
#include <stdio.h>

void two_fer(char *buffer, const char *name) {
    if (name == NULL || *name == '\0') {
        strcpy(buffer, "One for you, one for me.");
    } else {
        strcpy(buffer, "One for ");
        strcat(buffer, name);
        strcat(buffer, ", one for me.");
    }
}