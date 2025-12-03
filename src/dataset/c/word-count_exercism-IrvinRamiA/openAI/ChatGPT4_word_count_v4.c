#include "word_count.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int count_words(const char *sentence, word_count_word_t *words)
{
    if (!sentence || !words) return 0;

    const char *delimiters = " ,.-\n:!!&@$%^&\"";
    unsigned char total_words = 0;

    char *copy_sentence = strdup(sentence);
    if (!copy_sentence) return 0;

    for (char *p = copy_sentence; *p; ++p) *p = tolower(*p);

    char *token = strtok(copy_sentence, delimiters);

    while (token)
    {
        size_t len = strlen(token);
        if (len > 1 && token[0] == '\'' && token[len - 1] == '\'')
        {
            token[len - 1] = '\0';
            token++;
            len -= 2;
        }

        unsigned char found = 0;
        for (unsigned char i = 0; i < total_words; i++)
        {
            if (strcmp(words[i].text, token) == 0)
            {
                words[i].count++;
                found = 1;
                break;
            }
        }

        if (!found && total_words < MAX_WORDS)
        {
            strncpy(words[total_words].text, token, MAX_WORD_LENGTH - 1);
            words[total_words].text[MAX_WORD_LENGTH - 1] = '\0';
            words[total_words].count = 1;
            total_words++;
        }

        token = strtok(NULL, delimiters);
    }

    free(copy_sentence);
    return total_words;
}