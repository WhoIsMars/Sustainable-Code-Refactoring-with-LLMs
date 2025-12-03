#include "secret_handshake.h"
#include <stdlib.h>

const char **commands(size_t number)
{
    static const char* command_strings[] = {
        "wink",
        "double blink", 
        "close your eyes",
        "jump"
    };
    
    // Count set bits in first 4 positions
    unsigned char result_len = 0;
    for (unsigned char i = 0; i < 4; i++) {
        if (number & (1 << i)) {
            result_len++;
        }
    }
    
    // Allocate result array
    char **result = (char **)malloc((result_len + 1) * sizeof(char *));
    if (result_len == 0) {
        result[0] = NULL;
        return (const char **)result;
    }
    
    unsigned char index = 0;
    
    // Check if we need to reverse (bit 4 set)
    if (number & 16) { // bit 4 is set
        // Add commands in reverse order
        for (int i = 3; i >= 0; i--) {
            if (number & (1 << i)) {
                result[index++] = (char*)command_strings[i];
            }
        }
    } else {
        // Add commands in normal order
        for (unsigned char i = 0; i < 4; i++) {
            if (number & (1 << i)) {
                result[index++] = (char*)command_strings[i];
            }
        }
    }
    
    result[index] = NULL;
    return (const char **)result;
}