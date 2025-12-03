#include "two_fer.h"

#include <string.h>

#define BUFFER_SIZE (100)
#define PREFIX "One for "
#define SUFFIX ", one for me."
#define DEFAULT_NAME "you"
#define PREFIX_LEN 8
#define SUFFIX_LEN 13

void two_fer(char *buffer, const char *name)
{
    const char *target_name = name ? name : DEFAULT_NAME;
    
    memcpy(buffer, PREFIX, PREFIX_LEN);
    
    char *pos = buffer + PREFIX_LEN;
    while (*target_name) {
        *pos++ = *target_name++;
    }
    
    memcpy(pos, SUFFIX, SUFFIX_LEN + 1);
}