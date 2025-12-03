#include "secret_handshake.h"
#include <stdlib.h>

const char **commands(size_t number)
{
    static const char* command_map[4] = {
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
    
    // Fill commands based on bit positions
    for (unsigned char i = 0; i < 4; i++) {
        if (number & (1 << i)) {
            result[index++] = (char*)command_map[i];
        }
    }
    
    // Reverse if 5th bit is set
    if (number & (1 << 4)) {
        for (unsigned char i = 0; i < result_len / 2; i++) {
            char *temp = result[i];
            result[i] = result[result_len - 1 - i];
            result[result_len - 1 - i] = temp;
        }
    }
    
    result[result_len] = NULL;
    return (const char **)result;
}