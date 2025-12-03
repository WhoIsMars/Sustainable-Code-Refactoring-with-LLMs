#include "two_fer.h"
#include <stdio.h>
#include <string.h>

void two_fer(char *buffer, const char *name)
{
    const char *default_name = "you";
    if (name == NULL) {
        name = default_name;
    }
    snprintf(buffer, strlen("One for , one for me.") + strlen(name) + 1, "One for %s, one for me.", name);
}