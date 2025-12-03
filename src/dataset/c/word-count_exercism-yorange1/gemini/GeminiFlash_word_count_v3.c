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
        if (strncmp(words[i].text, word, MAX_WORD_LENGTH) == 0)
        {
            words[i].count++;
            return 0;
        }
    }

    if (*words_count >= MAX_WORDS)
    {
        return EXCESSIVE_NUMBER_OF_WORDS;
    }

    strncpy(words[*words_count].text, word, word_length);
    words[*words_count].text[word_length] = '\0';
    words[*words_count].count = 1;
    (*words_count)++;

    return 0;
}

int count_words(const char *sentence, word_count_word_t *words)
{
    if (NULL == sentence || NULL == words)
        return INVAILD_PARAMETER;

    size_t length = strlen(sentence);
    if (0 == length)
    {
        return 0;
    }

    memset(words, 0, MAX_WORDS * sizeof(word_count_word_t));

    char sentence_copy[length + 1];
    sentence_copy[length] = '\0';

    for (size_t i = 0; i < length; i++)
    {
        char c = sentence[i];
        if (isalpha(c))
        {
            sentence_copy[i] = tolower(c);
        }
        else if (isdigit(c))
        {
            sentence_copy[i] = c;
        }
        else if (c == '\'')
        {
            if (i == 0 || i == length - 1 || (i > 0 && sentence[i - 1] == delim) || (i < length - 1 && sentence[i + 1] == delim))
            {
                sentence_copy[i] = delim;
            }
            else
            {
                sentence_copy[i] = c;
            }
        }
        else
        {
            sentence_copy[i] = delim;
        }
    }

    size_t words_count = 0;
    char *token = strtok(sentence_copy, &delim);
    while (token != NULL)
    {
        int result = update_count(words, &words_count, token);
        if (result < 0)
        {
            return result;
        }
        token = strtok(NULL, &delim);
    }

    return (int)words_count;
}