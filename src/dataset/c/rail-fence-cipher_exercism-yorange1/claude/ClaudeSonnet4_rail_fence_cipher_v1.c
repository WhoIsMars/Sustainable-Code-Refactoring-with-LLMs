#include "rail_fence_cipher.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *encode(char *text, size_t rails)
{
    if (NULL == text || 0 == rails)
    {
        return NULL;
    }
    
    size_t length = strlen(text);
    if (0 == length)
    {
        return NULL;
    }

    if (rails == 1)
    {
        char *cipher = malloc(length + 1);
        if (NULL == cipher) return NULL;
        strcpy(cipher, text);
        return cipher;
    }

    char *cipher = malloc(length + 1);
    if (NULL == cipher)
    {
        return NULL;
    }

    size_t cipher_idx = 0;
    
    for (size_t rail = 0; rail < rails; rail++)
    {
        size_t step = 2 * (rails - 1);
        size_t pos = rail;
        
        while (pos < length)
        {
            cipher[cipher_idx++] = text[pos];
            
            if (rail != 0 && rail != rails - 1)
            {
                size_t next_pos = pos + step - 2 * rail;
                if (next_pos < length)
                {
                    cipher[cipher_idx++] = text[next_pos];
                }
            }
            
            pos += step;
        }
    }
    
    cipher[length] = '\0';
    return cipher;
}

char *decode(char *ciphertext, size_t rails)
{
    if (NULL == ciphertext || 0 == rails)
    {
        return NULL;
    }
    
    size_t length = strlen(ciphertext);
    if (0 == length)
    {
        return NULL;
    }

    if (rails == 1)
    {
        char *text = malloc(length + 1);
        if (NULL == text) return NULL;
        strcpy(text, ciphertext);
        return text;
    }

    char *text = malloc(length + 1);
    if (NULL == text)
    {
        return NULL;
    }

    size_t cipher_idx = 0;
    
    for (size_t rail = 0; rail < rails; rail++)
    {
        size_t step = 2 * (rails - 1);
        size_t pos = rail;
        
        while (pos < length)
        {
            text[pos] = ciphertext[cipher_idx++];
            
            if (rail != 0 && rail != rails - 1)
            {
                size_t next_pos = pos + step - 2 * rail;
                if (next_pos < length)
                {
                    text[next_pos] = ciphertext[cipher_idx++];
                }
            }
            
            pos += step;
        }
    }
    
    text[length] = '\0';
    return text;
}