#include "phone_number.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MIN_PHONE_NUMBER_LEN (10)
#define MAX_PHONE_NUMBER_LEN (11)

char *phone_number_clean(const char *input)
{
    char digits[12];
    uint8_t count = 0;
    
    const char *ptr = input;
    while (*ptr && count <= MAX_PHONE_NUMBER_LEN) {
        if (*ptr >= '0' && *ptr <= '9') {
            digits[count++] = *ptr;
        }
        ptr++;
    }
    
    char *number = (char *)malloc(MIN_PHONE_NUMBER_LEN + 1);
    memset(number, '0', MIN_PHONE_NUMBER_LEN);
    number[MIN_PHONE_NUMBER_LEN] = '\0';
    
    if (count == MIN_PHONE_NUMBER_LEN && digits[0] >= '2' && digits[3] >= '2') {
        memcpy(number, digits, MIN_PHONE_NUMBER_LEN);
    }
    else if (count == MAX_PHONE_NUMBER_LEN && digits[0] == '1' && digits[1] >= '2' && digits[4] >= '2') {
        memcpy(number, &digits[1], MIN_PHONE_NUMBER_LEN);
    }
    
    return number;
}