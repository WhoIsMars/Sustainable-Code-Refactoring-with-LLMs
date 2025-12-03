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

    size_t normalized_len = 0;
    for (size_t i = 0; i < input_len; i++) {
        if (isalnum(input[i])) {
            normalized_len++;
        }
    }

    if (normalized_len == 0) {
        char *empty = malloc(1);
        empty[0] = '\0';
        return empty;
    }

    size_t cols = (size_t)ceil(sqrt((double)normalized_len));
    size_t rows = (normalized_len + cols - 1) / cols;

    size_t cipher_len = cols * 2;
    char *cipher = malloc(cipher_len);
    size_t cipher_index = 0;

    for (size_t col = 0; col < cols; col++) {
        for (size_t row = 0; row < rows; row++) {
            size_t pos = row * cols + col;
            if (pos < normalized_len) {
                size_t input_idx = 0;
                size_t norm_count = 0;
                
                while (input_idx < input_len && norm_count <= pos) {
                    if (isalnum(input[input_idx])) {
                        if (norm_count == pos) {
                            cipher[cipher_index++] = isalpha(input[input_idx]) ? 
                                tolower(input[input_idx]) : input[input_idx];
                            break;
                        }
                        norm_count++;
                    }
                    input_idx++;
                }
            } else {
                cipher[cipher_index++] = ' ';
            }
        }
        
        if (col < cols - 1) {
            cipher[cipher_index++] = ' ';
        }
    }

    cipher[cipher_index] = '\0';
    return cipher;
}