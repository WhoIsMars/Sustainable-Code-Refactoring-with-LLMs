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

    const char *src = input;
    size_t normalized_len = 0;
    
    while (*src) {
        if (isalnum(*src)) {
            normalized_len++;
        }
        src++;
    }
    
    if (normalized_len == 0) {
        char *result = malloc(1);
        *result = '\0';
        return result;
    }

    size_t cols = (size_t)ceil(sqrt((double)normalized_len));
    size_t rows = (normalized_len + cols - 1) / cols;
    
    size_t result_size = cols * (rows + 1);
    char *cipher = malloc(result_size);
    
    src = input;
    size_t pos = 0;
    char *normalized = malloc(normalized_len);
    
    while (*src) {
        if (isalpha(*src)) {
            normalized[pos++] = tolower(*src);
        } else if (isdigit(*src)) {
            normalized[pos++] = *src;
        }
        src++;
    }
    
    size_t cipher_idx = 0;
    for (size_t col = 0; col < cols; col++) {
        for (size_t row = 0; row < rows; row++) {
            size_t src_idx = row * cols + col;
            cipher[cipher_idx++] = (src_idx < normalized_len) ? normalized[src_idx] : ' ';
        }
        cipher[cipher_idx++] = (col == cols - 1) ? '\0' : ' ';
    }
    
    free(normalized);
    return cipher;
}