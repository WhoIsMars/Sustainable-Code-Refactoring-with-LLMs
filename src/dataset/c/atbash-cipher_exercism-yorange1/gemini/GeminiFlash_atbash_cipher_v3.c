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

    // Calculate the maximum possible length of the encoded string.
    for (size_t i = 0; i < len; i++) {
        if (isalnum(input[i])) {
            encoded_len++;
            if ((encoded_len % 5) == 0) {
                encoded_len++; // Account for space
            }
        }
    }
    if (encoded_len > 0 && (encoded_len % 6 == 1)) {
        encoded_len--;
    }

    char *cipher = (char *)malloc(encoded_len + 1);
    if (cipher == NULL) return NULL;

    size_t cipher_index = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (isalpha(input[i]))
        {
            cipher[cipher_index] = atbash_alphabet[tolower(input[i]) - 'a'];
            cipher_index++;
        }
        else if (isdigit(input[i]))
        {
            cipher[cipher_index] = input[i];
            cipher_index++;
        }

        if ((cipher_index % 5) == 0 && cipher_index > 0 && cipher_index < encoded_len)
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
    size_t decoded_len = 0;

    for (size_t i = 0; i < len; i++) {
        if (isalnum(input[i])) {
            decoded_len++;
        }
    }

    char *text = (char *)malloc(decoded_len + 1);
    if (text == NULL) return NULL;

    size_t text_index = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (isalpha(input[i]))
        {
            char c = tolower(input[i]);
            for (int j = 0; j < 26; j++) {
                if (atbash_alphabet[j] == c) {
                    text[text_index] = 'a' + j;
                    text_index++;
                    break;
                }
            }
        }
        else if (isdigit(input[i]))
        {
            text[text_index] = input[i];
            text_index++;
        }
    }

    text[text_index] = '\0';

    return text;
}