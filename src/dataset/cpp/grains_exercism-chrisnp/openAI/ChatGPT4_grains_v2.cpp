#include "grains.h"

uint_least64_t grains::square(uint_least16_t num) {
    return 1ULL << (num - 1);
}

uint_least64_t grains::total() {
    return ~0ULL; // Equivalent to (1ULL << 64) - 1 for 64-bit unsigned integers
}