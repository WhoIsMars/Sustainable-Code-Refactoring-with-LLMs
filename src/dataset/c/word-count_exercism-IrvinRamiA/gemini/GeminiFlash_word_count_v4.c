#include "word_count.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int count_words(const char *sentence, word_count_word_t *words)
{
    size_t input_len = strlen(sentence);
    char *copy_sentence = (char *)malloc(input_len + 1);
    if (!copy_sentence) return -1;

    const char *delimiters = " ,.-\n:!!&@$%^&\"";
    char *token;
    int total_words = 0;

    for (size_t i = 0; i < input_len; i++)
    {
        copy_sentence[i] = tolower(sentence[i]);
    }
    copy_sentence[input_len] = '\0';

    token = strtok(copy_sentence, delimiters);

    while (token != NULL)
    {
        size_t token_len = strlen(token);

        if (token_len > 1 && token[0] == '\'' && token[token_len - 1] == '\'')
        {
            token[token_len - 1] = '\0';
            token++;
            token_len -= 2;
        }

        int found = 0;
        for (int i = 0; i < total_words; i++)
        {
            if (strncmp(words[i].text, token, token_len + 1) == 0)
            {
                words[i].count++;
                found = 1;
                break;
            }
        }

        if (!found)
        {
            if (total_words < MAX_WORDS)
            {
                strncpy(words[total_words].text, token, sizeof(words[total_words].text) - 1);
                words[total_words].text[sizeof(words[total_words].text) - 1] = '\0';
                words[total_words].count = 1;
                total_words++;
            }
            else
            {
                free(copy_sentence);
                return -1;
            }
        }

        token = strtok(NULL, delimiters);
    }

    free(copy_sentence);
    return total_words;
}