#include "anagram.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static int comparator(const void *char_a, const void *char_b)
{
    return *(const char *)char_a - *(const char *)char_b;
}

static void sort_sentence_in_place(char *sentence)
{
    qsort(sentence, strlen(sentence), sizeof(char), comparator);
}

static void convert_string_to_lower_case(char *sentence)
{
    for (char *ptr = sentence; *ptr; ++ptr)
    {
        *ptr = tolower(*ptr);
    }
}

void find_anagrams(char *subject, struct candidates *candidates)
{
    size_t subject_length = strlen(subject);
    char *ordered_subject = strdup(subject);

    convert_string_to_lower_case(ordered_subject);
    sort_sentence_in_place(ordered_subject);

    for (size_t i = 0; i < candidates->count; i++)
    {
        char *candidate_word = candidates->candidate[i].word;
        size_t candidate_length = strlen(candidate_word);

        if (candidate_length != subject_length)
        {
            candidates->candidate[i].is_anagram = NOT_ANAGRAM;
            continue;
        }

        char *ordered_candidate = strdup(candidate_word);
        convert_string_to_lower_case(ordered_candidate);
        sort_sentence_in_place(ordered_candidate);

        if (strcmp(ordered_subject, ordered_candidate) == 0 &&
            strcasecmp(subject, candidate_word) != 0)
        {
            candidates->candidate[i].is_anagram = IS_ANAGRAM;
        }
        else
        {
            candidates->candidate[i].is_anagram = NOT_ANAGRAM;
        }

        free(ordered_candidate);
    }

    free(ordered_subject);
}