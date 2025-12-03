#include "anagram.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static int comparator(const void *char_a, const void *char_b)
{
    return *((char *)char_a) - *((char *)char_b);
}

static char *sort_sentence(char *sentence)
{
    char *sentence_copy = (char *)malloc((strlen(sentence) + 1) * sizeof(char));

    strcpy(sentence_copy, sentence);
    qsort(sentence_copy, strlen(sentence_copy), sizeof(char), comparator);

    return sentence_copy;
}

static void convert_string_to_lower_case(char *sentence)
{
    for (unsigned char i = 0; i < strlen(sentence); i++)
    {
        *(sentence + i) = tolower(*(sentence + i));
    }
}

void find_anagrams(char *subject, struct candidates *candidates)
{
    unsigned char subject_length = strlen(subject);
    char *ordered_candidate;
    char *ordered_subject;

    convert_string_to_lower_case(subject);
    ordered_subject = sort_sentence(subject);

    for (unsigned char i = 0u; i < candidates->count; i++)
    {
        convert_string_to_lower_case(candidates->candidate[i].word);
        ordered_candidate = sort_sentence(candidates->candidate[i].word);

        if (strncmp(ordered_subject, ordered_candidate, subject_length + 1) == 0 &&
            strncmp(subject, candidates->candidate[i].word, subject_length + 1) != 0)
        {
            candidates->candidate[i].is_anagram = IS_ANAGRAM;
        }
        else
        {
            candidates->candidate[i].is_anagram = NOT_ANAGRAM;
        }
    }
}
