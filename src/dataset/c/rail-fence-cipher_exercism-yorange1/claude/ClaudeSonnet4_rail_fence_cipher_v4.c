#include "rail_fence_cipher.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *encode(char *text, size_t rails)
{
    if (!text || rails == 0) {
        return NULL;
    }
    
    size_t length = strlen(text);
    if (length == 0) {
        return NULL;
    }
    
    if (rails == 1) {
        char *result = malloc(length + 1);
        if (!result) return NULL;
        memcpy(result, text, length + 1);
        return result;
    }

    char *cipher = malloc(length + 1);
    if (!cipher) {
        return NULL;
    }
    
    size_t cipher_idx = 0;
    
    for (size_t rail = 0; rail < rails; rail++) {
        size_t pos = rail;
        int direction = (rail == 0 || rail == rails - 1) ? 1 : 0;
        
        while (pos < length) {
            cipher[cipher_idx++] = text[pos];
            
            if (rail == 0) {
                pos += 2 * (rails - 1);
            } else if (rail == rails - 1) {
                pos += 2 * (rails - 1);
            } else {
                if (direction) {
                    pos += 2 * (rails - 1 - rail);
                } else {
                    pos += 2 * rail;
                }
                direction = !direction;
            }
        }
    }
    
    cipher[length] = '\0';
    return cipher;
}

char *decode(char *ciphertext, size_t rails)
{
    if (!ciphertext || rails == 0) {
        return NULL;
    }
    
    size_t length = strlen(ciphertext);
    if (length == 0) {
        return NULL;
    }
    
    if (rails == 1) {
        char *result = malloc(length + 1);
        if (!result) return NULL;
        memcpy(result, ciphertext, length + 1);
        return result;
    }

    char *text = malloc(length + 1);
    if (!text) {
        return NULL;
    }
    
    size_t cipher_idx = 0;
    
    for (size_t rail = 0; rail < rails; rail++) {
        size_t pos = rail;
        int direction = (rail == 0 || rail == rails - 1) ? 1 : 0;
        
        while (pos < length) {
            text[pos] = ciphertext[cipher_idx++];
            
            if (rail == 0) {
                pos += 2 * (rails - 1);
            } else if (rail == rails - 1) {
                pos += 2 * (rails - 1);
            } else {
                if (direction) {
                    pos += 2 * (rails - 1 - rail);
                } else {
                    pos += 2 * rail;
                }
                direction = !direction;
            }
        }
    }
    
    text[length] = '\0';
    return text;
}