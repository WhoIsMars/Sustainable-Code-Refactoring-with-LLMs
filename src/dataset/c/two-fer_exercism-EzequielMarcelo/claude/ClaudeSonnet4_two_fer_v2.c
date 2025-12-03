#include "two_fer.h"
#include <string.h>

void two_fer(char *buffer, const char *name) 
{
    if (name && *name) {
        const char prefix[] = "One for ";
        const char suffix[] = ", one for me.";
        
        char *ptr = buffer;
        memcpy(ptr, prefix, sizeof(prefix) - 1);
        ptr += sizeof(prefix) - 1;
        
        size_t name_len = strlen(name);
        memcpy(ptr, name, name_len);
        ptr += name_len;
        
        memcpy(ptr, suffix, sizeof(suffix));
    } else {
        memcpy(buffer, "One for you, one for me.", 25);
    }
}