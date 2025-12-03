#include "rail_fence_cipher.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *encode(char *text, size_t rails) {
  if (!text || !rails) return NULL;

  size_t length = strlen(text);
  if (!length) return NULL;

  char *cipher = (char *)calloc(length + 1, sizeof(char));
  if (!cipher) return NULL;

  size_t rail_index[length];
  int row_step = 1;
  size_t row = 0;

  for (size_t col = 0; col < length; col++) {
    rail_index[col] = row;
    row += row_step;
    if (row == rails - 1 || row == 0) {
      row_step *= -1;
    }
  }

  size_t cipher_index = 0;
  for (size_t r = 0; r < rails; r++) {
    for (size_t i = 0; i < length; i++) {
      if (rail_index[i] == r) {
        cipher[cipher_index++] = text[i];
      }
    }
  }

  return cipher;
}

char *decode(char *ciphertext, size_t rails) {
  if (!ciphertext || !rails) return NULL;

  size_t length = strlen(ciphertext);
  if (!length) return NULL;

  char *text = (char *)calloc(length + 1, sizeof(char));
  if (!text) return NULL;

  size_t rail_index[length];
  int row_step = 1;
  size_t row = 0;

  for (size_t col = 0; col < length; col++) {
    rail_index[col] = row;
    row += row_step;
    if (row == rails - 1 || row == 0) {
      row_step *= -1;
    }
  }

  size_t cipher_index = 0;
  for (size_t r = 0; r < rails; r++) {
    for (size_t i = 0; i < length; i++) {
      if (rail_index[i] == r) {
        text[i] = ciphertext[cipher_index++];
      }
    }
  }

  return text;
}