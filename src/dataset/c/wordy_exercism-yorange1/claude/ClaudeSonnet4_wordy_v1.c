#include "wordy.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline char get_operation(const char *substr, size_t len)
{
    if (!substr) return ' ';
    
    switch (substr[0]) {
        case 'p':
            return (len == 4 && memcmp(substr, "plus", 4) == 0) ? '+' : 0;
        case 'm':
            if (len == 5 && memcmp(substr, "minus", 5) == 0) return '-';
            if (len == 10 && memcmp(substr, "multiplied", 10) == 0) return '*';
            return 0;
        case 'd':
            return (len == 7 && memcmp(substr, "divided", 7) == 0) ? '/' : 0;
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
    assert(question && result);

    size_t length = strlen(question);
    if (length < 10 || memcmp(question, "What is", 7) != 0) {
        return false;
    }

    const char *ptr = question + 8;
    const char *end = question + length - 1;
    
    // Skip leading spaces
    while (ptr < end && *ptr == ' ') ptr++;
    
    // Parse first number
    char *endptr;
    int number1 = strtol(ptr, &endptr, 10);
    if (endptr == ptr) return false;
    
    ptr = endptr;
    size_t count = 0;
    int answer = number1;
    
    while (ptr < end) {
        // Skip spaces
        while (ptr < end && *ptr == ' ') ptr++;
        if (ptr >= end) break;
        
        // Find operation word
        const char *op_start = ptr;
        while (ptr < end && *ptr != ' ') ptr++;
        size_t op_len = ptr - op_start;
        
        char operation = get_operation(op_start, op_len);
        if (operation == 0) return false;
        
        // Handle "multiplied by" and "divided by"
        if (operation == '*' || operation == '/') {
            while (ptr < end && *ptr == ' ') ptr++;
            if (ptr >= end || (end - ptr < 2) || memcmp(ptr, "by", 2) != 0) return false;
            ptr += 2;
        }
        
        // Skip spaces before number
        while (ptr < end && *ptr == ' ') ptr++;
        if (ptr >= end) return false;
        
        // Parse second number
        int number2 = strtol(ptr, &endptr, 10);
        if (endptr == ptr) return false;
        
        answer = calculate(answer, number2, operation);
        ptr = endptr;
        count++;
    }
    
    *result = answer;
    return true;
}