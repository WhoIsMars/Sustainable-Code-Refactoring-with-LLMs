#include "crypto_square.h"

#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

char *ciphertext(const char *input) {
  if (input == NULL) {
    return NULL;
  }

  size_t input_len = strlen(input);
  size_t normalized_len = 0;
  char *normalized = (char *)malloc(input_len + 1); // Allocate on heap

  if (normalized == NULL) {
    return NULL; // Handle allocation failure
  }

  for (size_t i = 0; i < input_len; i++) {
    if (isalnum((unsigned char)input[i])) {
      normalized[normalized_len++] = tolower((unsigned char)input[i]);
    }
  }
  normalized[normalized_len] = '\0';

  if (normalized_len == 0) {
    char *empty_string = (char *)calloc(1, 1);
    free(normalized);
    return empty_string;
  }

  size_t cols = (size_t)ceil(sqrt((double)normalized_len));
  size_t rows = (normalized_len > (cols * (cols - 1))) ? cols : cols - 1;
  if (cols == 0) rows = 0;
  if (rows == 0) cols = 0;

  char *cipher = (char *)calloc(1, (rows * cols + cols)); // Allocate for spaces and null terminator
  if (cipher == NULL) {
    free(normalized);
    return NULL; // Handle allocation failure
  }

  size_t cipher_index = 0;
  for (size_t col = 0; col < cols; col++) {
    for (size_t row = 0; row < rows; row++) {
      size_t char_index = row * cols + col;
      if (char_index < normalized_len) {
        cipher[cipher_index++] = normalized[char_index];
      } else {
        cipher[cipher_index++] = ' ';
      }
    }
    if (col < cols - 1) {
      cipher[cipher_index++] = ' ';
    }
  }

  cipher[cipher_index] = '\0';
  free(normalized); // Free allocated memory
  return cipher;
}