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
        char *result = malloc(1);
        result[0] = '\0';
        return result;
    }

    // Count valid characters first to avoid oversized allocation
    size_t valid_count = 0;
    for (size_t i = 0; i < input_len; i++) {
        if (isalnum(input[i])) {
            valid_count++;
        }
    }

    if (valid_count == 0) {
        char *result = malloc(1);
        result[0] = '\0';
        return result;
    }

    // Allocate exact size needed for normalized string
    char *normalized = malloc(valid_count + 1);
    size_t index = 0;

    for (size_t i = 0; i < input_len; i++) {
        if (isalpha(input[i])) {
            normalized[index++] = tolower(input[i]);
        } else if (isdigit(input[i])) {
            normalized[index++] = input[i];
        }
    }

    size_t cols = (size_t)ceil(sqrt((double)valid_count));
    size_t rows = (valid_count + cols - 1) / cols; // More efficient ceiling division

    // Calculate exact output size
    size_t output_size = cols * rows + cols; // data + spaces + null terminator
    char *cipher = malloc(output_size);
    
    size_t cipher_index = 0;

    for (size_t col = 0; col < cols; col++) {
        for (size_t row = 0; row < rows; row++) {
            size_t pos = row * cols + col;
            if (pos < valid_count) {
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