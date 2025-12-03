#include "atbash_cipher.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static const char atbash_alphabet[26] = "zyxwvutsrqponmlkjihgfedcba";

char *atbash_encode(const char *input)
{
    assert(input != NULL);

    size_t len = strlen(input);
    char *cipher = (char *)malloc(len * 2 / 5 + len + 1);
    assert(cipher != NULL);

    size_t cipher_index = 0, group_count = 0;

    for (size_t i = 0; i < len; i++)
    {
        char c = input[i];
        if (isalpha(c))
        {
            cipher[cipher_index++] = atbash_alphabet[tolower(c) - 'a'];
            group_count++;
        }
        else if (isdigit(c))
        {
            cipher[cipher_index++] = c;
            group_count++;
        }

        if (group_count == 5)
        {
            cipher[cipher_index++] = ' ';
            group_count = 0;
        }
    }

    if (cipher_index > 0 && cipher[cipher_index - 1] == ' ')
        cipher_index--;

    cipher[cipher_index] = '\0';
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
            text[text_index++] = atbash_alphabet[tolower(c) - 'a'];
        }
        else if (isdigit(c))
        {
            text[text_index++] = c;
        }
    }

    text[text_index] = '\0';
    return text;
}