#include "anagram.h"

#define _GNU_SOURCE
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define ALPHA_NUM (26)

static void count_letter(const char *letters, size_t length, uint8_t alpha_table[ALPHA_NUM])
{
    memset(alpha_table, 0, ALPHA_NUM);

    for (size_t i = 0; i < length; i++)
    {
        size_t index = (unsigned char)letters[i] | 0x20;
        if (index >= 'a' && index <= 'z')
        {
            alpha_table[index - 'a']++;
        }
    }
}

static bool is_anagrams(size_t subject_length, const uint8_t alpha_table[ALPHA_NUM], const char *word, size_t word_length)
{
    if (word_length != subject_length)
    {
        return false;
    }

    uint8_t tmp_table[ALPHA_NUM];
    memcpy(tmp_table, alpha_table, ALPHA_NUM);

    for (size_t i = 0; i < word_length; i++)
    {
        size_t index = (unsigned char)word[i] | 0x20;
        if (index >= 'a' && index <= 'z')
        {
            index -= 'a';
            if (tmp_table[index] == 0)
            {
                return false;
            }
            tmp_table[index]--;
        }
    }

    return true;
}

void find_anagrams(const char *subject, struct candidates *candidates)
{
    assert(subject != NULL && candidates != NULL);

    size_t subject_length = strlen(subject);
    uint8_t subject_alpha_table[ALPHA_NUM];
    count_letter(subject, subject_length, subject_alpha_table);

    for (size_t i = 0; i < candidates->count; i++)
    {
        struct candidate *candidate = &candidates->candidate[i];
        size_t word_length = strlen(candidate->word);

        if (word_length == subject_length &&
            strcasecmp(subject, candidate->word) != 0 &&
            is_anagrams(subject_length, subject_alpha_table, candidate->word, word_length))
        {
            candidate->is_anagram = IS_ANAGRAM;
        }
        else
        {
            candidate->is_anagram = NOT_ANAGRAM;
        }
    }
}