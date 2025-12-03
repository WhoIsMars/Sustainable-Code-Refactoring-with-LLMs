#include "word_count.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int count_words(const char *sentence, word_count_word_t *words)
{
    unsigned char input_len = strlen(sentence);
    char *copy_sentence = (char *)malloc((input_len + 1) * sizeof(char));
    const char *delimiters = " ,.-\n:!!&@$%^&\"";
    char *token;
    unsigned char total_words = 0;
    unsigned char repeated_word = 0;
    unsigned char index = 0;

    for (index = 0; index < strlen(sentence); index++)
    {
        copy_sentence[index] = tolower(sentence[index]);
    }
    copy_sentence[index] = '\0';

    token = strtok(copy_sentence, delimiters);

    while (token != NULL)
    {
        if (('\'' == token[0]) && ('\'' == token[strlen(token) - 1]))
        {
            token[strlen(token) - 1] = '\0';
            token++;
        }

        /* Saving first word */
        if (total_words == 0)
        {
            strncpy(words[total_words++].text, token, strlen(token));
            words[total_words - 1].count++;
        }
        else
        {
            for (unsigned char i = 0; i < total_words; i++)
            {
                /* Checking if word is repeated */
                if (strncmp(words[i].text, token, strlen(token) + 1) == 0)
                {
                    words[i].count++;
                    repeated_word = 1;
                    break;
                }
            }

            if (repeated_word == 0)
            {
                strncpy(words[total_words++].text, token, strlen(token));
                words[total_words - 1].count++;
            }
            repeated_word = 0;
        }

        token = strtok(NULL, delimiters);
    }

    return total_words;
}
