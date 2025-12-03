#include "two_fer.h"
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE (100)

void two_fer(char *buffer, const char *name) {
    const char *actual_name = (name != NULL) ? name : "you";
    size_t name_len = strlen(actual_name);

    if (name_len > BUFFER_SIZE - 16) {
        strncpy(buffer, "One for , one for me.", BUFFER_SIZE);
        buffer[BUFFER_SIZE - 1] = '\0';
        return;
    }

    snprintf(buffer, BUFFER_SIZE, "One for %s, one for me.", actual_name);
}