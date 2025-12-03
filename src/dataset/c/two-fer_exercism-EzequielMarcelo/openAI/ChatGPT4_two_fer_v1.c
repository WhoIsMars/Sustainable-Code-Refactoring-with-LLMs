#include "two_fer.h"
#include <string.h>

void two_fer(char *buffer, const char *name) 
{
    const char *default_name = "you";
    snprintf(buffer, 100, "One for %s, one for me.", (name && *name) ? name : default_name);
}