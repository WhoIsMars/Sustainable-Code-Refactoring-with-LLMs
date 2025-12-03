#include "acronym.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase) {
  if (!phrase || !*phrase) {
    return NULL;
  }

  size_t phrase_len = strlen(phrase);
  char *abrev = malloc(phrase_len + 1); // Allocate enough space
  if (!abrev) return NULL; // Handle allocation failure

  char *tmp = abrev;
  *tmp++ = toupper(*phrase); // Convert first char to uppercase
  
  for (size_t i = 1; i < phrase_len; ++i) {
    if (phrase[i] == ' ' || phrase[i] == '-') {
      // Skip multiple delimiters
      while (i < phrase_len && (phrase[i] == ' ' || phrase[i] == '-')) {
        i++;
      }

      if (i < phrase_len && isalpha(phrase[i])) {
        *tmp++ = toupper(phrase[i]);
      }
    }
  }

  *tmp = '\0';
  size_t abrev_len = tmp - abrev;
  char *result = realloc(abrev, abrev_len + 1); // Reallocate to actual size
    if (!result) {
        free(abrev);
        return NULL;
    }

  return result;
}