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

static size_t append_word(char *buffer, size_t offset, const char *word) {
    if (offset > 0) buffer[offset++] = ' ';
    while (*word) buffer[offset++] = *word++;
    return offset;
}

static size_t say_thousand(uint16_t number, char *buffer, size_t offset) {
    assert(number < 1000);

    uint16_t hundred = number / 100;
    uint16_t under_hundred = number % 100;

    if (hundred != 0) {
        offset = append_word(buffer, offset, digit_0_19_name[hundred]);
        offset = append_word(buffer, offset, "hundred");
    }

    if (under_hundred != 0) {
        if (hundred != 0) offset = append_word(buffer, offset, "and");
        if (under_hundred < 20) {
            offset = append_word(buffer, offset, digit_0_19_name[under_hundred]);
        } else {
            uint16_t ten = under_hundred / 10;
            uint16_t under_ten = under_hundred % 10;
            offset = append_word(buffer, offset, tens_20_90_name[ten]);
            if (under_ten != 0) {
                offset = append_word(buffer, offset, digit_0_19_name[under_ten]);
            }
        }
    }

    return offset;
}

int say(int64_t input, char **ans) {
    assert(ans != NULL);

    if (input > MAX_INPUT || input < MIN_INPUT) return -1;

    if (input == 0) {
        *ans = strdup("zero");
        return 0;
    }

    char buffer[1024] = {0};
    size_t offset = 0;

    const char *scale_names[] = {"", "thousand", "million", "billion"};
    uint16_t parts[4] = {0};
    int part_count = 0;

    while (input > 0 && part_count < 4) {
        parts[part_count++] = input % SCALE_BASE;
        input /= SCALE_BASE;
    }

    for (int i = part_count - 1; i >= 0; --i) {
        if (parts[i] != 0) {
            offset = say_thousand(parts[i], buffer, offset);
            if (i > 0) offset = append_word(buffer, offset, scale_names[i]);
        }
    }

    *ans = strdup(buffer);
    return 0;
}