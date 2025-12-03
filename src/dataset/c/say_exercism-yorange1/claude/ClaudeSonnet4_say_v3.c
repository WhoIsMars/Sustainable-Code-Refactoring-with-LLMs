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
#define MAX_RESULT_LEN (256)

static const char * const digit_0_19_name[] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
};

static const char * const tens_20_90_name[] = {
    "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
};

static const char * const scale_names[] = {"", "thousand", "million", "billion"};

static int append_thousand(char *buffer, int pos, uint16_t number, const char *scale)
{
    if (number == 0) return pos;
    
    if (pos > 0) {
        buffer[pos++] = ' ';
    }
    
    uint16_t hundred = number / 100;
    uint16_t under_hundred = number % 100;
    
    if (hundred != 0) {
        const char *hundred_name = digit_0_19_name[hundred];
        while (*hundred_name) buffer[pos++] = *hundred_name++;
        buffer[pos++] = ' ';
        buffer[pos++] = 'h';
        buffer[pos++] = 'u';
        buffer[pos++] = 'n';
        buffer[pos++] = 'd';
        buffer[pos++] = 'r';
        buffer[pos++] = 'e';
        buffer[pos++] = 'd';
        if (under_hundred != 0) buffer[pos++] = ' ';
    }
    
    if (under_hundred != 0) {
        if (under_hundred < 20) {
            const char *name = digit_0_19_name[under_hundred];
            while (*name) buffer[pos++] = *name++;
        } else {
            uint16_t ten = under_hundred / 10;
            uint16_t under_ten = under_hundred % 10;
            const char *tens_name = tens_20_90_name[ten];
            while (*tens_name) buffer[pos++] = *tens_name++;
            if (under_ten != 0) {
                buffer[pos++] = '-';
                const char *ones_name = digit_0_19_name[under_ten];
                while (*ones_name) buffer[pos++] = *ones_name++;
            }
        }
    }
    
    if (*scale) {
        buffer[pos++] = ' ';
        while (*scale) buffer[pos++] = *scale++;
    }
    
    return pos;
}

static char *say_thousand(uint16_t number)
{
    char *buffer = malloc(64);
    if (!buffer) return NULL;
    
    int pos = append_thousand(buffer, 0, number, "");
    buffer[pos] = '\0';
    
    return buffer;
}

int say(int64_t input, char **ans)
{
    assert(ans != NULL);

    if (input > MAX_INPUT || input < MIN_INPUT)
        return -1;

    if (input == 0) {
        *ans = malloc(5);
        if (!*ans) return -1;
        strcpy(*ans, "zero");
        return 0;
    }

    char *buffer = malloc(MAX_RESULT_LEN);
    if (!buffer) return -1;
    
    int pos = 0;
    uint16_t parts[4];
    int scale_idx = 0;
    
    while (input > 0 && scale_idx < 4) {
        parts[scale_idx] = input % SCALE_BASE;
        input /= SCALE_BASE;
        scale_idx++;
    }
    
    for (int i = scale_idx - 1; i >= 0; i--) {
        if (parts[i] != 0) {
            pos = append_thousand(buffer, pos, parts[i], scale_names[i]);
        }
    }
    
    buffer[pos] = '\0';
    *ans = buffer;
    
    return 0;
}