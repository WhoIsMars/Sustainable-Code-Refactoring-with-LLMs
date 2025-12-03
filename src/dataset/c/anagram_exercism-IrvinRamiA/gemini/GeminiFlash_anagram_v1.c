#include "anagram.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

static int comparator(const void *char_a, const void *char_b) {
  return *(const char *)char_a - *(const char *)char_b;
}

static void sort_string(char *str) {
  qsort(str, strlen(str), sizeof(char), comparator);
}

static void string_to_lower_case(char *str) {
  for (char *p = str; *p; ++p) {
    *p = tolower((unsigned char)*p);
  }
}

void find_anagrams(char *subject, struct candidates *candidates) {
  size_t subject_length = strlen(subject);

  // Allocate memory for a lowercase and sorted copy of the subject.
  char *lower_subject = strdup(subject);
  if (!lower_subject) return; // Handle allocation failure

  string_to_lower_case(lower_subject);
  sort_string(lower_subject);

  for (size_t i = 0; i < candidates->count; i++) {
    char *candidate_word = candidates->candidate[i].word;
    size_t candidate_length = strlen(candidate_word);

    // Early exit if lengths differ
    if (subject_length != candidate_length) {
      candidates->candidate[i].is_anagram = NOT_ANAGRAM;
      continue;
    }

    // Allocate memory for a lowercase and sorted copy of the candidate.
    char *lower_candidate = strdup(candidate_word);
    if (!lower_candidate) continue; // Handle allocation failure

    string_to_lower_case(lower_candidate);
    sort_string(lower_candidate);

    // Compare sorted strings
    bool is_anagram = (strcmp(lower_subject, lower_candidate) == 0) &&
                       (strcmp(subject, candidate_word) != 0);

    candidates->candidate[i].is_anagram = is_anagram ? IS_ANAGRAM : NOT_ANAGRAM;

    free(lower_candidate);
  }

  free(lower_subject);
}