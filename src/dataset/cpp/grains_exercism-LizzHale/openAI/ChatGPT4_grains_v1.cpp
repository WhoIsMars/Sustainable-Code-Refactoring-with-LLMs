#include "grains.h"

namespace grains {

    uint64_t square(int number) {
        return uint64_t(1) << (number - 1);
    }

    uint64_t total() {
        return (uint64_t(1) << max_squares) - 1;
    }

}  // namespace grains