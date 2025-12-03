#include "anagram.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static int comparator(const void *char_a, const void *char_b)
{
    return *((char *)char_a) - *((char *)char_b);
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
    char subject_copy[strlen(subject) + 1];
    strcpy(subject_copy, subject);
    convert_string_to_lower_case(subject_copy);
    sort_sentence_in_place(subject_copy);

    for (unsigned int i = 0; i < candidates->count; i++)
    {
        char *candidate_word = candidates->candidate[i].word;
        if (strlen(candidate_word) != strlen(subject))
        {
            candidates->candidate[i].is_anagram = NOT_ANAGRAM;
            continue;
        }

        char candidate_copy[strlen(candidate_word) + 1];
        strcpy(candidate_copy, candidate_word);
        convert_string_to_lower_case(candidate_copy);
        sort_sentence_in_place(candidate_copy);

        if (strcmp(subject_copy, candidate_copy) == 0 &&
            strcasecmp(subject, candidate_word) != 0)
        {
            candidates->candidate[i].is_anagram = IS_ANAGRAM;
        }
        else
        {
            candidates->candidate[i].is_anagram = NOT_ANAGRAM;
        }
    }
}