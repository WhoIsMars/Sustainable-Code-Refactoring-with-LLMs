#include "word_count.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int count_words(const char *sentence, word_count_word_t *words)
{
    size_t input_len = strlen(sentence);
    char *copy_sentence = (char *)malloc((input_len + 1) * sizeof(char));
    if (copy_sentence == NULL) return -1;

    const char *delimiters = " ,.-\n:!!&@$%^&\"";
    char *token;
    int total_words = 0;
    int i;

    for (size_t index = 0; index < input_len; index++)
    {
        copy_sentence[index] = tolower(sentence[index]);
    }
    copy_sentence[input_len] = '\0';

    token = strtok(copy_sentence, delimiters);

    while (token != NULL)
    {
        size_t token_len = strlen(token);

        if (token_len > 0 && token[0] == '\'' && token[token_len - 1] == '\'')
        {
            token[token_len - 1] = '\0';
            token++;
            token_len -= 2;
        }

        int found = 0;
        for (i = 0; i < total_words; i++)
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
            if (total_words < MAX_NUMBER_OF_WORDS) {
                strncpy(words[total_words].text, token, MAX_WORD_LENGTH - 1);
                words[total_words].text[MAX_WORD_LENGTH - 1] = '\0';
                words[total_words].count = 1;
                total_words++;
            } else {
                free(copy_sentence);
                return -1;
            }
        }

        token = strtok(NULL, delimiters);
    }

    free(copy_sentence);
    return total_words;
}