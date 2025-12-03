#include "anagram.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

static int comparator(const void *char_a, const void *char_b) {
  return tolower(*(unsigned char *)char_a) - tolower(*(unsigned char *)char_b);
}

static bool is_anagram(const char *subject, const char *candidate) {
  size_t subject_length = strlen(subject);
  size_t candidate_length = strlen(candidate);

  if (subject_length != candidate_length) {
    return false;
  }

  if (strcasecmp(subject, candidate) == 0) {
    return false;
  }

  char *subject_copy = strdup(subject);
  if (!subject_copy) return false;

  char *candidate_copy = strdup(candidate);
  if (!candidate_copy) {
    free(subject_copy);
    return false;
  }

  qsort(subject_copy, subject_length, sizeof(char), comparator);
  qsort(candidate_copy, candidate_length, sizeof(char), comparator);

  bool result = (strcmp(subject_copy, candidate_copy) == 0);

  free(subject_copy);
  free(candidate_copy);

  return result;
}

void find_anagrams(char *subject, struct candidates *candidates) {
  for (size_t i = 0; i < candidates->count; i++) {
    if (is_anagram(subject, candidates->candidate[i].word)) {
      candidates->candidate[i].is_anagram = IS_ANAGRAM;
    } else {
      candidates->candidate[i].is_anagram = NOT_ANAGRAM;
    }
  }
}