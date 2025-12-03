#include "atbash_cipher.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static const char atbash_alphabet[26] = {'z', 'y', 'x', 'w', 'v', 'u', 't', 's', 'r', 'q',
                                         'p', 'o', 'n', 'm', 'l', 'k', 'j', 'i', 'h', 'g',
                                         'f', 'e', 'd', 'c', 'b', 'a'};

char *atbash_encode(const char *input)
{
    assert(input != NULL);

    size_t len = strlen(input);
    size_t estimated_size = len + len / 5 + 1; // Account for spaces and null terminator
    char *cipher = (char *)malloc(estimated_size);
    assert(cipher != NULL);

    size_t cipher_index = 0, group_count = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (isalpha(input[i]))
        {
            cipher[cipher_index++] = atbash_alphabet[tolower(input[i]) - 'a'];
            group_count++;
        }
        else if (isdigit(input[i]))
        {
            cipher[cipher_index++] = input[i];
            group_count++;
        }

        if (group_count == 5 && i < len - 1)
        {
            cipher[cipher_index++] = ' ';
            group_count = 0;
        }
    }

    if (cipher_index > 0 && cipher[cipher_index - 1] == ' ')
    {
        cipher_index--; // Remove trailing space
    }

    cipher[cipher_index] = '\0';
    return cipher;
}

char *atbash_decode(const char *input)
{
    assert(input != NULL);

    size_t len = strlen(input);
    char *text = (char *)malloc(len + 1); // No extra space needed for decoding
    assert(text != NULL);

    size_t text_index = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (isalpha(input[i]))
        {
            text[text_index++] = atbash_alphabet[tolower(input[i]) - 'a'];
        }
        else if (isdigit(input[i]))
        {
            text[text_index++] = input[i];
        }
    }

    text[text_index] = '\0';
    return text;
}