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

    char sentence_copy[length + 1];

    size_t j = 0;
    for (size_t i = 0; i < length; i++) {
        char c = sentence[i];
        if (isalnum(c)) {
            sentence_copy[j++] = (char)tolower(c);
        } else if (c == '\'') {
            if (i > 0 && i < length - 1 && isalnum(sentence[i - 1]) && isalnum(sentence[i + 1])) {
                sentence_copy[j++] = c;
            }
        } else {
            sentence_copy[j++] = delim;
        }
    }
    sentence_copy[j] = '\0';

    int words_count = 0;
    char *token = strtok(sentence_copy, &delim);
    while (token != NULL) {
        if ((words_count = update_count(words, words_count, token)) < 0) {
            return words_count;
        }
        token = strtok(NULL, &delim);
    }

    return words_count;
}