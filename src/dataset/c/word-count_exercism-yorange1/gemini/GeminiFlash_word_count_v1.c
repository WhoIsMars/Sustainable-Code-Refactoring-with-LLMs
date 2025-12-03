#include "word_count.h"

#include <ctype.h>
#include <stddef.h>
#include <string.h>

const char delim = ' ';

static int update_count(word_count_word_t *words, size_t words_count, const char *word) {
    size_t word_length = strlen(word);
    if (word_length > MAX_WORD_LENGTH) {
        return EXCESSIVE_LENGTH_WORD;
    }

    for (size_t i = 0; i < words_count; i++) {
        if (words[i].text[0] == word[0] && strcmp(words[i].text, word) == 0) {
            words[i].count++;
            return words_count;
        }
    }

    if (words_count >= MAX_WORDS) {
        return EXCESSIVE_NUMBER_OF_WORDS;
    }

    strncpy(words[words_count].text, word, word_length);
    words[words_count].text[word_length] = '\0';
    words[words_count].count = 1;

    return words_count + 1;
}

int count_words(const char *sentence, word_count_word_t *words) {
    if (sentence == NULL || words == NULL) {
        return INVAILD_PARAMETER;
    }

    size_t length = strlen(sentence);
    if (length == 0) {
        return 0; 
    }

    memset(words, 0, MAX_WORDS * sizeof(word_count_word_t));

    char *sentence_copy = (char *)malloc(length + 1);
    if (sentence_copy == NULL) {
        return INVAILD_PARAMETER; 
    }
    sentence_copy[length] = '\0';

    for (size_t i = 0; i < length; i++) {
        if (isalpha(sentence[i])) {
            sentence_copy[i] = tolower(sentence[i]);
        } else if (isdigit(sentence[i])) {
            sentence_copy[i] = sentence[i];
        } else if (sentence[i] == '\'') {
            if (i == 0 || i == length - 1 || sentence[i - 1] == delim || sentence[i + 1] == delim) {
                sentence_copy[i] = delim;
            } else {
                sentence_copy[i] = sentence[i];
            }
        } else {
            sentence_copy[i] = delim;
        }
    }

    int words_count = 0;
    char *token = strtok(sentence_copy, &delim);
    while (token != NULL) {
        int result = update_count(words, words_count, token);
        if (result < 0) {
            free(sentence_copy);
            return result;
        }
        if (result > words_count) {
            words_count = result;
        }

        token = strtok(NULL, &delim);
    }

    free(sentence_copy);
    return words_count;
}