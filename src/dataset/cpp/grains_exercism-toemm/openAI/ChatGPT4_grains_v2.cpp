#include "grains.h"

namespace grains {

    unsigned long long square(int squares) {
        return 1ULL << (squares - 1);
    }

    unsigned long long total() {
        return (1ULL << 64) - 1; // Sum of a geometric series: 2^64 - 1
    }

}  // namespace grains