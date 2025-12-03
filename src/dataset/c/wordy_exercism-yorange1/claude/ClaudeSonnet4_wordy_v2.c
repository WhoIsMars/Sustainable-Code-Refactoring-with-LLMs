#include "wordy.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline char get_operation(const char *word, const char **next_pos)
{
    switch (word[0]) {
        case 'p':
            return (strcmp(word, "plus") == 0) ? '+' : 0;
        case 'm':
            if (strcmp(word, "minus") == 0) return '-';
            if (strcmp(word, "multiplied") == 0) {
                // Skip "by" word
                while (**next_pos == ' ') (*next_pos)++;
                if (strncmp(*next_pos, "by", 2) == 0) {
                    *next_pos += 2;
                    return '*';
                }
            }
            return 0;
        case 'd':
            if (strcmp(word, "divided") == 0) {
                // Skip "by" word
                while (**next_pos == ' ') (*next_pos)++;
                if (strncmp(*next_pos, "by", 2) == 0) {
                    *next_pos += 2;
                    return '/';
                }
            }
            return 0;
        default:
            return 0;
    }
}

static inline int calculate(int number1, int number2, char operation)
{
    switch (operation) {
        case '+': return number1 + number2;
        case '-': return number1 - number2;
        case '*': return number1 * number2;
        case '/': return number1 / number2;
        default: assert(false); return 0;
    }
}

bool answer(const char *question, int *result)
{
    assert(NULL != question);
    assert(NULL != result);

    size_t length = strlen(question);
    if (length < 10 || strncmp(question, "What is ", 8) != 0 || question[length-1] != '?') {
        return false;
    }

    const char *pos = question + 8;
    const char *end = question + length - 1;
    
    // Skip leading spaces
    while (pos < end && *pos == ' ') pos++;
    
    // Parse first number
    char *endptr;
    int result_value = strtol(pos, &endptr, 10);
    if (endptr == pos) return false;
    pos = endptr;
    
    // Skip spaces
    while (pos < end && *pos == ' ') pos++;
    
    // If we've reached the end, it's just a number
    if (pos >= end) {
        *result = result_value;
        return true;
    }
    
    while (pos < end) {
        // Extract operation word
        const char *word_start = pos;
        while (pos < end && *pos != ' ') pos++;
        
        size_t word_len = pos - word_start;
        char word[16];
        if (word_len >= sizeof(word)) return false;
        
        memcpy(word, word_start, word_len);
        word[word_len] = '\0';
        
        // Skip spaces after operation word
        while (pos < end && *pos == ' ') pos++;
        
        char operation = get_operation(word, &pos);
        if (operation == 0) return false;
        
        // Skip spaces after "by" if applicable
        while (pos < end && *pos == ' ') pos++;
        
        // Parse next number
        int number2 = strtol(pos, &endptr, 10);
        if (endptr == pos) return false;
        pos = endptr;
        
        result_value = calculate(result_value, number2, operation);
        
        // Skip spaces
        while (pos < end && *pos == ' ') pos++;
    }
    
    *result = result_value;
    return true;
}