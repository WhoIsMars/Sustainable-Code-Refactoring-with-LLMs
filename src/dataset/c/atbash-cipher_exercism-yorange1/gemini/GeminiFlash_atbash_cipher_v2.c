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

  // Add spaces after every 5 characters, but only if there are characters to encode
  if (encoded_len > 0) {
    encoded_len += (encoded_len - 1) / 5; // Integer division gives the correct number of spaces
  }

  char *cipher = (char *)malloc(encoded_len + 1); // Allocate exactly the required memory
  if (cipher == NULL) {
    return NULL; // Handle allocation failure
  }
  cipher[encoded_len] = '\0'; // Null-terminate the string

  size_t cipher_index = 0;
  size_t char_count = 0;

  for (size_t i = 0; i < len; i++) {
    if (isalpha(input[i])) {
      cipher[cipher_index++] = atbash_alphabet[tolower(input[i]) - 'a'];
      char_count++;
    } else if (isdigit(input[i])) {
      cipher[cipher_index++] = input[i];
      char_count++;
    }

    if (char_count > 0 && char_count % 5 == 0 && cipher_index < encoded_len) {
      cipher[cipher_index++] = ' ';
    }
  }

  return cipher;
}

char *atbash_decode(const char *input) {
  assert(input != NULL);

  size_t len = strlen(input);
  size_t decoded_len = 0;

  // Calculate the maximum possible length of the decoded string.
  for (size_t i = 0; i < len; i++) {
    if (isalnum(input[i])) {
      decoded_len++;
    }
  }

  char *text = (char *)malloc(decoded_len + 1); // Allocate exactly the required memory
  if (text == NULL) {
    return NULL; // Handle allocation failure
  }
  text[decoded_len] = '\0'; // Null-terminate the string

  size_t text_index = 0;
  for (size_t i = 0; i < len; i++) {
    if (isalpha(input[i])) {
      // Optimized decoding: Directly calculate the index instead of using atbash_alphabet
      text[text_index++] = 'a' + ('z' - tolower(input[i]));
    } else if (isdigit(input[i])) {
      text[text_index++] = input[i];
    }
  }

  return text;
}