#include "acronym.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase) {
  if (phrase == NULL || *phrase == '\0') {
    return NULL;
  }

  size_t phrase_len = strlen(phrase);
  char *result = (char *)malloc(phrase_len + 1); // Max possible size
  if (result == NULL) {
    return NULL;
  }

  size_t result_len = 0;
  int new_word = 1; // Flag to indicate the start of a new word

  for (size_t i = 0; i < phrase_len; ++i) {
    if (isalpha(phrase[i])) {
      if (new_word) {
        result[result_len++] = toupper(phrase[i]);
        new_word = 0;
      }
    } else if (phrase[i] == ' ' || phrase[i] == '-' || phrase[i] == '_') {
      new_word = 1;
    }
  }

  if (result_len == 0) {
    free(result);
    return NULL;
  }

  result = (char *)realloc(result, result_len + 1); // Resize to actual length
  if (result == NULL) {
      // Handle realloc failure, possibly by returning a truncated string or NULL
      return NULL;
  }
  result[result_len] = '\0';

  return result;
}