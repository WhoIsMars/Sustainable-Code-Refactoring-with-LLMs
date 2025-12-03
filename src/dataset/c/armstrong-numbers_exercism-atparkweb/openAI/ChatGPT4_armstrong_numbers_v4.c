#include "armstrong_numbers.h"
#include <stdbool.h>

bool is_armstrong_number(int candidate) {
    if (candidate < 0)
        return false;

    int number = candidate, total = 0, numDigits = 0, powerLookup[10];
    while (number > 0) {
        numDigits++;
        number /= 10;
    }

    number = candidate;
    for (int i = 0; i < 10; i++) {
        int result = 1;
        for (int j = 0; j < numDigits; j++) {
            result *= i;
        }
        powerLookup[i] = result;
    }

    while (number > 0) {
        total += powerLookup[number % 10];
        number /= 10;
    }

    return candidate == total;
}