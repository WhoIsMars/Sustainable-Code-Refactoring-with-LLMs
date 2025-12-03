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
        char ch = tolower(letters[i]);
        if (ch >= 'a' && ch <= 'z')
        {
            alpha_table[ch - 'a']++;
        }
    }
}

static bool is_anagrams(size_t subject_length, const uint8_t alpha_table[ALPHA_NUM], const char *word)
{
    size_t word_length = 0;
    uint8_t tmp_table[ALPHA_NUM] = {0};

    for (const char *p = word; *p; p++)
    {
        char ch = tolower(*p);
        if (ch < 'a' || ch > 'z')
            return false;

        word_length++;
        size_t index = ch - 'a';
        if (++tmp_table[index] > alpha_table[index])
        {
            return false;
        }
    }

    return word_length == subject_length;
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

        if (strcasecmp(subject, candidate->word) != 0 &&
            is_anagrams(subject_length, subject_alpha_table, candidate->word))
        {
            candidate->is_anagram = IS_ANAGRAM;
        }
        else
        {
            candidate->is_anagram = NOT_ANAGRAM;
        }
    }
}