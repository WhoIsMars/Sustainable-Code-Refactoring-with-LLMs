#define _GNU_SOURCE
#include "say.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_INPUT (0)
#define MAX_INPUT (999999999999)
#define MAX_SCALE_NAME_LEN (10)
#define MAX_DIGIT_NAME_LEN (20)
#define MAX_TENS_NAME_LEN (10)
#define SCALE_BASE (1000)

static const char digit_0_19_name[][MAX_DIGIT_NAME_LEN] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

static const char tens_20_90_name[][MAX_TENS_NAME_LEN] = {
    "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

static int say_thousand(uint16_t number, char **result)
{
    assert(number < 1000);

    char buf[64] = {0}; // Increased buffer size to avoid potential overflows
    int len = 0;

    uint16_t hundred = number / 100;
    uint16_t under_hundred = number % 100;

    if (hundred != 0)
    {
        len += snprintf(buf + len, sizeof(buf) - len, "%s hundred", digit_0_19_name[hundred]);
        if (len < 0 || len >= sizeof(buf)) return -1; // Check for errors
    }

    if (under_hundred != 0)
    {
        if (hundred != 0) {
            len += snprintf(buf + len, sizeof(buf) - len, " ");
            if (len < 0 || len >= sizeof(buf)) return -1;
        }

        if (under_hundred < 20)
        {
            len += snprintf(buf + len, sizeof(buf) - len, "%s", digit_0_19_name[under_hundred]);
            if (len < 0 || len >= sizeof(buf)) return -1;
        }
        else
        {
            uint16_t ten = under_hundred / 10;
            uint16_t under_ten = under_hundred % 10;
            if (under_ten != 0)
            {
                len += snprintf(buf + len, sizeof(buf) - len, "%s-%s", tens_20_90_name[ten], digit_0_19_name[under_ten]);
                if (len < 0 || len >= sizeof(buf)) return -1;
            }
            else
            {
                len += snprintf(buf + len, sizeof(buf) - len, "%s", tens_20_90_name[ten]);
                if (len < 0 || len >= sizeof(buf)) return -1;
            }
        }
    }

    if (len > 0) {
        *result = strdup(buf);
        if (*result == NULL) return -1;
    } else {
        *result = NULL;
    }

    return 0;
}

int say(int64_t input, char **ans)
{
    assert(ans != NULL);

    if (input > MAX_INPUT || input < MIN_INPUT)
        return -1;

    if (input == 0)
    {
        *ans = strdup("zero");
        if (*ans == NULL) return -1;
        return 0;
    }

    char *parts[4] = {NULL, NULL, NULL, NULL};
    const char *scales[] = {"", "thousand", "million", "billion"};
    int i = 0;
    int result = 0;

    while (input > 0)
    {
        uint16_t chunk = input % SCALE_BASE;
        input /= SCALE_BASE;

        if (chunk != 0)
        {
            result = say_thousand(chunk, &parts[i]);
            if (result != 0) {
                // Cleanup allocated memory before returning error
                for (int j = 0; j < i; j++) {
                    free(parts[j]);
                }
                return -1;
            }
        }
        i++;
    }

    // Concatenate the parts
    char buf[256] = {0};
    int len = 0;

    for (int j = i - 1; j >= 0; j--)
    {
        if (parts[j] != NULL)
        {
            if (len > 0) {
                len += snprintf(buf + len, sizeof(buf) - len, " ");
                if (len < 0 || len >= sizeof(buf)) {
                    // Cleanup allocated memory before returning error
                    for (int k = 0; k < i; k++) {
                        free(parts[k]);
                    }
                    return -1;
                }
            }
            len += snprintf(buf + len, sizeof(buf) - len, "%s", parts[j]);
            if (len < 0 || len >= sizeof(buf)) {
                // Cleanup allocated memory before returning error
                for (int k = 0; k < i; k++) {
                    free(parts[k]);
                }
                return -1;
            }

            if (j > 0) {
                len += snprintf(buf + len, sizeof(buf) - len, " %s", scales[j]);
                if (len < 0 || len >= sizeof(buf)) {
                    // Cleanup allocated memory before returning error
                    for (int k = 0; k < i; k++) {
                        free(parts[k]);
                    }
                    return -1;
                }
            }
            free(parts[j]);
        }
    }

    *ans = strdup(buf);
    if (*ans == NULL) return -1;

    return 0;
}