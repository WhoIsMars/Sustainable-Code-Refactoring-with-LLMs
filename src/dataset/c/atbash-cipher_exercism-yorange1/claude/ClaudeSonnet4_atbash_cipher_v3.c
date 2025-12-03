#include "atbash_cipher.h"

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static inline char atbash_transform(char c) {
    return 'z' - (c - 'a');
}

static size_t calculate_encoded_length(const char *input) {
    size_t len = strlen(input);
    size_t valid_chars = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (isalnum(input[i])) {
            valid_chars++;
        }
    }
    
    return valid_chars + (valid_chars > 0 ? (valid_chars - 1) / 5 : 0) + 1;
}

static size_t calculate_decoded_length(const char *input) {
    size_t len = strlen(input);
    size_t valid_chars = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (isalnum(input[i])) {
            valid_chars++;
        }
    }
    
    return valid_chars + 1;
}

char *atbash_encode(const char *input)
{
    assert(input != NULL);

    size_t output_len = calculate_encoded_length(input);
    char *cipher = (char *)malloc(output_len);
    assert(cipher != NULL);

    size_t cipher_index = 0;
    size_t input_len = strlen(input);

    for (size_t i = 0; i < input_len; i++)
    {
        char c = input[i];
        
        if (isalpha(c))
        {
            cipher[cipher_index] = atbash_transform(tolower(c));
            cipher_index++;
        }
        else if (isdigit(c))
        {
            cipher[cipher_index] = c;
            cipher_index++;
        }
        else
        {
            continue;
        }

        if (cipher_index % 5 == 0 && i < input_len - 1)
        {
            size_t remaining = input_len - i - 1;
            for (size_t j = i + 1; j < input_len; j++) {
                if (isalnum(input[j])) {
                    cipher[cipher_index] = ' ';
                    cipher_index++;
                    break;
                }
            }
        }
    }

    cipher[cipher_index] = '\0';
    return cipher;
}

char *atbash_decode(const char *input)
{
    assert(input != NULL);

    size_t output_len = calculate_decoded_length(input);
    char *text = (char *)malloc(output_len);
    assert(text != NULL);

    size_t text_index = 0;
    size_t input_len = strlen(input);
    
    for (size_t i = 0; i < input_len; i++)
    {
        char c = input[i];
        
        if (isalpha(c))
        {
            text[text_index] = atbash_transform(tolower(c));
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