#include "grains.h"

using namespace std;

uint_least64_t grains::square(uint_least16_t num) {
    return 1ULL << --num;
}

uint_least64_t grains::total() {
    return (1ULL << 63) + ((1ULL << 63) - 1ULL);
}