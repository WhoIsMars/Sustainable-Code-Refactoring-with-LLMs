#include "say.h"

#include <assert.h>
#include <stdbool.h>
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

static int say_thousand(uint16_t number, char *buf, size_t size)
{
    assert(number < 1000);

    if (number == 0)
    {
        return 0;
    }

    int written = 0;
    uint16_t hundred = number / 100;
    uint16_t under_hundred = number % 100;

    if (hundred != 0)
    {
        written = snprintf(buf, size, "%s hundred", digit_0_19_name[hundred]);
        if (written < 0 || (size_t)written >= size)
            return -1;
    }

    if (under_hundred != 0)
    {
        if (hundred != 0)
        {
            written += snprintf(buf + written, size - written, " ");
            if (written < 0 || (size_t)written >= size)
                return -1;
        }

        if (under_hundred < 20)
        {
            written += snprintf(buf + written, size - written, "%s", digit_0_19_name[under_hundred]);
            if (written < 0 || (size_t)written >= size)
                return -1;
        }
        else
        {
            uint16_t ten = under_hundred / 10;
            uint16_t under_ten = under_hundred % 10;
            if (under_ten != 0)
            {
                written += snprintf(buf + written, size - written, "%s-%s", tens_20_90_name[ten], digit_0_19_name[under_ten]);
                if (written < 0 || (size_t)written >= size)
                    return -1;
            }
            else
            {
                written += snprintf(buf + written, size - written, "%s", tens_20_90_name[ten]);
                if (written < 0 || (size_t)written >= size)
                    return -1;
            }
        }
    }

    return written;
}

int say(int64_t input, char **ans)
{
    assert(ans != NULL);

    if (input > MAX_INPUT || input < MIN_INPUT)
        return -1;

    if (input == 0)
    {
        *ans = strdup("zero");
        if (*ans == NULL)
            return -1;
        return 0;
    }

    char *result = NULL;
    size_t result_size = 256;
    result = malloc(result_size);
    if (result == NULL)
        return -1;
    result[0] = '\0';

    int written = 0;
    int scale_count = 0;
    char scale_str[64];

    if (input == 0) {
        written = snprintf(result, result_size, "zero");
        if (written < 0 || (size_t)written >= result_size) {
            free(result);
            return -1;
        }
        *ans = result;
        return 0;
    }

    char *scales[] = {"", "thousand", "million", "billion"};
    int num_scales = sizeof(scales) / sizeof(scales[0]);

    int64_t remaining = input;
    bool first_part = true;

    for (int i = 0; i < num_scales; ++i) {
        uint16_t part = remaining % SCALE_BASE;
        remaining /= SCALE_BASE;

        if (part != 0) {
            int scale_written = say_thousand(part, scale_str, sizeof(scale_str));
            if (scale_written < 0) {
                free(result);
                return -1;
            }

            size_t needed = strlen(scale_str) + (i > 0 ? strlen(scales[i]) + 1 : 0) + (written > 0 ? 1 : 0) + 1;

            if (needed > result_size - written) {
                char *new_result = realloc(result, result_size + 256);
                if (new_result == NULL) {
                    free(result);
                    return -1;
                }
                result = new_result;
                result_size += 256;
            }

            if (!first_part) {
                memmove(result + strlen(scale_str) + (i > 0 ? strlen(scales[i]) + 1 : 0) + 1, result, strlen(result) + 1);
            }

            if (i > 0) {
                snprintf(result, strlen(scale_str) + strlen(scales[i]) + 2, "%s %s", scale_str, scales[i]);
            } else {
                snprintf(result, strlen(scale_str) + 1, "%s", scale_str);
            }

            if (!first_part) {
                snprintf(result + strlen(scale_str) + (i > 0 ? strlen(scales[i]) + 1 : 0), 2, " ");
            }

            first_part = false;
        }
    }

    *ans = result;
    return 0;
}