#include "word_count.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int count_words(const char *sentence, word_count_word_t *words) {
    size_t input_len = strlen(sentence);
    if (input_len == 0) return 0;

    char *copy_sentence = (char *)malloc(input_len + 1);
    if (!copy_sentence) return 0;

    const char *delimiters = " ,.-\n:!!&@$%^&\"";
    char *token;
    int total_words = 0;

    // Convert to lowercase and copy
    for (size_t i = 0; i < input_len; ++i) {
        copy_sentence[i] = tolower(sentence[i]);
    }
    copy_sentence[input_len] = '\0';

    token = strtok(copy_sentence, delimiters);

    while (token != NULL) {
        size_t token_len = strlen(token);

        // Handle apostrophes
        if (token_len > 1 && token[0] == '\'' && token[token_len - 1] == '\'') {
            token[token_len - 1] = '\0';
            token++;
            token_len -= 2; // Adjust token_len after removing apostrophes
        }

        int found = 0;
        for (int i = 0; i < total_words; ++i) {
            if (strncmp(words[i].text, token, token_len + 1) == 0) {
                words[i].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (total_words < MAX_WORDS) {
                strncpy(words[total_words].text, token, token_len);
                words[total_words].text[token_len] = '\0'; // Ensure null termination
                words[total_words].count = 1;
                total_words++;
            } else {
                free(copy_sentence);
                return -1; // Indicate an error if MAX_WORDS is exceeded
            }
        }

        token = strtok(NULL, delimiters);
    }

    free(copy_sentence);
    return total_words;
}