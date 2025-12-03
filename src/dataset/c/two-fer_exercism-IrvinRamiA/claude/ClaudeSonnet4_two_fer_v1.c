#include "two_fer.h"
#include <string.h>

void two_fer(char *buffer, const char *name)
{
    static const char prefix[] = "One for ";
    static const char suffix[] = ", one for me.";
    static const char default_name[] = "you";
    
    const char *target_name = name ? name : default_name;
    
    char *ptr = buffer;
    
    // Copy prefix
    memcpy(ptr, prefix, sizeof(prefix) - 1);
    ptr += sizeof(prefix) - 1;
    
    // Copy name
    size_t name_len = strlen(target_name);
    memcpy(ptr, target_name, name_len);
    ptr += name_len;
    
    // Copy suffix and null terminator
    memcpy(ptr, suffix, sizeof(suffix));
}