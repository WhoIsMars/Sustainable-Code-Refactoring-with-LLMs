#include "anagram.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

static int comparator(const void *char_a, const void *char_b) {
  return tolower(*(unsigned char *)char_a) - tolower(*(unsigned char *)char_b);
}

static bool is_anagram(const char *subject, const char *candidate) {
  size_t subject_len = strlen(subject);
  size_t candidate_len = strlen(candidate);

  if (subject_len != candidate_len) {
    return false;
  }

  if (strcasecmp(subject, candidate) == 0) {
    return false;
  }

  char *subject_sorted = strdup(subject);
  if (!subject_sorted) return false;

  char *candidate_sorted = strdup(candidate);
  if (!candidate_sorted) {
    free(subject_sorted);
    return false;
  }

  for (size_t i = 0; i < subject_len; ++i) {
    subject_sorted[i] = tolower(subject_sorted[i]);
    candidate_sorted[i] = tolower(candidate_sorted[i]);
  }

  qsort(subject_sorted, subject_len, sizeof(char), comparator);
  qsort(candidate_sorted, candidate_len, sizeof(char), comparator);

  bool result = (strcmp(subject_sorted, candidate_sorted) == 0);

  free(subject_sorted);
  free(candidate_sorted);

  return result;
}

void find_anagrams(char *subject, struct candidates *candidates) {
  for (size_t i = 0; i < candidates->count; i++) {
    candidates->candidate[i].is_anagram =
        is_anagram(subject, candidates->candidate[i].word) ? IS_ANAGRAM
                                                            : NOT_ANAGRAM;
  }
}