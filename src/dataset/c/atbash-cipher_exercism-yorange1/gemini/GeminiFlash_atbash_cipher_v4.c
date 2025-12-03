#include "atbash_cipher.h"

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static const char atbash_alphabet[26] = {'z', 'y', 'x', 'w', 'v', 'u', 't', 's', 'r', 'q',
                                         'p', 'o', 'n', 'm', 'l', 'k', 'j', 'i', 'h', 'g',
                                         'f', 'e', 'd', 'c', 'b', 'a'};

char *atbash_encode(const char *input)
{
    assert(input != NULL);

    size_t len = strlen(input);
    size_t encoded_len = 0;

    // Calculate the maximum possible length of the encoded string
    for (size_t i = 0; i < len; ++i) {
        if (isalnum(input[i])) {
            encoded_len++;
        }
    }
    encoded_len += (encoded_len > 0) ? (encoded_len - 1) / 5 : 0; // Add spaces
    encoded_len++; // Null terminator

    char *cipher = (char *)malloc(encoded_len);
    if (cipher == NULL) return NULL;

    size_t cipher_index = 0;
    size_t char_count = 0;

    for (size_t i = 0; i < len; ++i)
    {
        if (isalnum(input[i]))
        {
            char c = tolower(input[i]);
            if (isalpha(c))
            {
                cipher[cipher_index++] = atbash_alphabet[c - 'a'];
            }
            else
            {
                cipher[cipher_index++] = c;
            }

            char_count++;
            if (char_count % 5 == 0 && char_count != 0 && cipher_index < encoded_len -1)
            {
                cipher[cipher_index++] = ' ';
            }
        }
    }

    if (cipher_index > 0 && cipher[cipher_index - 1] == ' ')
    {
        cipher[cipher_index - 1] = '\0';
    } else {
        cipher[cipher_index] = '\0';
    }

    return cipher;
}

char *atbash_decode(const char *input)
{
    assert(input != NULL);

    size_t len = strlen(input);
    size_t decoded_len = 0;

    for (size_t i = 0; i < len; ++i) {
        if (isalnum(input[i])) {
            decoded_len++;
        }
    }
    decoded_len++; // Null terminator

    char *text = (char *)malloc(decoded_len);
    if (text == NULL) return NULL;

    size_t text_index = 0;
    for (size_t i = 0; i < len; ++i)
    {
        if (isalnum(input[i]))
        {
            char c = tolower(input[i]);
            if (isalpha(c))
            {
                text[text_index++] = atbash_alphabet[c - 'a'];
            }
            else
            {
                text[text_index++] = c;
            }
        }
    }

    text[text_index] = '\0';
    return text;
}