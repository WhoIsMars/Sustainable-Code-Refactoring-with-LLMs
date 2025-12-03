#include "anagram.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

static int comparator(const void *char_a, const void *char_b) {
  return tolower(*(unsigned char *)char_a) - tolower(*(unsigned char *)char_b);
}

static void sort_string(char *str) {
  qsort(str, strlen(str), sizeof(char), comparator);
}

static void to_lower(char *str) {
  for (char *p = str; *p; p++) {
    *p = tolower((unsigned char)*p);
  }
}

void find_anagrams(char *subject, struct candidates *candidates) {
  size_t subject_length = strlen(subject);

  char *subject_copy = strdup(subject);
  if (!subject_copy) return;

  to_lower(subject_copy);
  sort_string(subject_copy);

  for (size_t i = 0; i < candidates->count; i++) {
    char *candidate_word = candidates->candidate[i].word;
    size_t candidate_length = strlen(candidate_word);

    if (subject_length != candidate_length) {
      candidates->candidate[i].is_anagram = NOT_ANAGRAM;
      continue;
    }

    char *candidate_copy = strdup(candidate_word);
    if (!candidate_copy) continue;

    to_lower(candidate_copy);
    sort_string(candidate_copy);

    if (strcmp(subject_copy, candidate_copy) == 0 && strcmp(subject, candidate_word) != 0) {
      candidates->candidate[i].is_anagram = IS_ANAGRAM;
    } else {
      candidates->candidate[i].is_anagram = NOT_ANAGRAM;
    }
    free(candidate_copy);
  }
  free(subject_copy);
}