#include "wordy.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static inline char get_operation(const char *word, size_t len)
{
    switch (len) {
        case 4:
            if (memcmp(word, "plus", 4) == 0) return '+';
            break;
        case 5:
            if (memcmp(word, "minus", 5) == 0) return '-';
            break;
        case 7:
            if (memcmp(word, "divided", 7) == 0) return '/';
            break;
        case 10:
            if (memcmp(word, "multiplied", 10) == 0) return '*';
            break;
    }
    return 0;
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

static inline const char* skip_whitespace(const char* str)
{
    while (*str == ' ') str++;
    return str;
}

static inline const char* find_word_end(const char* str)
{
    while (*str && *str != ' ') str++;
    return str;
}

static inline int parse_number(const char* start, const char* end)
{
    int result = 0;
    int sign = 1;
    
    if (start < end && *start == '-') {
        sign = -1;
        start++;
    }
    
    while (start < end && *start >= '0' && *start <= '9') {
        result = result * 10 + (*start - '0');
        start++;
    }
    
    return start == end ? result * sign : INT_MAX;
}

bool answer(const char *question, int *result)
{
    assert(NULL != question);
    assert(NULL != result);

    size_t length = strlen(question);
    if (length < 10 || memcmp(question, "What is ", 8) != 0 || question[length - 1] != '?') {
        return false;
    }

    const char* ptr = question + 8;
    const char* end = question + length - 1;
    
    ptr = skip_whitespace(ptr);
    if (ptr >= end) return false;
    
    const char* word_end = find_word_end(ptr);
    int current_result = parse_number(ptr, word_end);
    if (current_result == INT_MAX) return false;
    
    ptr = skip_whitespace(word_end);
    
    while (ptr < end) {
        word_end = find_word_end(ptr);
        if (word_end == ptr) return false;
        
        size_t word_len = word_end - ptr;
        char operation = get_operation(ptr, word_len);
        
        if (operation == 0) return false;
        
        if (operation == '*' || operation == '/') {
            ptr = skip_whitespace(word_end);
            if (ptr >= end) return false;
            
            word_end = find_word_end(ptr);
            if (word_end - ptr != 2 || memcmp(ptr, "by", 2) != 0) return false;
        }
        
        ptr = skip_whitespace(word_end);
        if (ptr >= end) return false;
        
        word_end = find_word_end(ptr);
        int operand = parse_number(ptr, word_end);
        if (operand == INT_MAX) return false;
        
        if (operation == '/' && operand == 0) return false;
        
        current_result = calculate(current_result, operand, operation);
        ptr = skip_whitespace(word_end);
    }
    
    *result = current_result;
    return true;
}