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

    char *buf = NULL;
    size_t len = 0;

    uint16_t hundred = number / 100;
    uint16_t under_hundred = number % 100;

    if (hundred != 0)
    {
        if (asprintf(&buf, "%s hundred", digit_0_19_name[hundred]) == -1)
            return -1;
        len = strlen(buf);
    }

    if (under_hundred != 0)
    {
        char *under_hundred_str = NULL;
        if (under_hundred < 20)
        {
            if (asprintf(&under_hundred_str, "%s", digit_0_19_name[under_hundred]) == -1)
            {
                free(buf);
                return -1;
            }
        }
        else
        {
            uint16_t ten = under_hundred / 10;
            uint16_t under_ten = under_hundred % 10;
            if (under_ten != 0)
            {
                if (asprintf(&under_hundred_str, "%s-%s", tens_20_90_name[ten], digit_0_19_name[under_ten]) == -1)
                {
                    free(buf);
                    return -1;
                }
            }
            else
            {
                if (asprintf(&under_hundred_str, "%s", tens_20_90_name[ten]) == -1)
                {
                    free(buf);
                    return -1;
                }
            }
        }

        if (buf != NULL)
        {
            char *tmp = NULL;
            if (asprintf(&tmp, "%s %s", buf, under_hundred_str) == -1)
            {
                free(buf);
                free(under_hundred_str);
                return -1;
            }
            free(buf);
            free(under_hundred_str);
            buf = tmp;
        }
        else
        {
            buf = under_hundred_str;
        }
    }

    *result = buf;
    return 0;
}

int say(int64_t input, char **ans)
{
    assert(ans != NULL);

    if (input > MAX_INPUT || input < MIN_INPUT)
        return -1;

    if (input == 0)
    {
        return asprintf(ans, "zero") == -1 ? -1 : 0;
    }

    char *parts[4] = {NULL, NULL, NULL, NULL};
    const char *scales[] = {"", " thousand", " million", " billion"};
    int i = 0;
    int result = 0;

    while (input > 0)
    {
        uint16_t chunk = input % SCALE_BASE;
        if (chunk != 0)
        {
            if (say_thousand(chunk, &parts[i]) != 0)
            {
                for (int j = 0; j < i; j++)
                {
                    free(parts[j]);
                }
                return -1;
            }

            if (i > 0)
            {
                char *tmp = NULL;
                if (asprintf(&tmp, "%s%s", parts[i], scales[i]) == -1)
                {
                    for (int j = 0; j <= i; j++)
                    {
                        free(parts[j]);
                    }
                    return -1;
                }
                free(parts[i]);
                parts[i] = tmp;
            }
        }
        input /= SCALE_BASE;
        i++;
    }

    char *final_result = NULL;
    if (parts[0] != NULL)
    {
        final_result = parts[0];
    }

    for (int j = 1; j < i; j++)
    {
        if (parts[j] != NULL)
        {
            if (final_result != NULL)
            {
                char *tmp = NULL;
                if (asprintf(&tmp, "%s %s", parts[j], final_result) == -1)
                {
                    free(final_result);
                    free(parts[j]);
                    for (int k = j + 1; k < i; k++)
                    {
                        free(parts[k]);
                    }
                    return -1;
                }
                free(final_result);
                final_result = tmp;
            }
            else
            {
                final_result = parts[j];
            }
        }
    }

    *ans = final_result;

    return 0;
}