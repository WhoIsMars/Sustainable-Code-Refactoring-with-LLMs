#include "atbash_cipher.h"

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static const char atbash_alphabet[26] = {'z', 'y', 'x', 'w', 'v', 'u', 't', 's', 'r', 'q',
                                         'p', 'o', 'n', 'm', 'l', 'k', 'j', 'i', 'h', 'g',
                                         'f', 'e', 'd', 'c', 'b', 'a'};

static inline char atbash_transform(char c) {
    return atbash_alphabet[c - 'a'];
}

static inline int is_alphanumeric(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

static inline char to_lower(char c) {
    return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}

char *atbash_encode(const char *input)
{
    assert(input != NULL);

    size_t len = strlen(input);
    size_t max_output_len = len + (len / 5) + 1;
    
    char *cipher = (char *)calloc(max_output_len + 1, 1);
    assert(cipher != NULL);

    size_t cipher_index = 0;
    size_t group_count = 0;

    for (size_t i = 0; i < len; i++)
    {
        char c = input[i];
        char lower_c = to_lower(c);
        
        if (lower_c >= 'a' && lower_c <= 'z')
        {
            cipher[cipher_index++] = atbash_transform(lower_c);
            group_count++;
        }
        else if (c >= '0' && c <= '9')
        {
            cipher[cipher_index++] = c;
            group_count++;
        }

        if (group_count == 5 && i < len - 1)
        {
            size_t remaining = len - i - 1;
            for (size_t j = i + 1; j < len && remaining > 0; j++)
            {
                if (is_alphanumeric(input[j]))
                {
                    cipher[cipher_index++] = ' ';
                    group_count = 0;
                    break;
                }
                remaining--;
            }
        }
    }

    return cipher;
}

char *atbash_decode(const char *input)
{
    assert(input != NULL);

    size_t len = strlen(input);
    char *text = (char *)calloc(len + 1, 1);
    assert(text != NULL);

    size_t text_index = 0;
    for (size_t i = 0; i < len; i++)
    {
        char c = input[i];
        char lower_c = to_lower(c);
        
        if (lower_c >= 'a' && lower_c <= 'z')
        {
            text[text_index++] = atbash_transform(lower_c);
        }
        else if (c >= '0' && c <= '9')
        {
            text[text_index++] = c;
        }
    }

    return text;
}