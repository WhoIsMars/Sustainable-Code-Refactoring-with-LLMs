#include "wordy.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static inline char get_operation(const char *substr, size_t len)
{
    if (!substr) return ' ';
    
    switch (len) {
        case 4:
            if (memcmp(substr, "plus", 4) == 0) return '+';
            break;
        case 5:
            if (memcmp(substr, "minus", 5) == 0) return '-';
            break;
        case 10:
            if (memcmp(substr, "multiplied", 10) == 0) return '*';
            break;
        case 7:
            if (memcmp(substr, "divided", 7) == 0) return '/';
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

static inline const char* parse_number(const char* str, int* number)
{
    char* endptr;
    *number = (int)strtol(str, &endptr, 10);
    return (endptr == str) ? NULL : endptr;
}

static inline const char* find_word_end(const char* str)
{
    while (*str && *str != ' ') str++;
    return str;
}

bool answer(const char *question, int *result)
{
    assert(question && result);

    size_t length = strlen(question);
    if (length < 10 || memcmp(question, "What is ", 8) != 0 || question[length - 1] != '?') {
        return false;
    }

    const char* ptr = question + 8;
    const char* end = question + length - 1;
    
    ptr = skip_whitespace(ptr);
    if (ptr >= end) return false;
    
    int number1;
    ptr = parse_number(ptr, &number1);
    if (!ptr) return false;
    
    ptr = skip_whitespace(ptr);
    if (ptr >= end) {
        *result = number1;
        return true;
    }
    
    int answer = number1;
    
    while (ptr < end) {
        const char* word_start = ptr;
        const char* word_end = find_word_end(ptr);
        size_t word_len = word_end - word_start;
        
        char operation = get_operation(word_start, word_len);
        if (operation == 0) return false;
        
        ptr = skip_whitespace(word_end);
        
        if (operation == '*' || operation == '/') {
            word_start = ptr;
            word_end = find_word_end(ptr);
            if (word_end - word_start != 2 || memcmp(word_start, "by", 2) != 0) {
                return false;
            }
            ptr = skip_whitespace(word_end);
        }
        
        if (ptr >= end) return false;
        
        int number2;
        ptr = parse_number(ptr, &number2);
        if (!ptr) return false;
        
        answer = calculate(answer, number2, operation);
        ptr = skip_whitespace(ptr);
    }
    
    *result = answer;
    return true;
}