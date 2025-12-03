#include "acronym.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase) {
  if (phrase == NULL || phrase[0] == '\0') {
    return NULL;
  }

  size_t phrase_len = strlen(phrase);
  char *result = (char *)malloc(phrase_len + 1); // Allocate enough memory
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

  // Resize the allocated memory to the actual length of the acronym
  result = (char *)realloc(result, index + 1);
  if (result == NULL) {
      // Handle realloc failure (e.g., log an error, free previous allocation if needed)
      return NULL;
  }

  return result;
}