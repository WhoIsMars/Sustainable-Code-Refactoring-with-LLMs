#include "two_fer.h"

void two_fer(char *buffer, const char *name) 
{
    if (name != NULL && name[0] != '\0') 
        snprintf(buffer, 100, "One for %s, one for me.", name);  
     else 
        snprintf(buffer, 100, "One for you, one for me.");      
}
