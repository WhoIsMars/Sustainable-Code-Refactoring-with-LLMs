#include "word_count.h"

#include <ctype.h>
#include <stddef.h>
#include <string.h>

const char delim = ' ';

static int update_count(word_count_word_t *words, size_t words_count, const char *word, size_t word_length)
{
    if (word_length > MAX_WORD_LENGTH)
    {
        return EXCESSIVE_LENGTH_WORD;
    }

    for (size_t i = 0; i < words_count; i++)
    {
        if (words[i].text[0] == word[0] && 
            strncmp(words[i].text, word, word_length) == 0 && 
            words[i].text[word_length] == '\0')
        {
            words[i].count++;
            return words_count;
        }
    }

    // new word
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

    int words_count = 0;
    size_t i = 0;
    
    while (i < length)
    {
        // Skip delimiters
        while (i < length && (!isalnum(sentence[i]) && sentence[i] != '\''))
        {
            i++;
        }
        
        if (i >= length) break;
        
        // Start of word
        size_t word_start = i;
        size_t word_len = 0;
        char word_buffer[MAX_WORD_LENGTH + 1];
        
        while (i < length && word_len < MAX_WORD_LENGTH)
        {
            char c = sentence[i];
            
            if (isalpha(c))
            {
                word_buffer[word_len++] = tolower(c);
            }
            else if (isdigit(c))
            {
                word_buffer[word_len++] = c;
            }
            else if (c == '\'' && i > word_start && i < length - 1 && 
                     isalnum(sentence[i-1]) && isalnum(sentence[i+1]))
            {
                word_buffer[word_len++] = c;
            }
            else
            {
                break;
            }
            i++;
        }
        
        if (word_len > 0)
        {
            word_buffer[word_len] = '\0';
            words_count = update_count(words, words_count, word_buffer, word_len);
            if (words_count < 0)
            {
                return words_count;
            }
        }
        
        // Skip remaining non-word characters
        while (i < length && !isalnum(sentence[i]) && sentence[i] != '\'')
        {
            i++;
        }
    }

    return words_count;
}