#include "two_fer.h"
#include <string.h>

void two_fer(char *buffer, const char *name) {
    const char* default_name = "you";
    const char* name_to_use = (name != NULL && name[0] != '\0') ? name : default_name;

    size_t name_len = strlen(name_to_use);
    size_t buffer_size = 14 + name_len + 14 + 1;

    if (buffer_size > 100) {
        buffer[0] = '\0';
        return;
    }

    memcpy(buffer, "One for ", 8);
    memcpy(buffer + 8, name_to_use, name_len);
    memcpy(buffer + 8 + name_len, ", one for me.", 14);
    buffer[8 + name_len + 14] = '\0';
}