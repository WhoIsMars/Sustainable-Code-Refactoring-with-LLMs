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
    if (input_len == 0) {
        char *empty = malloc(1);
        empty[0] = '\0';
        return empty;
    }

    // Count normalized characters first to avoid oversized allocation
    size_t norm_len = 0;
    for (size_t i = 0; i < input_len; i++) {
        if (isalnum(input[i])) {
            norm_len++;
        }
    }

    if (norm_len == 0) {
        char *empty = malloc(1);
        empty[0] = '\0';
        return empty;
    }

    char *normalized = malloc(norm_len);
    size_t index = 0;

    for (size_t i = 0; i < input_len; i++) {
        if (isalpha(input[i])) {
            normalized[index++] = tolower(input[i]);
        } else if (isdigit(input[i])) {
            normalized[index++] = input[i];
        }
    }

    size_t cols = (size_t)ceil(sqrt((double)norm_len));
    size_t rows = (norm_len + cols - 1) / cols;

    // Calculate exact output size
    size_t output_size = cols * 2; // cols groups + (cols-1) spaces + null terminator
    char *cipher = malloc(output_size);
    size_t cipher_index = 0;

    for (size_t col = 0; col < cols; col++) {
        for (size_t row = 0; row < rows; row++) {
            size_t pos = row * cols + col;
            if (pos < norm_len) {
                cipher[cipher_index++] = normalized[pos];
            } else {
                cipher[cipher_index++] = ' ';
            }
        }

        if (col < cols - 1) {
            cipher[cipher_index++] = ' ';
        }
    }

    cipher[cipher_index] = '\0';
    free(normalized);
    return cipher;
}