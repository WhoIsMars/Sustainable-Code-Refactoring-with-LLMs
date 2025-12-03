#include "two_fer.h"

#include <string.h>

#define BUFFER_SIZE (100)

void two_fer(char *buffer, const char *name)
{
    static const char prefix[] = "One for ";
    static const char suffix[] = ", one for me.";
    static const char default_name[] = "you";
    
    const char *target_name = name ? name : default_name;
    
    char *pos = buffer;
    
    memcpy(pos, prefix, sizeof(prefix) - 1);
    pos += sizeof(prefix) - 1;
    
    size_t name_len = strlen(target_name);
    memcpy(pos, target_name, name_len);
    pos += name_len;
    
    memcpy(pos, suffix, sizeof(suffix));
}