#include "word_count.h"

#include <ctype.h>
#include <stddef.h>
#include <string.h>

static int update_count(word_count_word_t *words, size_t words_count, const char *word, size_t word_length)
{
    if (word_length > MAX_WORD_LENGTH)
    {
        return EXCESSIVE_LENGTH_WORD;
    }

    for (size_t i = 0; i < words_count; i++)
    {
        if (words[i].text[0] == word[0] && 
            strncmp(words[i].text, word, word_length + 1) == 0)
        {
            words[i].count++;
            return words_count;
        }
    }

    if (words_count >= MAX_WORDS)
    {
        return EXCESSIVE_NUMBER_OF_WORDS;
    }

    memcpy(words[words_count].text, word, word_length);
    words[words_count].text[word_length] = '\0';
    words[words_count].count = 1;

    return words_count + 1;
}

int count_words(const char *sentence, word_count_word_t *words)
{
    if (NULL == sentence || NULL == words)
        return INVAILD_PARAMETER;

    size_t length = strlen(sentence);
    if (0 == length)
    {
        return EXCESSIVE_LENGTH_WORD;
    }

    memset(words, 0, MAX_WORDS * sizeof(word_count_word_t));

    char sentence_copy[length + 1];
    const char *src = sentence;
    char *dst = sentence_copy;
    
    for (size_t i = 0; i < length; i++)
    {
        char c = src[i];
        if (isalpha(c))
        {
            *dst++ = tolower(c);
        }
        else if (isdigit(c))
        {
            *dst++ = c;
        }
        else if (c == '\'')
        {
            if (i == 0 || i == length - 1 || src[i - 1] == ' ' || src[i + 1] == ' ')
            {
                *dst++ = ' ';
            }
            else
            {
                *dst++ = c;
            }
        }
        else
        {
            *dst++ = ' ';
        }
    }
    *dst = '\0';

    int words_count = 0;
    char *word_start = sentence_copy;
    char *word_end;
    
    while (*word_start)
    {
        while (*word_start == ' ') word_start++;
        if (!*word_start) break;
        
        word_end = word_start;
        while (*word_end && *word_end != ' ') word_end++;
        
        size_t word_length = word_end - word_start;
        char temp = *word_end;
        *word_end = '\0';
        
        words_count = update_count(words, words_count, word_start, word_length);
        if (words_count < 0)
        {
            return words_count;
        }
        
        *word_end = temp;
        word_start = word_end;
    }

    return words_count;
}