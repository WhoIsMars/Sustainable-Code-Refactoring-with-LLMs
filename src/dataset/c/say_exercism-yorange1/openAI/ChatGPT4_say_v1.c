#define _GNU_SOURCE
#include "say.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_INPUT (0)
#define MAX_INPUT (999999999999)
#define SCALE_BASE (1000)

static const char *digit_0_19_name[] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

static const char *tens_20_90_name[] = {
    "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

static char *say_thousand(uint16_t number)
{
    assert(number < 1000);

    char buffer[100] = {0};
    char *result = NULL;

    uint16_t hundred = number / 100;
    uint16_t under_hundred = number % 100;

    if (hundred != 0)
    {
        snprintf(buffer, sizeof(buffer), "%s hundred", digit_0_19_name[hundred]);
    }

    if (under_hundred != 0)
    {
        if (under_hundred < 20)
        {
            snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "%s%s",
                     hundred ? " " : "", digit_0_19_name[under_hundred]);
        }
        else
        {
            uint16_t ten = under_hundred / 10;
            uint16_t under_ten = under_hundred % 10;
            snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "%s%s%s",
                     hundred ? " " : "", tens_20_90_name[ten],
                     under_ten ? "-" : "");
            if (under_ten)
            {
                snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "%s", digit_0_19_name[under_ten]);
            }
        }
    }

    result = strdup(buffer);
    return result;
}

int say(int64_t input, char **ans)
{
    assert(ans != NULL);

    if (input > MAX_INPUT || input < MIN_INPUT)
        return -1;

    if (input == 0)
    {
        *ans = strdup("zero");
        return 0;
    }

    char buffer[1024] = {0};
    char *parts[4] = {NULL, NULL, NULL, NULL};
    const char *scales[] = {"", "thousand", "million", "billion"};
    int scale_index = 0;

    while (input > 0 && scale_index < 4)
    {
        uint16_t chunk = input % SCALE_BASE;
        if (chunk != 0)
        {
            char *chunk_str = say_thousand(chunk);
            if (buffer[0] != '\0')
            {
                snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), " ");
            }
            if (scale_index > 0)
            {
                snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "%s ", scales[scale_index]);
            }
            snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "%s", chunk_str);
            free(chunk_str);
        }
        input /= SCALE_BASE;
        scale_index++;
    }

    size_t len = strlen(buffer);
    *ans = malloc(len + 1);
    if (*ans)
    {
        for (size_t i = 0; i < len; i++)
        {
            (*ans)[i] = buffer[len - i - 1];
        }
        (*ans)[len] = '\0';
    }

    return 0;
}