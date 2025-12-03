#include "two_fer.h"

#include <string.h>

#define BUFFER_SIZE (100)

void two_fer(char *buffer, const char *name)
{
    static const char prefix[] = "One for ";
    static const char suffix[] = ", one for me.";
    static const char default_name[] = "you";
    
    const char *actual_name = name ? name : default_name;
    
    char *ptr = buffer;
    
    memcpy(ptr, prefix, sizeof(prefix) - 1);
    ptr += sizeof(prefix) - 1;
    
    size_t name_len = strlen(actual_name);
    memcpy(ptr, actual_name, name_len);
    ptr += name_len;
    
    memcpy(ptr, suffix, sizeof(suffix));
}