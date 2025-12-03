#include "two_fer.h"
#include <string.h>
#include <stdio.h>

void two_fer(char *buffer, const char *name) 
{
    if (name == 0)
    {
        strcpy(buffer, "One for you, one for me.");
        return;
    }
    sprintf(buffer, "One for %s, one for me.", name);
}