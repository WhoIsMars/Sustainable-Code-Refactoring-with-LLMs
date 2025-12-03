#include "two_fer.h"
#include <string.h>
#include <stdio.h>

void two_fer(char *buffer, const char *name) {
    if (name != NULL && *name != '\0') {
        const char one_for[] = "One for ";
        const char one_for_me[] = ", one for me.";
        size_t name_len = strlen(name);
        size_t one_for_len = sizeof(one_for) - 1;
        size_t one_for_me_len = sizeof(one_for_me) - 1;

        memcpy(buffer, one_for, one_for_len);
        memcpy(buffer + one_for_len, name, name_len);
        memcpy(buffer + one_for_len + name_len, one_for_me, one_for_me_len + 1); // Include null terminator
    } else {
        const char general_msg[] = "One for you, one for me.";
        strcpy(buffer, general_msg);
    }
}