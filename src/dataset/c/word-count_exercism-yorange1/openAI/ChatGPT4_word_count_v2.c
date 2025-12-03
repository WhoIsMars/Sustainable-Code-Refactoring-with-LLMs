#include "word_count.h"

#include <ctype.h>
#include <stddef.h>
#include <string.h>

const char delim = ' ';

static int update_count(word_count_word_t *words, size_t *words_count, const char *word)
{
    size_t word_length = strlen(word);
    if (word_length > MAX_WORD_LENGTH)
    {
        return EXCESSIVE_LENGTH_WORD;
    }

    for (size_t i = 0; i < *words_count; i++)
    {
        if (strcmp(words[i].text, word) == 0)
        {
            words[i].count++;
            return 0;
        }
    }

    if (*words_count >= MAX_WORDS)
    {
        return EXCESSIVE_NUMBER_OF_WORDS;
    }

    strncpy(words[*words_count].text, word, MAX_WORD_LENGTH);
    words[*words_count].text[MAX_WORD_LENGTH] = '\0'; // Ensure null termination
    words[*words_count].count = 1;
    (*words_count)++;

    return 0;
}

int count_words(const char *sentence, word_count_word_t *words)
{
    if (!sentence || !words)
        return INVAILD_PARAMETER;

    size_t length = strlen(sentence);
    if (length == 0)
    {
        return EXCESSIVE_LENGTH_WORD;
    }

    memset(words, 0, MAX_WORDS * sizeof(word_count_word_t));

    char sentence_copy[MAX_WORDS * (MAX_WORD_LENGTH + 1)] = {0};
    size_t copy_index = 0;

    for (size_t i = 0; i < length; i++)
    {
        if (isalpha(sentence[i]))
        {
            sentence_copy[copy_index++] = tolower(sentence[i]);
        }
        else if (isdigit(sentence[i]))
        {
            sentence_copy[copy_index++] = sentence[i];
        }
        else if (sentence[i] == '\'')
        {
            if (i > 0 && i < length - 1 && isalnum(sentence[i - 1]) && isalnum(sentence[i + 1]))
            {
                sentence_copy[copy_index++] = sentence[i];
            }
            else
            {
                sentence_copy[copy_index++] = delim;
            }
        }
        else
        {
            sentence_copy[copy_index++] = delim;
        }
    }
    sentence_copy[copy_index] = '\0';

    size_t words_count = 0;
    char *save_ptr;
    char *word = strtok_r(sentence_copy, &delim, &save_ptr);
    while (word)
    {
        if (update_count(words, &words_count, word) < 0)
        {
            return EXCESSIVE_NUMBER_OF_WORDS;
        }
        word = strtok_r(NULL, &delim, &save_ptr);
    }

    return words_count;
}