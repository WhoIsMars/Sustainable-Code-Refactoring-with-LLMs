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
    
    // Calculate exact size needed
    size_t output_chars = 0;
    for (size_t i = 0; i < len; i++) {
        if (isalnum(input[i])) {
            output_chars++;
        }
    }
    
    // Add space for group separators (every 5 chars gets a space)
    size_t spaces = output_chars > 0 ? (output_chars - 1) / 5 : 0;
    size_t total_size = output_chars + spaces + 1;
    
    char *cipher = (char *)malloc(total_size);
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

        if (cipher_index % 5 == 0 && cipher_index != 0 && cipher_index < output_chars)
        {
            cipher[cipher_index] = ' ';
            cipher_index++;
        }
    }

    cipher[cipher_index] = '\0';
    return cipher;
}

char *atbash_decode(const char *input)
{
    assert(input != NULL);

    size_t len = strlen(input);
    
    // Calculate exact size needed
    size_t output_chars = 0;
    for (size_t i = 0; i < len; i++) {
        if (isalnum(input[i])) {
            output_chars++;
        }
    }
    
    char *text = (char *)malloc(output_chars + 1);
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
    return text;
}