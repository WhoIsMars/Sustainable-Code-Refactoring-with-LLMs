#include "grains.h"

namespace grains {
    constexpr unsigned long long square(int n) noexcept
    {
        return 1ULL << (n - 1);
    }

    constexpr unsigned long long total() noexcept {
        return 0xffff'ffff'ffff'ffff;
    }
}