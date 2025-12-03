#include "anagram.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static int comparator(const void *char_a, const void *char_b)
{
    return *((unsigned char *)char_a) - *((unsigned char *)char_b);
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
    unsigned char subject_length = strlen(subject);
    char *ordered_subject = strdup(subject);

    convert_string_to_lower_case(ordered_subject);
    sort_sentence_in_place(ordered_subject);

    for (unsigned char i = 0u; i < candidates->count; i++)
    {
        struct candidate *current_candidate = &candidates->candidate[i];
        if (strlen(current_candidate->word) != subject_length)
        {
            current_candidate->is_anagram = NOT_ANAGRAM;
            continue;
        }

        char *candidate_copy = strdup(current_candidate->word);
        convert_string_to_lower_case(candidate_copy);
        sort_sentence_in_place(candidate_copy);

        if (strcmp(ordered_subject, candidate_copy) == 0 &&
            strcasecmp(subject, current_candidate->word) != 0)
        {
            current_candidate->is_anagram = IS_ANAGRAM;
        }
        else
        {
            current_candidate->is_anagram = NOT_ANAGRAM;
        }

        free(candidate_copy);
    }

    free(ordered_subject);
}