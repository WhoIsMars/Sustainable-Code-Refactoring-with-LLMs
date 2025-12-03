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

static void append_to_result(char **result, const char *str) {
    if (*result == NULL) {
        asprintf(result, "%s", str);
    } else {
        char *temp = *result;
        asprintf(result, "%s %s", temp, str);
        free(temp);
    }
}

static void say_thousand(uint16_t number, char **result) {
    assert(number < 1000);

    uint16_t hundred = number / 100;
    uint16_t under_hundred = number % 100;

    if (hundred != 0) {
        append_to_result(result, digit_0_19_name[hundred]);
        append_to_result(result, "hundred");
    }

    if (under_hundred != 0) {
        if (under_hundred < 20) {
            append_to_result(result, digit_0_19_name[under_hundred]);
        } else {
            uint16_t ten = under_hundred / 10;
            uint16_t under_ten = under_hundred % 10;
            append_to_result(result, tens_20_90_name[ten]);
            if (under_ten != 0) {
                append_to_result(result, digit_0_19_name[under_ten]);
            }
        }
    }
}

int say(int64_t input, char **ans) {
    assert(ans != NULL);

    if (input > MAX_INPUT || input < MIN_INPUT)
        return -1;

    if (input == 0) {
        *ans = strdup("zero");
        return 0;
    }

    char *result = NULL;

    uint16_t parts[4];
    const char *scale_names[] = {"", "thousand", "million", "billion"};
    int scale_index = 0;

    while (input > 0) {
        parts[scale_index++] = input % SCALE_BASE;
        input /= SCALE_BASE;
    }

    for (int i = scale_index - 1; i >= 0; i--) {
        if (parts[i] != 0) {
            char *part_result = NULL;
            say_thousand(parts[i], &part_result);
            if (scale_names[i][0] != '\0') {
                append_to_result(&part_result, scale_names[i]);
            }
            append_to_result(&result, part_result);
            free(part_result);
        }
    }

    *ans = result;
    return 0;
}