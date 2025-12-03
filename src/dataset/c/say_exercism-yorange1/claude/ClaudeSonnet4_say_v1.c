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
#define MAX_RESULT_LEN (256)

static const char digit_0_19_name[][MAX_DIGIT_NAME_LEN] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

static const char tens_20_90_name[][MAX_TENS_NAME_LEN] = {
    "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

static const char scale_names[][MAX_SCALE_NAME_LEN] = {
    "", "thousand", "million", "billion"
};

static int say_thousand_to_buffer(uint16_t number, char *buffer, int offset)
{
    if (number == 0) return offset;
    
    uint16_t hundred = number / 100;
    uint16_t under_hundred = number % 100;
    
    if (hundred != 0) {
        offset += sprintf(buffer + offset, "%s hundred", digit_0_19_name[hundred]);
        if (under_hundred != 0) {
            buffer[offset++] = ' ';
        }
    }
    
    if (under_hundred != 0) {
        if (under_hundred < 20) {
            offset += sprintf(buffer + offset, "%s", digit_0_19_name[under_hundred]);
        } else {
            uint16_t ten = under_hundred / 10;
            uint16_t under_ten = under_hundred % 10;
            if (under_ten != 0) {
                offset += sprintf(buffer + offset, "%s-%s", tens_20_90_name[ten], digit_0_19_name[under_ten]);
            } else {
                offset += sprintf(buffer + offset, "%s", tens_20_90_name[ten]);
            }
        }
    }
    
    return offset;
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

    char buffer[MAX_RESULT_LEN];
    int offset = 0;
    uint16_t groups[4];
    int group_count = 0;
    
    // Extract groups of three digits
    while (input > 0 && group_count < 4) {
        groups[group_count] = input % SCALE_BASE;
        input /= SCALE_BASE;
        group_count++;
    }
    
    // Build result from highest to lowest group
    int first_group = 1;
    for (int i = group_count - 1; i >= 0; i--) {
        if (groups[i] != 0) {
            if (!first_group) {
                buffer[offset++] = ' ';
            }
            first_group = 0;
            
            offset = say_thousand_to_buffer(groups[i], buffer, offset);
            
            if (i > 0) {
                offset += sprintf(buffer + offset, " %s", scale_names[i]);
            }
        }
    }
    
    buffer[offset] = '\0';
    
    *ans = malloc(offset + 1);
    strcpy(*ans, buffer);
    
    return 0;
}