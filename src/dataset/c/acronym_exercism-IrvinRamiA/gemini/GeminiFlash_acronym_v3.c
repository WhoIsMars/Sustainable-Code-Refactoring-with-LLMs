#include "acronym.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *abbreviate(const char *phrase) {
  if (phrase == NULL || phrase[0] == '\0') {
    return NULL;
  }

  size_t phrase_len = strlen(phrase);
  char *result = (char *)malloc(phrase_len + 1); // Allocate enough space
  if (result == NULL) {
    return NULL; // Handle allocation failure
  }

  size_t index = 0;
  result[index++] = toupper(phrase[0]); // First character

  for (size_t i = 1; i < phrase_len; ++i) {
    if ((phrase[i - 1] == ' ' || phrase[i - 1] == '-' ||
         phrase[i - 1] == '_') &&
        isalpha(phrase[i])) {
      result[index++] = toupper(phrase[i]);
    }
  }

  result[index] = '\0'; // Null-terminate the string

  if (index == 0) {
      free(result);
      return NULL;
  }

  char *final_result = (char *)realloc(result, index + 1);
  if (final_result == NULL) {
      free(result);
      return NULL;
  }

  return final_result;
}