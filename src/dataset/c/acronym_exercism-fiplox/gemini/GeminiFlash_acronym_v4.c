#include "acronym.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase) {
  if (!phrase || !*phrase) {
    return NULL;
  }

  size_t phrase_len = strlen(phrase);
  char *abrev = malloc(phrase_len + 1);
  if (!abrev) {
    return NULL; // Handle allocation failure
  }

  char *tmp = abrev;
  *tmp++ = toupper(*phrase);

  for (size_t i = 1; i < phrase_len; ++i) {
    if (phrase[i] == ' ' || phrase[i] == '-') {
      // Skip multiple non-alphabetic characters
      while (i < phrase_len && !isalpha(phrase[i])) {
        i++;
      }

      if (i < phrase_len) {
        *tmp++ = toupper(phrase[i]);
      } else {
        break; // Avoid writing past the end of the phrase
      }
    }
  }

  *tmp = '\0';

  // Resize the allocated memory to the actual length of the acronym
  size_t abrev_len = strlen(abrev);
  char *resized_abrev = realloc(abrev, abrev_len + 1);
  if (!resized_abrev) {
    free(abrev); // Prevent memory leak if realloc fails
    return NULL;
  }

  return resized_abrev;
}