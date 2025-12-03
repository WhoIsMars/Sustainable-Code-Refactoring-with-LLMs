#include "nth_prime.h"
#include <stdbool.h>
#include <math.h>

static bool is_prime(uint32_t number) {
    if (number <= 1) return false;
    if (number <= 3) return true;
    if (number % 2 == 0 || number % 3 == 0) return false;

    for (uint32_t i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) return false;
    }

    return true;
}

uint32_t nth(uint32_t n) {
    if (n == 0) return 0;

    if (n <= 6) {
        uint32_t small_primes[] = {2, 3, 5, 7, 11, 13};
        return small_primes[n - 1];
    }

    uint32_t candidate = 13;
    uint32_t count = 6;

    while (count < n) {
        candidate += 2;
        if (is_prime(candidate)) {
            count++;
        }
    }

    return candidate;
}