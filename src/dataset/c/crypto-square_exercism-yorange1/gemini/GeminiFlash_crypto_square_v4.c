#include "crypto_square.h"

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *ciphertext(const char *input)
{
    assert(input != NULL);

    size_t input_len = strlen(input);
    size_t normalized_len = 0;

    // Pre-calculate the length of the normalized string
    for (size_t i = 0; i < input_len; i++)
    {
        if (isalnum(input[i]))
        {
            normalized_len++;
        }
    }

    if (normalized_len == 0) {
        char *empty_string = calloc(1, 1);
        if (empty_string == NULL) {
            return NULL;
        }
        empty_string[0] = '\0';
        return empty_string;
    }

    char *normalized = (char *)malloc(normalized_len + 1);
    if (normalized == NULL) {
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < input_len; i++)
    {
        if (isalnum(input[i]))
        {
            normalized[index++] = (char)tolower(input[i]);
        }
    }
    normalized[normalized_len] = '\0';

    size_t cols = ceil(sqrt((float)normalized_len));
    size_t rows = (size_t)((float)normalized_len / cols);
    if (rows * cols < normalized_len) {
        rows++;
    }

    char *cipher = (char *)calloc(1, (rows * cols + cols));
    if (cipher == NULL) {
        free(normalized);
        return NULL;
    }

    index = 0;
    for (size_t col = 0; col < cols; col++)
    {
        for (size_t row = 0; row < rows; row++)
        {
            size_t char_index = row * cols + col;
            if (char_index < normalized_len)
            {
                cipher[index++] = normalized[char_index];
            }
            else
            {
                cipher[index++] = ' ';
            }
        }
        if (col < cols - 1) {
            cipher[index++] = ' ';
        }
    }
    cipher[index] = '\0';

    free(normalized);
    return cipher;
}