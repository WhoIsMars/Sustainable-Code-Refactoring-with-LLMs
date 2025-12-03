#include "wordy.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char get_operation(const char *substr)
{
    if (strcmp(substr, "plus") == 0)
        return '+';
    if (strcmp(substr, "minus") == 0)
        return '-';
    if (strcmp(substr, "multiplied by") == 0)
        return '*';
    if (strcmp(substr, "divided by") == 0)
        return '/';
    return 0;
}

static int calculate(int number1, int number2, char operation)
{
    switch (operation)
    {
    case '+': return number1 + number2;
    case '-': return number1 - number2;
    case '*': return number1 * number2;
    case '/': return number1 / number2;
    default: assert(false); return 0;
    }
}

bool answer(const char *question, int *result)
{
    assert(question != NULL && result != NULL);

    if (strncmp(question, "What is ", 8) != 0)
        return false;

    const char *expression = question + 8;
    size_t length = strlen(expression);
    if (length < 2 || expression[length - 1] != '?')
        return false;

    char *question_copy = strdup(expression);
    if (!question_copy)
        return false;

    question_copy[length - 1] = '\0'; // Remove '?'

    char *token = strtok(question_copy, " ");
    if (!token)
    {
        free(question_copy);
        return false;
    }

    int number1;
    if (sscanf(token, "%d", &number1) != 1)
    {
        free(question_copy);
        return false;
    }

    int answer = number1;
    while ((token = strtok(NULL, " ")) != NULL)
    {
        char operation = get_operation(token);
        if (operation == 0)
        {
            free(question_copy);
            return false;
        }

        token = strtok(NULL, " ");
        if (!token)
        {
            free(question_copy);
            return false;
        }

        int number2;
        if (sscanf(token, "%d", &number2) != 1)
        {
            free(question_copy);
            return false;
        }

        answer = calculate(answer, number2, operation);
    }

    free(question_copy);
    *result = answer;
    return true;
}