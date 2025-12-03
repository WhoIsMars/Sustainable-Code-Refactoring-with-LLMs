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

static const char * const digit_0_19_name[] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

static const char * const tens_20_90_name[] = {
    "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

static const char * const scale_names[] = {"", "thousand", "million", "billion"};

static void append_to_buffer(char **buffer, size_t *pos, size_t *capacity, const char *str)
{
    size_t len = strlen(str);
    size_t needed = *pos + len + 1;
    
    if (needed > *capacity) {
        *capacity = needed * 2;
        *buffer = realloc(*buffer, *capacity);
    }
    
    strcpy(*buffer + *pos, str);
    *pos += len;
}

static void append_space(char **buffer, size_t *pos, size_t *capacity)
{
    if (*pos > 0) {
        append_to_buffer(buffer, pos, capacity, " ");
    }
}

static void say_thousand_to_buffer(uint16_t number, char **buffer, size_t *pos, size_t *capacity)
{
    if (number == 0) return;
    
    uint16_t hundred = number / 100;
    uint16_t under_hundred = number % 100;
    
    if (hundred != 0) {
        append_to_buffer(buffer, pos, capacity, digit_0_19_name[hundred]);
        append_to_buffer(buffer, pos, capacity, " hundred");
        if (under_hundred != 0) {
            append_to_buffer(buffer, pos, capacity, " ");
        }
    }
    
    if (under_hundred != 0) {
        if (under_hundred < 20) {
            append_to_buffer(buffer, pos, capacity, digit_0_19_name[under_hundred]);
        } else {
            uint16_t ten = under_hundred / 10;
            uint16_t under_ten = under_hundred % 10;
            append_to_buffer(buffer, pos, capacity, tens_20_90_name[ten]);
            if (under_ten != 0) {
                append_to_buffer(buffer, pos, capacity, "-");
                append_to_buffer(buffer, pos, capacity, digit_0_19_name[under_ten]);
            }
        }
    }
}

int say(int64_t input, char **ans)
{
    assert(ans != NULL);

    if (input > MAX_INPUT || input < MIN_INPUT)
        return -1;

    if (input == 0) {
        *ans = malloc(5);
        strcpy(*ans, "zero");
        return 0;
    }

    size_t capacity = 256;
    char *buffer = malloc(capacity);
    size_t pos = 0;
    
    uint16_t groups[4];
    int64_t temp = input;
    
    for (int i = 0; i < 4; i++) {
        groups[i] = temp % SCALE_BASE;
        temp /= SCALE_BASE;
    }
    
    bool first = true;
    for (int i = 3; i >= 0; i--) {
        if (groups[i] != 0) {
            if (!first) {
                append_to_buffer(&buffer, &pos, &capacity, " ");
            }
            say_thousand_to_buffer(groups[i], &buffer, &pos, &capacity);
            if (i > 0) {
                append_to_buffer(&buffer, &pos, &capacity, " ");
                append_to_buffer(&buffer, &pos, &capacity, scale_names[i]);
            }
            first = false;
        }
    }
    
    buffer[pos] = '\0';
    *ans = realloc(buffer, pos + 1);
    
    return 0;
}