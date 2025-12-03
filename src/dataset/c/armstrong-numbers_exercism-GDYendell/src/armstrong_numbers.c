#include "armstrong_numbers.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_armstrong_number(int candidate) {
    char digits[9];
    sprintf(digits, "%d", candidate);

    int len = strlen(digits);
    int armstrong_number = 0;
    for (int i = 0; i < len; ++i) {
        int digit = digits[i] - '0';
        armstrong_number += pow(digit, len);
    }

    return candidate == armstrong_number;
}
