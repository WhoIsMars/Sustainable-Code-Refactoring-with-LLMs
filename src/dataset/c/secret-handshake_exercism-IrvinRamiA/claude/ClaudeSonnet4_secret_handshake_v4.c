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
    
    unsigned char bits = number & 0x1F;
    unsigned char count = 0;
    unsigned char temp = bits & 0x0F;
    
    while (temp) {
        count += temp & 1;
        temp >>= 1;
    }
    
    if (count == 0) {
        char **result = (char **)malloc(sizeof(char *));
        result[0] = NULL;
        return (const char **)result;
    }
    
    char **result = (char **)malloc(count * sizeof(char *));
    unsigned char index = 0;
    
    for (unsigned char i = 0; i < 4; i++) {
        if (bits & (1 << i)) {
            result[index++] = (char*)command_strings[i];
        }
    }
    
    if (bits & 0x10) {
        for (unsigned char i = 0; i < count / 2; i++) {
            char *temp = result[i];
            result[i] = result[count - 1 - i];
            result[count - 1 - i] = temp;
        }
    }
    
    return (const char **)result;
}