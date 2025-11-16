#include "grains.h"

namespace grains {

    unsigned long long square(int squares) {
        return 1ULL << (squares - 1);
    }

    unsigned long long total() {
        // Use precomputed value for the total of all squares
        return (1ULL << 64) - 1;
    }

}  // namespace grains