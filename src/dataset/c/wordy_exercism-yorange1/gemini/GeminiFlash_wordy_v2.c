#include "wordy.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char get_operation(const char *token) {
    if (!token) return '\0';

    if (token[0] == 'p' && strcmp(token, "plus") == 0) return '+';
    if (token[0] == 'm') {
        if (strcmp(token, "minus") == 0) return '-';
        if (strcmp(token, "multiplied") == 0) return '*';
    }
    if (token[0] == 'd' && strcmp(token, "divided") == 0) return '/';

    return '\0';
}

static bool is_valid_number(const char *str) {
    if (!str || *str == '\0') return false;

    if (*str == '-' || *str == '+') str++;

    if (*str == '\0') return false;

    for (; *str != '\0'; str++) {
        if (!isdigit(*str)) return false;
    }

    return true;
}

bool answer(const char *question, int *result) {
    if (!question || !result) return false;

    size_t len = strlen(question);
    if (len < 10 || strncmp(question, "What is", 7) != 0 || question[len - 1] != '?') return false;

    const char *start = question + 8;
    const char *end = question + len - 1;

    int number1;
    if (sscanf(start, "%d", &number1) != 1) return false;

    int answer_val = number1;
    char operation = '\0';
    int number2;
    const char *current = start;
    while (current < end) {
        while (isspace(*current)) current++;

        if (isdigit(*current) || *current == '-' || *current == '+') {
            if (operation == '\0') {
                if (current != start) return false;
            } else {
                if (sscanf(current, "%d", &number2) != 1) return false;

                switch (operation) {
                    case '+': answer_val += number2; break;
                    case '-': answer_val -= number2; break;
                    case '*': answer_val *= number2; break;
                    case '/':
                        if (number2 == 0) return false;
                        answer_val /= number2;
                        break;
                    default: return false;
                }
                operation = '\0';
            }
            while (isdigit(*current) || *current == '-' || *current == '+') current++;
        } else {
            char op_str[20] = {0};
            int i = 0;
            while (current < end && !isspace(*current)) {
                op_str[i++] = *current++;
                if (i >= sizeof(op_str) - 1) return false;
            }

            if (op_str[0] == '\0') break;

            if (operation != '\0') return false;

            if (strcmp(op_str, "plus") == 0) operation = '+';
            else if (strcmp(op_str, "minus") == 0) operation = '-';
            else if (strcmp(op_str, "multiplied") == 0) operation = '*';
            else if (strcmp(op_str, "divided") == 0) operation = '/';
            else if (strcmp(op_str, "by") == 0) continue;
            else return false;
        }
    }

    if (operation != '\0') return false;

    *result = answer_val;
    return true;
}