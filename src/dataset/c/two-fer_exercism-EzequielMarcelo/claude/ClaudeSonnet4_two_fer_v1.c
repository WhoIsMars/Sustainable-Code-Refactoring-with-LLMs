#include "two_fer.h"
#include <string.h>

void two_fer(char *buffer, const char *name) 
{
    if (name != NULL && name[0] != '\0') {
        const char prefix[] = "One for ";
        const char suffix[] = ", one for me.";
        
        strcpy(buffer, prefix);
        strcat(buffer, name);
        strcat(buffer, suffix);
    } else {
        strcpy(buffer, "One for you, one for me.");
    }
}