#include "atbash_cipher.h"

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// zyxwvutsrqponmlkjihgfedcba
static const char atbash_alphabet[26] = {'z', 'y', 'x', 'w', 'v', 'u', 't', 's', 'r', 'q',
                                         'p', 'o', 'n', 'm', 'l', 'k', 'j', 'i', 'h', 'g',
                                         'f', 'e', 'd', 'c', 'b', 'a'};

char *atbash_encode(const char *input) {
  assert(input != NULL);

  size_t len = strlen(input);
  size_t encoded_len = 0;

  // Calculate the maximum possible length of the encoded string.
  for (size_t i = 0; i < len; i++) {
    if (isalnum(input[i])) {
      encoded_len++;
    }
  }

  // Add spaces every 5 characters, but only if there are characters to encode
  encoded_len += (encoded_len > 0) ? (encoded_len - 1) / 5 : 0;

  char *cipher = (char *)malloc(encoded_len + 1); // Allocate only needed memory
  if (cipher == NULL) {
    return NULL; // Handle allocation failure
  }

  size_t cipher_index = 0;
  for (size_t i = 0; i < len; i++) {
    char c = input[i];
    if (isalpha(c)) {
      cipher[cipher_index++] = atbash_alphabet[tolower(c) - 'a'];
    } else if (isdigit(c)) {
      cipher[cipher_index++] = c;
    }

    if (cipher_index > 0 && (cipher_index % 5 == 0) && (cipher_index < encoded_len)) {
      cipher[cipher_index++] = ' ';
    }
  }

  cipher[cipher_index] = '\0'; // Null-terminate the string
  return cipher;
}

char *atbash_decode(const char *input) {
  assert(input != NULL);

  size_t len = strlen(input);
  size_t decoded_len = 0;

  // Calculate the length of the decoded string (without spaces).
  for (size_t i = 0; i < len; i++) {
    if (isalnum(input[i])) {
      decoded_len++;
    }
  }

  char *text = (char *)malloc(decoded_len + 1); // Allocate only needed memory
  if (text == NULL) {
    return NULL; // Handle allocation failure
  }

  size_t text_index = 0;
  for (size_t i = 0; i < len; i++) {
    char c = input[i];
    if (isalnum(c)) {
        if (isalpha(c)) {
            for (int j = 0; j < 26; j++) {
                if (atbash_alphabet[j] == tolower(c)) {
                    text[text_index++] = 'a' + j;
                    break;
                }
            }
        } else {
            text[text_index++] = c;
        }
    }
  }

  text[text_index] = '\0'; // Null-terminate the string
  return text;
}