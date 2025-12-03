#include "secret_handshake.h"
#include <stdlib.h>

const char **commands(size_t number)
{
    static const char* command_map[] = {
        "wink",
        "double blink", 
        "close your eyes",
        "jump"
    };
    
    unsigned char bit_count = 0;
    unsigned char temp_number = number & 0x0F;
    
    while (temp_number) {
        bit_count += temp_number & 1;
        temp_number >>= 1;
    }
    
    char **result = (char **)malloc((bit_count + 1) * sizeof(char *));
    if (!result) return NULL;
    
    if (bit_count == 0) {
        result[0] = NULL;
        return (const char **)result;
    }
    
    unsigned char index = 0;
    for (unsigned char i = 0; i < 4; i++) {
        if (number & (1 << i)) {
            result[index++] = (char*)command_map[i];
        }
    }
    
    if (number & 16) {
        for (unsigned char i = 0; i < bit_count / 2; i++) {
            char *temp = result[i];
            result[i] = result[bit_count - 1 - i];
            result[bit_count - 1 - i] = temp;
        }
    }
    
    result[bit_count] = NULL;
    return (const char **)result;
}