#include "two_fer.h"
#include <string.h>

void two_fer(char *buffer, const char *name) 
{
    const char *default_name = "you";
    const char *use_name = (name && name[0] != '\0') ? name : default_name;
    snprintf(buffer, 100, "One for %s, one for me.", use_name);
}