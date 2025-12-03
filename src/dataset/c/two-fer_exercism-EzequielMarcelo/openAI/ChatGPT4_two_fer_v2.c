#include "two_fer.h"

void two_fer(char *buffer, const char *name) 
{
    const char *target = (name && *name) ? name : "you";
    snprintf(buffer, 100, "One for %s, one for me.", target);
}