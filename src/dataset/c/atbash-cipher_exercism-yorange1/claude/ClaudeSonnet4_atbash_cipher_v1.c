#include "atbash_cipher.h"

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *atbash_encode(const char *input)
{
    assert(input != NULL);

    size_t len = strlen(input);
    
    // Calculate exact size needed: alphanumeric chars + spaces every 5 chars + null terminator
    size_t max_output = len + (len / 5) + 1;
    char *cipher = (char *)malloc(max_output);
    assert(cipher != NULL);

    size_t cipher_index = 0;

    for (size_t i = 0; i < len; i++)
    {
        char c = input[i];
        if (isalpha(c))
        {
            cipher[cipher_index] = 'z' - (tolower(c) - 'a');
            cipher_index++;
        }
        else if (isdigit(c))
        {
            cipher[cipher_index] = c;
            cipher_index++;
        }

        if ((cipher_index + 1) % 6 == 0 && cipher_index != 0)
        {
            cipher[cipher_index] = ' ';
            cipher_index++;
        }
    }

    if (cipher_index > 0 && cipher[cipher_index - 1] == ' ')
    {
        cipher_index--;
    }
    
    cipher[cipher_index] = '\0';
    
    // Resize to actual size used
    cipher = (char *)realloc(cipher, cipher_index + 1);
    assert(cipher != NULL);

    return cipher;
}

char *atbash_decode(const char *input)
{
    assert(input != NULL);

    size_t len = strlen(input);
    char *text = (char *)malloc(len + 1);
    assert(text != NULL);

    size_t text_index = 0;
    for (size_t i = 0; i < len; i++)
    {
        char c = input[i];
        if (isalpha(c))
        {
            text[text_index] = 'z' - (tolower(c) - 'a');
            text_index++;
        }
        else if (isdigit(c))
        {
            text[text_index] = c;
            text_index++;
        }
    }

    text[text_index] = '\0';
    
    // Resize to actual size used
    text = (char *)realloc(text, text_index + 1);
    assert(text != NULL);

    return text;
}