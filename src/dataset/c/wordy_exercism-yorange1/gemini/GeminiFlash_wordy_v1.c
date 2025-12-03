#include "wordy.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char get_operation(const char *substr) {
    if (!substr) return '\0';

    if (substr[0] == 'p' && strcmp(substr, "plus") == 0) return '+';
    if (substr[0] == 'm') {
        if (strcmp(substr, "minus") == 0) return '-';
        if (strcmp(substr, "multiplied") == 0) return '*';
    }
    if (substr[0] == 'd' && strcmp(substr, "divided") == 0) return '/';

    return '\0';
}

static int calculate(int number1, int number2, char operation) {
    switch (operation) {
        case '+': return number1 + number2;
        case '-': return number1 - number2;
        case '*': return number1 * number2;
        case '/': return number1 / number2;
        default: return 0; // Or handle error as needed
    }
}

bool answer(const char *question, int *result) {
    if (!question || !result) return false;

    size_t len = strlen(question);
    if (len < 10 || strncmp(question, "What is", 7) != 0) return false;

    const char *p = question + 8;
    int number1 = 0;
    int sign = 1;
    bool first_number_found = false;
    int current_number = 0;
    char operation = '+';
    bool operation_pending = false;

    while (*p) {
        if (isdigit((unsigned char)*p) || (*p == '-' && !first_number_found && !operation_pending)) {
            int num_sign = 1;
            if (*p == '-') {
                num_sign = -1;
                p++;
            }
            current_number = 0;
            while (isdigit((unsigned char)*p)) {
                current_number = current_number * 10 + (*p - '0');
                p++;
            }
            current_number *= num_sign;

            if (!first_number_found) {
                number1 = current_number;
                first_number_found = true;
            } else {
                number1 = calculate(number1, current_number, operation);
                operation_pending = false;
            }
        } else if (isalpha((unsigned char)*p)) {
            const char *start = p;
            while (isalpha((unsigned char)*p)) {
                p++;
            }
            size_t word_len = p - start;
            char word[20];
            if (word_len < sizeof(word)) {
                strncpy(word, start, word_len);
                word[word_len] = '\0';

                if (strcmp(word, "plus") == 0) {
                    operation = '+';
                    operation_pending = true;
                } else if (strcmp(word, "minus") == 0) {
                    operation = '-';
                    operation_pending = true;
                } else if (strcmp(word, "multiplied") == 0) {
                    operation = '*';
                    operation_pending = true;
                    if (strncmp(p, " by", 3) == 0) p += 3;
                } else if (strcmp(word, "divided") == 0) {
                    operation = '/';
                    operation_pending = true;
                    if (strncmp(p, " by", 3) == 0) p += 3;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (*p == '?') {
            break;
        } else {
            p++;
        }
        while (isspace((unsigned char)*p)) p++;
    }

    if (!first_number_found || operation_pending) return false;

    *result = number1;
    return true;
}