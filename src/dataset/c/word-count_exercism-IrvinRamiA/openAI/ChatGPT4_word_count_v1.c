#include "word_count.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int count_words(const char *sentence, word_count_word_t *words)
{
    if (!sentence || !words) return 0;

    const char *delimiters = " ,.-\n:!!&@$%^&\"";
    char copy_sentence[MAX_WORD_LENGTH * MAX_WORDS] = {0};
    unsigned char total_words = 0;

    // Convert sentence to lowercase and copy to buffer
    for (unsigned char i = 0; sentence[i] != '\0' && i < sizeof(copy_sentence) - 1; i++) {
        copy_sentence[i] = tolower(sentence[i]);
    }

    char *token = strtok(copy_sentence, delimiters);

    while (token != NULL) {
        size_t token_len = strlen(token);

        // Remove surrounding single quotes
        if (token[0] == '\'' && token[token_len - 1] == '\'') {
            token[token_len - 1] = '\0';
            token++;
            token_len -= 2;
        }

        // Check if the word already exists
        unsigned char i;
        for (i = 0; i < total_words; i++) {
            if (strcmp(words[i].text, token) == 0) {
                words[i].count++;
                break;
            }
        }

        // Add new word if not found
        if (i == total_words && total_words < MAX_WORDS) {
            strncpy(words[total_words].text, token, MAX_WORD_LENGTH - 1);
            words[total_words].text[MAX_WORD_LENGTH - 1] = '\0'; // Ensure null-termination
            words[total_words].count = 1;
            total_words++;
        }

        token = strtok(NULL, delimiters);
    }

    return total_words;
}