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

static char *say_thousand(uint16_t number, char *buf)
{
    assert(number < 1000);

    buf[0] = '\0';
    int len = 0;

    uint16_t hundred = number / 100;
    uint16_t under_hundred = number % 100;

    if (hundred != 0)
    {
        len += sprintf(buf + len, "%s hundred", digit_0_19_name[hundred]);
    }

    if (under_hundred != 0)
    {
        if (hundred != 0) {
            len += sprintf(buf + len, " ");
        }
        if (under_hundred < 20)
        {
            len += sprintf(buf + len, "%s", digit_0_19_name[under_hundred]);
        }
        else
        {
            uint16_t ten = under_hundred / 10;
            uint16_t under_ten = under_hundred % 10;
            if (under_ten != 0)
            {
                len += sprintf(buf + len, "%s-%s", tens_20_90_name[ten], digit_0_19_name[under_ten]);
            }
            else
            {
                len += sprintf(buf + len, "%s", tens_20_90_name[ten]);
            }
        }
    }

    return buf;
}

int say(int64_t input, char **ans)
{
    assert(ans != NULL);

    if (input > MAX_INPUT || input < MIN_INPUT)
        return -1;

    if (input == 0)
    {
        if (asprintf(ans, "zero") < 0) return -1;
        return 0;
    }

    char *result = NULL;
    char thousand_buf[128];
    char million_buf[128];
    char billion_buf[128];
    char trillion_buf[128];

    uint16_t under_thousand = input % SCALE_BASE;
    input /= SCALE_BASE;

    uint16_t under_million = input % SCALE_BASE;
    input /= SCALE_BASE;

    uint16_t under_billion = input % SCALE_BASE;
    input /= SCALE_BASE;

    uint16_t under_trillion = input % SCALE_BASE;

    trillion_buf[0] = '\0';
    million_buf[0] = '\0';
    billion_buf[0] = '\0';
    thousand_buf[0] = '\0';

    int len = 0;

    if (under_trillion != 0) {
        say_thousand(under_trillion, trillion_buf);
        len += sprintf(billion_buf + len, "%s billion", trillion_buf);
    }

    if (under_billion != 0) {
        if (len > 0) len += sprintf(billion_buf + len, " ");
        say_thousand(under_billion, trillion_buf);
        len += sprintf(billion_buf + len, "%s million", trillion_buf);
    }

    if (under_million != 0) {
        if (len > 0) len += sprintf(billion_buf + len, " ");
        say_thousand(under_million, trillion_buf);
        len += sprintf(billion_buf + len, "%s thousand", trillion_buf);
    }

    if (under_thousand != 0) {
        if (len > 0) len += sprintf(billion_buf + len, " ");
        say_thousand(under_thousand, trillion_buf);
        len += sprintf(billion_buf + len, "%s", trillion_buf);
    }

    if (len == 0) {
        if (asprintf(ans, "zero") < 0) return -1;
    } else {
        if (asprintf(ans, "%s", billion_buf) < 0) return -1;
    }

    return 0;
}