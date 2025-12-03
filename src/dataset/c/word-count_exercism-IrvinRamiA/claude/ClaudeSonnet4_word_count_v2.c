#include "word_count.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int count_words(const char *sentence, word_count_word_t *words)
{
    size_t input_len = strlen(sentence);
    char *copy_sentence = (char *)malloc((input_len + 1) * sizeof(char));
    const char *delimiters = " ,.-\n:!!&@$%^&\"";
    char *token;
    int total_words = 0;
    int repeated_word = 0;

    // Single pass conversion to lowercase
    for (size_t i = 0; i <= input_len; i++)
    {
        copy_sentence[i] = (i < input_len) ? tolower(sentence[i]) : '\0';
    }

    token = strtok(copy_sentence, delimiters);

    while (token != NULL)
    {
        size_t token_len = strlen(token);
        
        // Handle quotes more efficiently
        if (token_len > 1 && token[0] == '\'' && token[token_len - 1] == '\'')
        {
            token[token_len - 1] = '\0';
            token++;
            token_len -= 2;
        }

        repeated_word = 0;
        // Check for existing word
        for (int i = 0; i < total_words; i++)
        {
            if (strcmp(words[i].text, token) == 0)
            {
                words[i].count++;
                repeated_word = 1;
                break;
            }
        }

        // Add new word if not found
        if (!repeated_word)
        {
            strcpy(words[total_words].text, token);
            words[total_words].count = 1;
            total_words++;
        }

        token = strtok(NULL, delimiters);
    }

    free(copy_sentence);
    return total_words;
}