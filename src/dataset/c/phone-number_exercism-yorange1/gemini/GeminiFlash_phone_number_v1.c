#include "phone_number.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MIN_PHONE_NUMBER_LEN (10)
#define MAX_PHONE_NUMBER_LEN (11)

char *phone_number_clean(const char *input) {
    char *number = (char *)calloc(1, MIN_PHONE_NUMBER_LEN + 1);
    if (!number) return NULL; 

    uint8_t count = 0;
    char temp[MAX_PHONE_NUMBER_LEN + 1] = {0};
    size_t input_len = strlen(input);

    for (size_t i = 0; i < input_len; ++i) {
        if (isdigit(input[i])) {
            if (count >= MAX_PHONE_NUMBER_LEN) {
                memset(number, '0', MIN_PHONE_NUMBER_LEN);
                return number;
            }
            temp[count++] = input[i];
        }
    }

    if (count == MIN_PHONE_NUMBER_LEN && temp[0] >= '2' && temp[3] >= '2') {
        memcpy(number, temp, MIN_PHONE_NUMBER_LEN);
        return number;
    } else if (count == MAX_PHONE_NUMBER_LEN && temp[0] == '1' && temp[1] >= '2' && temp[4] >= '2') {
        memcpy(number, &temp[1], MIN_PHONE_NUMBER_LEN);
        return number;
    }

    memset(number, '0', MIN_PHONE_NUMBER_LEN);
    return number;
}