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
    size_t len = strlen(sentence);
    char *sentence_copy = (char *)malloc((len + 1) * sizeof(char));
    
    strcpy(sentence_copy, sentence);
    qsort(sentence_copy, len, sizeof(char), comparator);

    return sentence_copy;
}

static void convert_string_to_lower_case(char *sentence)
{
    for (char *p = sentence; *p; p++)
    {
        *p = tolower((unsigned char)*p);
    }
}

void find_anagrams(char *subject, struct candidates *candidates)
{
    size_t subject_length = strlen(subject);
    char *ordered_candidate;
    char *ordered_subject;

    convert_string_to_lower_case(subject);
    ordered_subject = sort_sentence(subject);

    for (size_t i = 0; i < candidates->count; i++)
    {
        if (strlen(candidates->candidate[i].word) != subject_length)
        {
            candidates->candidate[i].is_anagram = NOT_ANAGRAM;
            continue;
        }

        convert_string_to_lower_case(candidates->candidate[i].word);
        
        if (strcmp(subject, candidates->candidate[i].word) == 0)
        {
            candidates->candidate[i].is_anagram = NOT_ANAGRAM;
            continue;
        }

        ordered_candidate = sort_sentence(candidates->candidate[i].word);

        if (strcmp(ordered_subject, ordered_candidate) == 0)
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